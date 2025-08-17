#include "uart.h"
#include "command_excute.h"
#include "stdio.h"
uint8_t data_rx;
uint8_t buff_uart[BUFFER_UART];
uint8_t index_uart = 0;
UART_HandleTypeDef* hyp_uart;
uint8_t flag_uart = 0;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == hyp_uart->Instance)
	{
		buff_uart[index_uart++] = data_rx;
		if(data_rx == '\n')
		{
			flag_uart = 1;
		}
		HAL_UART_Receive_IT(hyp_uart, &data_rx, 1);
	}
}
void uart_handle(void)
{
	//command_excute((char*)buff_uart, sizeof(buff_uart));
	if(flag_uart)
	{
	    for(int i = 0; i < index_uart; i++)
	    {
	        char temp[10];
	        sprintf(temp, "%d ", buff_uart[i]);
	        HAL_UART_Transmit(hyp_uart, (uint8_t*)temp, strlen(temp), HAL_MAX_DELAY);
	    }
	    HAL_UART_Transmit(hyp_uart, (uint8_t*)"\r\n", 2, HAL_MAX_DELAY);

	    command_excute((char*)buff_uart);
	    memset(buff_uart, 0, index_uart);
	    index_uart = 0;
	    flag_uart = 0;
	}
}
void uart_init(UART_HandleTypeDef *huart)
{
	hyp_uart = huart;
	HAL_UART_Receive_IT(hyp_uart, &data_rx, 1);
}
