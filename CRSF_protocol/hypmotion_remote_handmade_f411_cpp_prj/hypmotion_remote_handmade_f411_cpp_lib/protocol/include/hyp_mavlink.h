/**
  ******************************************************************************
  * @file    hypmotion_mavlink.h
  * @author  HYPMOTION Firmware Team
  * @version V2.0.0
  * @date    ${date}
  * @brief   This file contains all the functions prototypes for the hypmotion_application.c
  *          firmware library
  *
  ******************************************************************************
  * @Copyright
  * COPYRIGHT NOTICE: (c) 2024 HYPMOTION. All rights reserved.
  *
  * The information contained herein is confidential
  * property of Company. The use, copying, transfer or
  * disclosure of such information is prohibited except
  * by express written agreement with Company.
  *
  ******************************************************************************
*/

#ifndef HYPMOTION_MAVLINK_PROTOCOL_H_
#define HYPMOTION_MAVLINK_PROTOCOL_H_

#ifdef __cplusplus
extern "C" {
#endif

/*Includes-----------------------------------------------------------*/
#include "protocol/mavlink/common/mavlink.h"
#include <common/include/hyp_ringbuffer.h>
#include <module/include/hyp_joystick.h>
#include <common/include/hyp_common.h>
#include <bsp/include/hyp_UART.h>

/*Private Defines ----------------------------------------------------*/
#define SYSTEM_ID			10
#define MAVLINK_CHANNEL		MAVLINK_COMM_0


#define TX_BUFF_SIZE		256
#define RX_BUFF_SIZE		256
/*STRUCTURE-----------------------------------------------------------*/
typedef struct _T_MAVLINK_TIME_TX
{
	uint32_t timeMS;
	uint32_t timeSendHeartBeat;
	uint32_t timeSendRCchannels;
	uint32_t timeSendDataRequest;
	uint32_t timeSendBatteryStatus;
	uint32_t timeSendDataRqRcChannels;
	uint32_t timeCount;

}mavlink_time_tx_t;

typedef struct
{
    uint32_t heartbeat_count;
    uint32_t attitude_count;
    uint32_t rc_channels_count;

    float heartbeat_frequency;
    float attitude_frequency;
    float rc_channels_frequency;


    uint32_t time_current;
    uint32_t last_time;

} hyp_mavlink_frequency_t;

typedef struct __T_COUNT_MSG
{
	uint16_t	msgCountHeartbeat_temp;
	uint16_t	msgCountHeartbeat;

	uint16_t 	msgCountRequestStream_temp;
	uint16_t 	msgCountRequestStream;

}mavlink_count_msg_t;

typedef struct _T_MAVLINK_TX
{
	mavlink_heartbeat_t 			tx_heartbeat;
	mavlink_rc_channels_override_t	rc_channels_override;
	mavlink_rc_channels_t 			rc_channels;
	RingBuffer						tx_ringbuffer;
	mavlink_count_msg_t				tx_count;
	mavlink_time_tx_t				tx_time;
	uint8_t							tx_Buf[TX_BUFF_SIZE];

}mavlink_tx_t;

typedef struct _T_MAVLINK_RX
{
	mavlink_heartbeat_t 			rx_heartbeat;
	mavlink_message_t				rx_msg;
	uint8_t							rx_Buf[RX_BUFF_SIZE];

}mavlink_rx_t;

typedef struct
{
    uint8_t 	reverse;
    uint8_t 	hardware;
    uint16_t 	max_value;
    uint16_t 	min_value;

}DecodedParam;

typedef struct _T_EEPROM_DEBUG
{
	DecodedParam 	eeprom_channel;
	uint16_t 		eeprom_trim;

}Eeprom_debug_t;


typedef struct
{
//    bool param_request_list_flag;
    bool param_request_read_flag;
    bool param_set_value_flag;
    bool heartbeat_flag;
    bool command_long_flag;

}flag_t;


typedef struct __T_Hypmotion_Mavlink
{
	flag_t 								flags;
	mavlink_tx_t						tx_mavlink;
	mavlink_rx_t						rx_mavlink;
	hyp_mavlink_frequency_t				mavlink_frequency;

	hyp_joystick_t						*joystick;

	hyp_osThread_inFo_t					ID;

	uint32_t							lastTimeHeartBeat;
	uint8_t								connectionLost;

//	hyp_bsp_uart_t						*uart;

	E_HYP_ReturnCode 					returnCode;

	UART_HandleTypeDef					*uartHandle;

	HAL_StatusTypeDef (*hyp_uart_transmitDMA)(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t size);
	HAL_StatusTypeDef (*hyp_uart_receiveDMA)(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t size);

}hyp_mavlink_t;

/*FUNCTION-----------------------------------------------------------*/
/** @brief      This function use for UART_1 DMA Receive
	@return       no return
*/
void UART1_DMA_Receive(void);

/** @brief      This function use for UART_3 DMA Receive
	@return       no return
*/
void UART3_DMA_Receive(void);

/** @brief      This function use for send mavlink heartbeat to HYPTX APP
	@return       no return
*/
//void mavlink_send_heartbeat(mavlink_channel_t channel, uint8_t base_mode);

/** @brief      This function use for send mavlink heartbeat to microhard
	@return       no return
*/
void mavlink_send_heartbeat_microhard(void);

/** @brief      This function use for send param value to HYPTX APP
	@return       no return
*/
void mavlink_send_param_value(mavlink_channel_t channel, mavlink_param_value_t *param_value);

/** @brief      This function use for send rc channels to HYPTX APP
	@return       no return
*/
void mavlink_send_ID_RC_Channels(mavlink_channel_t channel);

/** @brief      This function use for send rc channels to microhard
	@return       no return
*/
void mavlink_send_ID_RC_Channels_Microhard(mavlink_channel_t channel);

/** @brief      This function use for calib joystick on HYPTX APP
	@return       no return
*/
void HYP_Calib_Joystick();

/** @brief      This function use for handle message mavlink command long from HYPTX APP
	@return       no return
*/
void handle_command_long();

/** @brief      This function use for process param set from HYPTX APP
	@return       no return
*/
void process_param_set(mavlink_param_set_t *param_set);

/** @brief      This function use for process param request read from HYPTX APP
	@return       no return
*/
void process_param_request_read(mavlink_param_request_read_t *param_request_read);

/** @brief      This function use for process param request list from HYPTX APP
	@return       no return
*/
void process_param_request_list(mavlink_param_request_list_t *param_request_list);

/** @brief      This function use for handle message receive from HYPTX APP
	@return       no return
*/
void handle_param_mavlink();

/** @brief      This function use for handle message transmit to HYPTX APP
	@return       no return
*/
void handle_message_transmission_mavlink();

/** @brief      This function use for handle message transmit to microhard
	@return       no return
*/
void handle_message_transmission_mavlink_microhard();

/** @brief      This function use for send message to HYPTX APP and microhard
	@return       no return
*/
void send_mavlink_message(void);

/*--------------------------------------main functions--------------------------------------------*/
/** @brief      This function use for init mavlink protocol
	@return       no return
*/
E_HYP_ReturnCode hyp_mavlink_initialize(hyp_mavlink_t *handle);

/** @brief      This function use for process mavlink protocol
	@return       no return
*/
E_HYP_ReturnCode hyp_mavlink_process(hyp_mavlink_t *handle);


#ifdef __cplusplus
}
#endif // extern "C"

#endif /*HYPMOTION_MAVLINK_PROTOCOL_H_*/

/************************ (C) COPYRIGHT HYPMOTION *****END OF FILE****************/
