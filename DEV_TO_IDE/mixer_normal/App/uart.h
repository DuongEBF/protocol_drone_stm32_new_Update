#ifndef __UART_H
#define __UART_H
#include "main.h"
#include "string.h"
#define BUFFER_UART 128

extern uint8_t data_rx;
extern uint8_t buff_uart[BUFFER_UART];
extern uint8_t index_uart;
extern UART_HandleTypeDef* hyp_uart;
void uart_init(UART_HandleTypeDef *huart);
void uart_handle(void);
#endif