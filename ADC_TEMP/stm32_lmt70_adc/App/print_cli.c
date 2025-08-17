#include "print_cli.h"
extern UART_HandleTypeDef huart5;
void print_cli(const char* str, ...)
{
	char stringArray[100];
	va_list args;
	va_start(args, str);
	uint8_t len_str = vsprintf(stringArray, str, args);
	va_end(args);
	HAL_UART_Transmit(&huart5, (uint8_t*)stringArray, len_str, 100);
}