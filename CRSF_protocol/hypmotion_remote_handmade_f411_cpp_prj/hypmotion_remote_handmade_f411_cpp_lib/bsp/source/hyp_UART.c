/**
  ******************************************************************************
  * @file    hyp_UART.c
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
/* Includes ------------------------------------------------------------------*/
#include <bsp/include/hyp_UART.h>
#include <common/include/hyp_ringbuffer.h>

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static UART_HandleTypeDef	*huart_handle = NULL;

/* Private function prototypes -----------------------------------------------*/
/* @brief: This function used for hyp bsp uart ring buffer write
 * @return: value 16 bits
 * */
uint16_t hypmotion_bsp_uart_ringbuffer_write(hyp_bsp_uart_t *handle, const uint8_t *data, uint16_t len)
{
	uint16_t i;

	for(i = 0; i < len; i++)
	{
		uint16_t next = (handle->ringbuffer.head + 1) % BUFFER_SIZE;

		if(next == handle->ringbuffer.tail) break; // Buffer full

		handle->ringbuffer.buffer[handle->ringbuffer.head] = data[i];

		handle->ringbuffer.head = next;
	}

	return i;
}


/* @brief: This function used for hyp bsp uart ring buffer read
 * @return: value 16 bits
 * */
uint16_t hypmotion_bsp_uart_ringbuffer_read(hyp_bsp_uart_t *handle, uint8_t *data, uint16_t len)
{
	uint16_t i;

	for(i = 0; i < len; i++)
	{
		if(handle->ringbuffer.tail == handle->ringbuffer.head) break; // buffer empty

		data[i] = handle->ringbuffer.buffer[handle->ringbuffer.tail];

		handle->ringbuffer.tail = (handle->ringbuffer.tail + 1) % BUFFER_SIZE;
	}

	return i;
}


/* @brief: This function used for hyp bsp uart ring buffer avaiable
 * @return: value 16 bits
 * */
uint16_t hypmotion_bsp_uart_ringbuffer_available(hyp_bsp_uart_t *handle)
{
	return (BUFFER_SIZE + handle->ringbuffer.head - handle->ringbuffer.tail) % BUFFER_SIZE;
}


/* @brief: This function used for hyp bsp uart ring buffer space
 * @return: value 16 bits
 * */
uint16_t hypmotion_bsp_uart_ringbuffer_space(hyp_bsp_uart_t *handle)
{
	return (BUFFER_SIZE - hypmotion_bsp_uart_ringbuffer_available(handle) - 1);
}


/* @brief: This function used for hyp bsp uart ring buffer avaiable
 * @return: value 16 bits
 * */
uint16_t hypmotion_bsp_uart_ringbuffer_space(hyp_bsp_uart_t *handle);

/* @brief: This function used for hyp bsp uart initial
 * @return: hypmotion system return code
 * */
E_HYP_ReturnCode hypmotion_bsp_uart_initialize(hyp_bsp_uart_t *handle)
{
	if(handle == NULL) return HYP_SYSTEM_RETURN_CODE_POINTER_IS_NULL;

	/* Assign pointer */
	handle->hyp_uart_receiveDMA  = HAL_UART_Receive_DMA;
	handle->hyp_uart_transmitDMA = HAL_UART_Transmit_DMA;

	handle->ringbuffer.head = 0;
	handle->ringbuffer.tail = 0;


	return HYP_SYSTEM_RETURN_CODE_SUCCESS;
}
