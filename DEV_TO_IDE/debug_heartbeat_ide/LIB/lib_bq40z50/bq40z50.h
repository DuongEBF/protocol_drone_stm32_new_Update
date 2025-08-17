#ifndef _BQ40Z50_H
#define _BQ40Z50_H
#include "main.h"
#define BQ40Z50_ADDR  (0x0B << 1)
typedef struct
{
	uint8_t soc;
	uint16_t volt;
	int16_t current;
	float temperature_celsius;
	uint16_t remaining_capacity;
	uint16_t full_charge_capacity;
}infor_bq40z50_t;

void BQ40Z50_Init(I2C_HandleTypeDef* i2c);
HAL_StatusTypeDef bq40z50_read_u8(uint8_t cmd, uint8_t* data);
HAL_StatusTypeDef bq40z50_read_u16(uint8_t cmd, uint16_t* data);
HAL_StatusTypeDef bq40z50_read_i16(uint8_t cmd, int16_t* data);
HAL_StatusTypeDef BQ40Z50_ReadAll(infor_bq40z50_t* info);
#endif