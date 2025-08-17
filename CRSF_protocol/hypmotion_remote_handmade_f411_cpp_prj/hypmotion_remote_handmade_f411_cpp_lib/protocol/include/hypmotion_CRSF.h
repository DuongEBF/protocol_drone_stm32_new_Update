/**
  ******************************************************************************
  * @file    hypmotion_CRSF.h
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
#ifndef PROTOCOL_INCLUDE_HYPMOTION_CRSF_H_
#define PROTOCOL_INCLUDE_HYPMOTION_CRSF_H_

#ifdef __cplusplus
extern "C" {
#endif

/*Include-----------------------------------------------------------*/
#include <common/include/hyp_common.h>
#include <module/include/hyp_joystick.h>
#include <bsp/include/hyp_UART.h>

/*Define -----------------------------------------------------------*/
#define ADC_VALUE_MIN			1000
#define ADC_VALUE_MAX			3000

#define CRSF_VALUE_MIN			172
#define CRSF_VALUE_MAX			1811

/*Typedef-----------------------------------------------------------*/
typedef struct
{
	uint32_t 	timeSendCRSF;
	uint32_t 	elapseTimeSendCRSF;

}time_send_crsf_protocol_t;

typedef struct __T_HYPMOTION_CRSF_PROTOCOL
{
	uint8_t 							crsf_frame[26];  // full frame

	uint16_t 							ch[16];         // input RC channel values (0–2047)

	time_send_crsf_protocol_t			time;

	hyp_osThread_inFo_t					ID;

	hyp_joystick_t						*joystick;

	hyp_bsp_uart_t						*uart;

	E_HYP_ReturnCode 					returnCode;

//	UART_HandleTypeDef					*uartHandle;
//
//	HAL_StatusTypeDef (*hyp_uart_transmitDMA)(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t size);
//	HAL_StatusTypeDef (*hyp_uart_receiveDMA)(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t size);

}hypmotion_crsf_protocol_t;

/*Function-----------------------------------------------------------*/
E_HYP_ReturnCode hypmotion_crsf_protocol_initialize(hypmotion_crsf_protocol_t *handle);

E_HYP_ReturnCode hypmotion_crsf_protocol_process(hypmotion_crsf_protocol_t *handle);

#ifdef __cplusplus
}
#endif // extern "C"

#endif /* PROTOCOL_INCLUDE_HYPMOTION_CRSF_H_ */

/************************ (C) COPYRIGHT HYPMOTION *****END OF FILE****************/

