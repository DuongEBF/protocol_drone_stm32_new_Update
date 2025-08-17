/**
  ******************************************************************************
  * @file    hyp_UART.h
  * @author  HYPMOTION Firmware Team
  * @version V2.0.0
  * @date    ${date}
  * @brief   This file contains all the functions prototypes for the hypmotion_common.c
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef BSP_INCLUDE_HYP_UART_H_
#define BSP_INCLUDE_HYP_UART_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "common/include/hyp_common.h"

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#define HYP_UART_TX_BUFFER		256
#define HYP_UART_RX_BUFFER		256
#define	BUFFER_SIZE				256

/* Exported types ------------------------------------------------------------*/
typedef struct
{
	uint8_t 			buffer[BUFFER_SIZE];

	volatile uint16_t	head;

	volatile uint16_t	tail;

}hyp_ringbuffer_t;

typedef struct __T_HYPMOTION_BSP_UART
{
	UART_HandleTypeDef					*uartHandle;

	hyp_ringbuffer_t					ringbuffer;

	HAL_StatusTypeDef (*hyp_uart_transmitDMA)(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t size);
	HAL_StatusTypeDef (*hyp_uart_receiveDMA)(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t size);

	E_HYP_ReturnCode 					returnCode;

}hyp_bsp_uart_t;

/* Exported functions --------------------------------------------------------*/
uint16_t hypmotion_bsp_uart_ringbuffer_write(hyp_bsp_uart_t *handle, const uint8_t *data, uint16_t len);

uint16_t hypmotion_bsp_uart_ringbuffer_read(hyp_bsp_uart_t *handle, uint8_t *data, uint16_t len);

uint16_t hypmotion_bsp_uart_ringbuffer_available(hyp_bsp_uart_t *handle);

uint16_t hypmotion_bsp_uart_ringbuffer_space(hyp_bsp_uart_t *handle);

E_HYP_ReturnCode hypmotion_bsp_uart_initialize(hyp_bsp_uart_t *handle);

E_HYP_ReturnCode hypmotion_bsp_uart_process(hyp_bsp_uart_t *handle);

#ifdef __cplusplus
}
#endif // extern "C"

#endif /* BSP_INCLUDE_HYP_UART_H_ */

/************************ (C) COPYRIGHT HYPMOTION *****END OF FILE****************/
