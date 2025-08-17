/**
  ******************************************************************************
  * @file    hyp_mavlink.c
  * @author  HYPMOTION Firmware Team
  * @version V1.0.0
  * @date    ${date}
  * @brief
  *
  ******************************************************************************
  * @Copyright
  * COPYRIGHT NOTICE: (c) ${year} NST.
  * All rights reserved.
  *
  * The information contained herein is confidential
  * property of Company. The use, copying, transfer or
  * disclosure of such information is prohibited except
  * by express written agreement with Company.
  *
  ******************************************************************************
*/

/*INCLUDE--------------------------------------------------------------------------*/
#include <protocol/include/hyp_mavlink.h>

/*VARIABLE--------------------------------------------------------------------------*/

/*UART BOARD SUPPORT*/
extern UART_HandleTypeDef huart6;

extern DMA_HandleTypeDef hdma_usart6_rx;
extern DMA_HandleTypeDef hdma_usart6_tx;

static hyp_mavlink_t 	*pMAVLink;

/*FUNCTION-----------------------------------------------------------------------------------*/
static void _calculator_mavlink_frequency(hyp_mavlink_frequency_t *handle)
{
	handle->time_current = hyp_getTimeMS();

	if(handle->time_current - handle->last_time >= 1000)
	{
		/* Update last time */
		handle->last_time = handle->time_current;

		/* Calculator frequency */
		handle->heartbeat_frequency = handle->heartbeat_count / 1.0f;

		/* Reset count */
		handle->heartbeat_count = 0;
	}
}


E_HYP_ReturnCode _hyp_mavlink_check_lost_connection(hyp_mavlink_t *handle)
{
	if(handle == NULL)  return HYP_SYSTEM_RETURN_CODE_POINTER_IS_NULL;

	if(handle->connectionLost == 0 && (hyp_getTimeMS() - handle->lastTimeHeartBeat >= 3000))
	{
		handle->connectionLost = 1;

		return HYP_SYSTEM_RETURN_CODE_MAVLINK_IS_LOST_CONNECTION;
	}

	return HYP_SYSTEM_RETURN_CODE_MAVLINK_OK;
}


//E_HYP_ReturnCode _hyp_mavlink_handle_lost_connection(hyp_mavlink_t *handle)
//{
//	if(handle == NULL) return HYP_SYSTEM_RETURN_CODE_POINTER_IS_NULL;
//
//	if(_hyp_mavlink_check_lost_connection(handle) == HYP_SYSTEM_RETURN_CODE_MAVLINK_IS_LOST_CONNECTION)
//	{
//		// Stop UART DMA
//		HAL_UART_DMAStop(handle->uartHandle);
//
//		// Deinit UART
//		HAL_UART_DeInit(handle->uartHandle);
//
//
//		if(HAL_UART_Init(handle->uartHandle) != HAL_OK)
//		{
//			return HYP_SYSTEM_RETURN_CODE_ERROR;
//		}
//
//		handle->mavlink_frequency.time_current = 0;
//		handle->mavlink_frequency.last_time = 0;
//
//		RingBuffer_Init(&handle->tx_mavlink.tx_ringbuffer);
//
//		if(handle->hyp_uart_receiveDMA(handle->uartHandle, handle->rx_mavlink.rx_Buf, RX_BUFF_SIZE) == HAL_OK)
//		{
//			return HYP_SYSTEM_RETURN_CODE_MAVLINK_OK;
//		}
//	}
//	else
//	{
//		return HYP_SYSTEM_RETURN_CODE_SUCCESS;
//	}
//
//	return HYP_SYSTEM_RETURN_CODE_MAVLINK_IS_LOST_CONNECTION;
//}


static void _hyp_mavlink_message_send_heartbeat_toDrone(hyp_mavlink_t *handle)
{
//	uint8_t system_id 	= SYSTEM_ID;
//	uint8_t comp_id 	= MAV_COMP_ID_PERIPHERAL;
//	uint8_t chan		= MAVLINK_CHANNEL;

	uint8_t system_id 	= 1;
	uint8_t comp_id 	= MAV_COMP_ID_AUTOPILOT1;
	uint8_t chan		= MAVLINK_COMM_0;


	handle->tx_mavlink.tx_heartbeat.autopilot 		= MAV_AUTOPILOT_GENERIC;
	handle->tx_mavlink.tx_heartbeat.system_status	= 0;
	handle->tx_mavlink.tx_heartbeat.base_mode		= 0;
	handle->tx_mavlink.tx_heartbeat.type			= MAV_TYPE_QUADROTOR;

	mavlink_message_t tx_msg = {0};

	mavlink_msg_heartbeat_encode_chan(system_id,
									  comp_id,
									  chan,
								      &tx_msg,
									  &handle->tx_mavlink.tx_heartbeat);

	uint16_t 	len = 0;
	uint8_t 	msgBuf[TX_BUFF_SIZE];

	memset(msgBuf, 0x00, TX_BUFF_SIZE);

	len = mavlink_msg_to_send_buffer(msgBuf, &tx_msg);

	RingBuffer_Write(&handle->tx_mavlink.tx_ringbuffer, msgBuf, len);
//	hypmotion_bsp_uart_ringbuffer_write(handle->uart, msgBuf, len);

	// Calculator MAVLink frequency
	handle->tx_mavlink.tx_count.msgCountHeartbeat_temp++;
}


/** @brief      This function use for send rc channels to HYPTX APP
	@return       no return
*/
E_HYP_ReturnCode hyp_mavlink_send_ID_RCChannels_toDrone(hyp_mavlink_t *handle)
{
	if(handle == NULL) return HYP_SYSTEM_RETURN_CODE_POINTER_IS_NULL;

	hyp_joystick_t	*Joystick = handle->joystick;

//	mavlink_rc_channels_t rc_channels;

	uint8_t systemid 	= 10;
	uint8_t compid 		= MAV_COMP_ID_PERIPHERAL;
	uint8_t chan		= MAVLINK_COMM_0;

	uint16_t flight_mode;
	if(Joystick->button.button_3 == GPIO_PIN_SET && Joystick->button.button_4 == GPIO_PIN_SET)
	{
		flight_mode = 1500;
	}
	else if(Joystick->button.button_3 == GPIO_PIN_SET && Joystick->button.button_4 == GPIO_PIN_RESET)
	{
		flight_mode = 1000;
	}
	else if(Joystick->button.button_3 == GPIO_PIN_RESET && Joystick->button.button_4 == GPIO_PIN_SET)
	{
		flight_mode = 2000;
	}

	handle->tx_mavlink.rc_channels.chan1_raw  = map(Joystick->hypmotion_adc.adc_lowpass.adc_value_1, 3000, 1000, 1000, 2000);
	handle->tx_mavlink.rc_channels.chan2_raw  = map(Joystick->hypmotion_adc.adc_lowpass.adc_value_0, 1000, 3000, 1000, 2000);
	handle->tx_mavlink.rc_channels.chan3_raw  = map(Joystick->hypmotion_adc.adc_lowpass.adc_value_3, 3100, 1000, 1000, 2000);
	handle->tx_mavlink.rc_channels.chan4_raw  = map(Joystick->hypmotion_adc.adc_lowpass.adc_value_2, 3000, 1000, 1000, 2000);
	handle->tx_mavlink.rc_channels.chan5_raw  = flight_mode;
	handle->tx_mavlink.rc_channels.chan6_raw  = 1500;
	handle->tx_mavlink.rc_channels.chan7_raw  = 1500;
	handle->tx_mavlink.rc_channels.chan8_raw  = 1500;
	handle->tx_mavlink.rc_channels.chan9_raw  = 1500;
	handle->tx_mavlink.rc_channels.chan10_raw = 1500;
	handle->tx_mavlink.rc_channels.chan11_raw = map(Joystick->button.button_1, 1, 0, 1000, 2000);
	handle->tx_mavlink.rc_channels.chan12_raw = 1500;
	handle->tx_mavlink.rc_channels.chan13_raw = 1500;
	handle->tx_mavlink.rc_channels.chan14_raw = 1500;
	handle->tx_mavlink.rc_channels.chan15_raw = 1500;
	handle->tx_mavlink.rc_channels.chan16_raw = 1500;
	handle->tx_mavlink.rc_channels.chan17_raw = 1500;
	handle->tx_mavlink.rc_channels.chan18_raw = 1500;


	handle->tx_mavlink.rc_channels.chancount = 18;
	handle->tx_mavlink.rc_channels.rssi = 255; // Giá trị RSSI (chất lượng tín hiệu)
	handle->tx_mavlink.rc_channels.time_boot_ms = HAL_GetTick();

	mavlink_message_t message_tx;
	mavlink_msg_rc_channels_encode_chan(systemid,
										compid,
										chan,
										&message_tx,
										&handle->tx_mavlink.rc_channels);

	uint16_t len = 0;
	uint8_t msgbuf[MAVLINK_MAX_PACKET_LEN];

	/*!< Clear buffer */
	memset(msgbuf, 0x00, MAVLINK_MAX_PACKET_LEN);

	len = mavlink_msg_to_send_buffer(msgbuf, &message_tx);

	RingBuffer_Write(&handle->tx_mavlink.tx_ringbuffer, msgbuf, len);
//	hypmotion_bsp_uart_ringbuffer_write(handle->uart, msgbuf, len);

	return HYP_SYSTEM_RETURN_CODE_SUCCESS;
}

/** @brief      This function use for send rc channels to HYPTX APP
	@return       no return
*/
E_HYP_ReturnCode hyp_mavlink_send_ID_RCChannels_OverRide_toDrone(hyp_mavlink_t *handle)
{
	if(handle == NULL) return HYP_SYSTEM_RETURN_CODE_POINTER_IS_NULL;

	hyp_joystick_t	*Joystick = handle->joystick;

//	mavlink_rc_channels_override_t	rc_channels_override;

	uint8_t systemid 	= 255;
	uint8_t compid 		= MAV_COMP_ID_ALL;
	uint8_t chan		= MAVLINK_COMM_0;

	uint16_t flight_mode;
	if(Joystick->button.button_3 == GPIO_PIN_SET && Joystick->button.button_4 == GPIO_PIN_SET)
	{
		flight_mode = 1500;
	}
	else if(Joystick->button.button_3 == GPIO_PIN_SET && Joystick->button.button_4 == GPIO_PIN_RESET)
	{
		flight_mode = 1000;
	}
	else if(Joystick->button.button_3 == GPIO_PIN_RESET && Joystick->button.button_4 == GPIO_PIN_SET)
	{
		flight_mode = 2000;
	}
	handle->tx_mavlink.rc_channels_override.chan1_raw  = map(Joystick->hypmotion_adc.adc_lowpass.adc_value_1, 3200, 800, 1000, 2000);
	handle->tx_mavlink.rc_channels_override.chan2_raw  = map(Joystick->hypmotion_adc.adc_lowpass.adc_value_0, 1100, 3400, 1000, 2000);
	handle->tx_mavlink.rc_channels_override.chan3_raw  = map(Joystick->hypmotion_adc.adc_lowpass.adc_value_3, 3200, 800, 1000, 2000);
	handle->tx_mavlink.rc_channels_override.chan4_raw  = map(Joystick->hypmotion_adc.adc_lowpass.adc_value_2, 3200, 800, 1000, 2000);
	handle->tx_mavlink.rc_channels_override.chan5_raw  = flight_mode;
	handle->tx_mavlink.rc_channels_override.chan6_raw  = 1500;
	handle->tx_mavlink.rc_channels_override.chan7_raw  = 1500;
	handle->tx_mavlink.rc_channels_override.chan8_raw  = 1500;
	handle->tx_mavlink.rc_channels_override.chan9_raw  = 1500;
	handle->tx_mavlink.rc_channels_override.chan10_raw = 1500;
	handle->tx_mavlink.rc_channels_override.chan11_raw = map(Joystick->button.button_1, 1, 0, 1000, 2000);
	handle->tx_mavlink.rc_channels_override.chan12_raw = 1500;
	handle->tx_mavlink.rc_channels_override.chan13_raw = 1500;
	handle->tx_mavlink.rc_channels_override.chan14_raw = 1500;
	handle->tx_mavlink.rc_channels_override.chan15_raw = 1500;
	handle->tx_mavlink.rc_channels_override.chan16_raw = 1500;
	handle->tx_mavlink.rc_channels_override.chan17_raw = 1500;
	handle->tx_mavlink.rc_channels_override.chan18_raw = 1500;

	handle->tx_mavlink.rc_channels_override.target_system 		= 0;
	handle->tx_mavlink.rc_channels_override.target_component 	= 0;


	mavlink_message_t message_tx;
	mavlink_msg_rc_channels_override_encode_chan(systemid,
												compid,
												chan,
												&message_tx,
												&handle->tx_mavlink.rc_channels_override);

	uint16_t len = 0;
	uint8_t msgbuf[MAVLINK_MAX_PACKET_LEN];

	/*!< Clear buffer */
	memset(msgbuf, 0x00, MAVLINK_MAX_PACKET_LEN);

	len = mavlink_msg_to_send_buffer(msgbuf, &message_tx);

	RingBuffer_Write(&handle->tx_mavlink.tx_ringbuffer, msgbuf, len);
//	hypmotion_bsp_uart_ringbuffer_write(handle->uart, msgbuf, len);

	return HYP_SYSTEM_RETURN_CODE_SUCCESS;
}


E_HYP_ReturnCode hyp_mavlink_message_receive(hyp_mavlink_t *handle)
{
	if(handle == NULL) return HYP_SYSTEM_RETURN_CODE_POINTER_IS_NULL;

	hyp_mavlink_frequency_t *Frequency = &handle->mavlink_frequency;

	// Get new bytes
	static uint16_t prevRxIndex;

	uint16_t newRxIndex = RX_BUFF_SIZE - __HAL_DMA_GET_COUNTER(handle->uartHandle->hdmarx);

	uint16_t newBytes 	= 	(newRxIndex >= prevRxIndex) ?
							(newRxIndex - prevRxIndex) :
							(RX_BUFF_SIZE - prevRxIndex + newRxIndex);

	// Decode mavlink
	mavlink_message_t	rx_msg = {0};
	mavlink_status_t	rx_status;

	for(uint16_t i = 0; i < newBytes; i++)
	{
		uint8_t bufIndex = (prevRxIndex + i) % RX_BUFF_SIZE;

		if(mavlink_parse_char(MAVLINK_CHANNEL, handle->rx_mavlink.rx_Buf[bufIndex], &rx_msg, &rx_status))
		{
			if(rx_msg.sysid == 1)
			{

				switch(rx_msg.msgid)
				{

					case MAVLINK_MSG_ID_HEARTBEAT:
					{
						mavlink_msg_heartbeat_decode(&rx_msg, &handle->rx_mavlink.rx_heartbeat);

						Frequency->heartbeat_count++;

						handle->lastTimeHeartBeat = HAL_GetTick();

						if(handle->connectionLost == 1)
						{
							handle->connectionLost = 0;
						}

					}break;

				}
			}
		}
	}


    // update old byte
    prevRxIndex = newRxIndex;

    return HYP_SYSTEM_RETURN_CODE_MAVLINK_OK;
}

/*===============================================================
 *  						FreeRTOS
 * =============================================================*/
void hyp_MAVLinkTask(void const *argument)
{
	for(;;)
	{
		hyp_mavlink_process(pMAVLink);

		osDelay(1);
	}

}
/*---------------------------------------HYPMOTION FUNCTION----------------------------------------------*/
/** @brief      This function use for init mavlink protocol
	@return       no return
*/
E_HYP_ReturnCode hyp_mavlink_initialize(hyp_mavlink_t *handle)
{
	if(handle == NULL) return HYP_SYSTEM_RETURN_CODE_POINTER_IS_NULL;

	/* Assign pointer FreeRTOS */
	pMAVLink = handle;

	/* Assign function pointer */
	handle->uartHandle 				= &huart6;
	handle->hyp_uart_receiveDMA  	= HAL_UART_Receive_DMA;
	handle->hyp_uart_transmitDMA 	= HAL_UART_Transmit_DMA;

//	hypmotion_bsp_uart_initialize(handle->uart);
//
//	handle->uart->uartHandle 			= &huart6;
//	handle->uart->hyp_uart_receiveDMA   = HAL_UART_Receive_DMA;
//	handle->uart->hyp_uart_transmitDMA  = HAL_UART_Transmit_DMA;

	/* Value initialize */
	handle->lastTimeHeartBeat = 0;
	handle->connectionLost = 0;
	handle->mavlink_frequency.time_current = 0;
	handle->mavlink_frequency.last_time = 0;

	/* Init flags */
	handle->flags.heartbeat_flag = false;

	/* Ring Buffer initialization */
	RingBuffer_Init(&handle->tx_mavlink.tx_ringbuffer);

	/* Flush RX buffer to avoid corrupted data */
	memset(handle->rx_mavlink.rx_Buf, 0, RX_BUFF_SIZE);
	__HAL_UART_CLEAR_OREFLAG(handle->uartHandle); // Clear UART Overrun flag


	/* Delay 100 MS to wait the MAVLink bytes */
	osDelay(100);

	/* Receive data via UART by DMA circular */
	if(handle->hyp_uart_receiveDMA(handle->uartHandle, handle->rx_mavlink.rx_Buf, RX_BUFF_SIZE) != HAL_OK)
	{
		return HYP_SYSTEM_RETURN_CODE_COMM_INIT_FAILED;
	}

	/* Create MAVLink FreeRTOS Task */
	osThreadDef(MAVLinkTask, hyp_MAVLinkTask, osPriorityNormal, 0, 512);
	handle->ID.Id = osThreadCreate(osThread(MAVLinkTask), NULL);

	if(handle->ID.Id == NULL) return HYP_SYSTEM_RETURN_CODE_POINTER_IS_NULL;


	return HYP_SYSTEM_RETURN_CODE_SUCCESS;
}

/*
 *  @brief:     This function use for process mavlink protocol
 *  @return:      no return
*/
E_HYP_ReturnCode hyp_mavlink_process(hyp_mavlink_t *handle)
{
	if(handle == NULL) return HYP_SYSTEM_RETURN_CODE_POINTER_IS_NULL;

	/*--------------------------- Handle MAVLink lost connection -----------------------------*/
//	_hyp_mavlink_handle_lost_connection(handle);

	/*--------------------------- Process send MAVLink ----------------------------------- */
	mavlink_time_tx_t *time = &handle->tx_mavlink.tx_time;

	time->timeMS = hyp_getTimeMS();

	// Send MAVLink heart beat with 1 Hz
	if(time->timeMS - time->timeSendHeartBeat >= 1000)
	{
		time->timeSendHeartBeat = time->timeMS;

		_hyp_mavlink_message_send_heartbeat_toDrone(handle);

	}

	if(time->timeMS - time->timeSendRCchannels >= 2)
	{
		time->timeSendRCchannels = time->timeMS;

//		hyp_mavlink_send_ID_RCChannels_toDrone(handle);
		hyp_mavlink_send_ID_RCChannels_OverRide_toDrone(handle);

	}

	// Process ring buffer
	if(__HAL_DMA_GET_COUNTER(handle->uartHandle->hdmatx) == 0)
	{
		uint16_t len_read = RingBuffer_Read(&handle->tx_mavlink.tx_ringbuffer,
											handle->tx_mavlink.tx_Buf,
											TX_BUFF_SIZE);

//		uint16_t len_read = hypmotion_bsp_uart_ringbuffer_read(handle->uart,
//															   handle->tx_mavlink.tx_Buf,
//															   TX_BUFF_SIZE);

		if(len_read > 0)
		{
			handle->hyp_uart_transmitDMA(handle->uartHandle, handle->tx_mavlink.tx_Buf, len_read);
		}

	}

	/*--------------------------- Process receive MAVLink-----------------------------------*/
	hyp_mavlink_message_receive(handle);

	/*--------------------------- Compute MAVLink Frequency----------------------------------*/
	_calculator_mavlink_frequency(&handle->mavlink_frequency);


	return HYP_SYSTEM_RETURN_CODE_SUCCESS;
}

/************************ (C) COPYRIGHT HYPMOTION *****END OF FILE****************/
