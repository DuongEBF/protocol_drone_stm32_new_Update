/*
 * uart_irq.h
 *
 *  Created on: Aug 13, 2025
 *      Author: duong
 */

#ifndef UART_IRQ_UART_IRQ_H_
#define UART_IRQ_UART_IRQ_H_
#include "main.h"
void uart_init_fc(void);
void uart_init_tobufi(void);

uint8_t uart_read_tobufi(void);
uint8_t uart_read_fc(void);

uint16_t uart_available_tobufi(void);
uint16_t uart_available_fc(void);


void receive_rx_tobufi(uint8_t data_rx);
void receive_rx_fc(uint8_t data_rx);

#endif /* UART_IRQ_UART_IRQ_H_ */
