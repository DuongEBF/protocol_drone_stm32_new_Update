/*
 * UI.c
 *
 *  Created on: Aug 7, 2025
 *      Author: duong
 */
#include "UI.h"
#include <string.h>
#include <math.h>
extern UART_HandleTypeDef huart2;
#define DISARM_TILT_DEG         40.0f
#define ATT_VALID_MS            500

static float     att_roll = 0.0f, att_pitch = 0.0f; // radians
static uint32_t  att_last_ms = 0;                    // tick khi nhận ATTITUDE
// Tweakable timings (ms)
#define UNINIT_HALF_PERIOD_MS   300   // -> 50% duty, 600 ms full period
#define STANDBY_PERIOD_MS       1050
#define STANDBY_ON_MS           50
#define ACTIVE_HALF_PERIOD_MS   500   // -> alternate every 300 ms
#define CRITICAL_HALF_PERIOD_MS 200   // -> 50% duty, 400 ms full period

/* ---------- UI state ---------- */

static ui_rw_t ui = {.uart_tx_busy = 0};
static mavlink_ui_t mav;

static uint32_t last_heartbeat_time = 0;
static uint32_t heartbeat_period_ms = 0;
static float     heartbeat_freq_hz = 0.0f;

static GPIO_TypeDef* gpio = NULL;

/* ---------- LED ---------- */
/* ---------- Helpers ---------- */
// Helper: compute ON window in a repeating period
static inline uint8_t pulse_in_period(uint32_t now, uint32_t t0, uint16_t period_ms, uint16_t on_ms)
{
    uint32_t phase = (now - t0) % period_ms; // unsigned math -> overflow-safe
    return (phase < on_ms) ? 1u : 0u;
}

// Helper: write only when a pin actually needs to change
static inline void set_pin_if_changed(GPIO_TypeDef *port, uint16_t pin, uint8_t on, uint8_t *cached)
{
    if (on != *cached)
    {
        HAL_GPIO_WritePin(port, pin, on ? GPIO_PIN_SET : GPIO_PIN_RESET);
        *cached = on;
    }
}
/* ---------- UART IRQ ---------- */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART2)
	{
		RINGBUF_Put(&ui.ring, ui.rx_byte);
		HAL_UART_Receive_IT(&huart2, &ui.rx_byte, 1);
	}
}
static void ring_buffer_send_data(void)
{
    if (ui.uart_tx_busy) return;

    uint8_t data_to_send = 0;
	if(RINGBUF_Get(&ui.ring_tx, &data_to_send) == RING_OK)
	{
		uint8_t tx_data[1] = {data_to_send};
		ui.uart_tx_busy = 1;
		HAL_UART_Transmit_IT(&huart2, tx_data, 1);
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
      ui.uart_tx_busy = 0;
      ring_buffer_send_data();
    }
}


static void update_leds_by_mav_state(uint8_t state, uint32_t now)
{
    // Cache last outputs to avoid redundant HAL writes
    static uint8_t last_front_green = 0xFF, last_front_red = 0xFF;
    static uint8_t last_rear_green  = 0xFF, last_rear_red  = 0xFF;

    // Track when we entered the current state to restart patterns cleanly
    static uint8_t  last_state      = 0xFF;
    static uint32_t state_t0        = 0;

    if (state != last_state)
    {
        last_state = state;
        state_t0   = now;
    }

    // Front LEDs: constant according to your original logic
    set_pin_if_changed(gpio, LED_FRONT_GEAR_GREEN_Pin, 1, &last_front_green);
    set_pin_if_changed(gpio, LED_FRONT_GEAR_RED_Pin,   0, &last_front_red);

    // Compute desired rear LED states for this frame
    uint8_t rg = last_rear_green;  // default: keep previous if we don't handle the state
    uint8_t rr = last_rear_red;
    /* ---------- OVERRIDE: DISARM + TILT ---------- */
    do {
        static uint8_t tilt_override_last = 0;

        const uint8_t is_armed = (mav.hb.base_mode & MAV_MODE_FLAG_SAFETY_ARMED) ? 1 : 0;

        const uint8_t att_fresh = (att_last_ms != 0) && ((now - att_last_ms) <= ATT_VALID_MS);

        const float tilt_thresh_rad = DISARM_TILT_DEG * (float)M_PI / 180.0f;
        const uint8_t is_tilted = (att_fresh &&
                                  (fabsf(att_roll)  > tilt_thresh_rad ||
                                   fabsf(att_pitch) > tilt_thresh_rad)) ? 1 : 0;

        const uint8_t tilt_override = (!is_armed && is_tilted) ? 1 : 0;

        if (tilt_override != tilt_override_last)
        {
            state_t0 = now;
            tilt_override_last = tilt_override;
        }

        if (tilt_override)
        {
            rg = 0;
            rr = pulse_in_period(now, state_t0, 2 * CRITICAL_HALF_PERIOD_MS, CRITICAL_HALF_PERIOD_MS);
            set_pin_if_changed(gpio, LED_REAR_GEAR_GREEN_Pin, rg, &last_rear_green);
            set_pin_if_changed(gpio, LED_REAR_GEAR_RED_Pin,   rr, &last_rear_red);
            return;
        }
    } while (0);
    /* --------------------------------------------- */
    switch (state)
    {
		case MAV_STATE_UNINIT:
		{
			// Both rear blink together at 300 ms on/off (3.33 Hz)
			rg = rr = pulse_in_period(now, state_t0, 2 * UNINIT_HALF_PERIOD_MS, UNINIT_HALF_PERIOD_MS);
			break;
		}
		case MAV_STATE_STANDBY:
		{
			// Short green pulse (50 ms) every 1050 ms, red off
			rg = pulse_in_period(now, state_t0, STANDBY_PERIOD_MS, STANDBY_ON_MS);
			rr = 0;
			break;
		}
		case MAV_STATE_ACTIVE:
		{
			// Alternate green/red every 300 ms
			uint8_t first_half = pulse_in_period(now, state_t0, 2 * ACTIVE_HALF_PERIOD_MS, ACTIVE_HALF_PERIOD_MS);
			rg = first_half;
			rr = !first_half;
			break;
		}
		default:
			if (state >= MAV_STATE_CRITICAL)
			{
				// Red blinks at 5 Hz (200 ms on/off), green off
				rg = 0;
				rr = pulse_in_period(now, state_t0, 2 * CRITICAL_HALF_PERIOD_MS, CRITICAL_HALF_PERIOD_MS);
			}
			// else: leave rear LEDs as they were (matches your original 'default' behavior)
			break;
    }

    // Push rear outputs (only if they changed)
    set_pin_if_changed(gpio, LED_REAR_GEAR_GREEN_Pin, rg, &last_rear_green);
    set_pin_if_changed(gpio, LED_REAR_GEAR_RED_Pin,   rr, &last_rear_red);
}
/* ---------- MAVLink ---------- */
static void send_heartbeat(void)
{
	mavlink_message_t msg;
	uint8_t tx_frame[MAVLINK_MAX_PACKET_LEN];
	const uint8_t sysid = 1, compid = 1;

	mavlink_msg_heartbeat_pack(sysid, compid, &msg,
							 MAV_TYPE_GENERIC,
							 MAV_AUTOPILOT_GENERIC,
							 MAV_MODE_MANUAL_ARMED,
							 0,
							 MAV_STATE_ACTIVE);

	uint16_t len = mavlink_msg_to_send_buffer(tx_frame, &msg);
	for (uint16_t i = 0; i < len; i++)
	{
		RINGBUF_Put(&ui.ring_tx, tx_frame[i]);
	}
	ring_buffer_send_data();
}
static void mavlink_process(uint32_t now)
{
	update_leds_by_mav_state(mav.hb.system_status, now);
	while (RINGBUF_Get(&ui.ring, &ui.read_data) == RING_OK)
	{
		if (mavlink_parse_char(MAVLINK_COMM_0, ui.read_data, &mav.rx_msg, &mav.status))
		{
			switch (mav.rx_msg.msgid)
			{
				case MAVLINK_MSG_ID_HEARTBEAT:
				{
					mavlink_msg_heartbeat_decode(&mav.rx_msg, &mav.hb);

					if (last_heartbeat_time != 0)
					{
						heartbeat_period_ms = now - last_heartbeat_time;
						if (heartbeat_period_ms > 0)
						{
							heartbeat_freq_hz = 1000.0f / (float)heartbeat_period_ms;
						}
					}
					last_heartbeat_time = now;
					break;
				}

                case MAVLINK_MSG_ID_ATTITUDE:
                {
                    mavlink_attitude_t att;
                    mavlink_msg_attitude_decode(&mav.rx_msg, &att);
                    att_roll    = att.roll;   // rad
                    att_pitch   = att.pitch;  // rad
                    att_last_ms = now;
                    break;
                }

				default:
					break;
			}
		}
	}
}

/* ---------- App loop ---------- */
void ui_handle(void)
{
	static uint32_t t_hb = 0;
	if (HAL_GetTick() - t_hb > 1000)
	{
		send_heartbeat();
		t_hb = HAL_GetTick();
	}
	mavlink_process(HAL_GetTick());
}

/*--------- App Init ---------*/
void ui_init(GPIO_TypeDef* gpio_x)
{
	memset(&ui, 0, sizeof(ui));
	ui.uart_tx_busy = 0;
	RINGBUF_Init(&ui.ring, ui.ring_buf, sizeof(ui.ring_buf));
	RINGBUF_Init(&ui.ring_tx, ui.ring_buf_tx, sizeof(ui.ring_buf_tx));
	HAL_UART_Receive_IT(&huart2, &ui.rx_byte, 1);
	gpio = gpio_x;
}
