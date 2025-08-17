/*
 * UI.h
 *
 *  Created on: Aug 7, 2025
 *      Author: duong
 */

#ifndef UI_UI_H_
#define UI_UI_H_
#include "main.h"
#include "common/mavlink.h"
#include "ring.h"
typedef struct
{
	RINGBUF ring;
	RINGBUF ring_tx;
	uint8_t ring_buf[1000];
	uint8_t ring_buf_tx[256];
	uint8_t rx_byte;
	uint8_t read_data;
	volatile uint8_t uart_tx_busy;
}ui_rw_t;
typedef struct
{
	mavlink_message_t rx_msg;
	mavlink_status_t status;
	mavlink_heartbeat_t hb;
}mavlink_ui_t;
void ui_handle(void);
void ui_init(GPIO_TypeDef* gpio_x);
#endif /* UI_UI_H_ */
