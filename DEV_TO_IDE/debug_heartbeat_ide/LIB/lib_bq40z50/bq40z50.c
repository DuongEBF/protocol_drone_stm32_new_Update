#include "bq40z50.h"
static I2C_HandleTypeDef* bq40z50_i2c;

void BQ40Z50_Init(I2C_HandleTypeDef* i2c)
{
	bq40z50_i2c = i2c;
}
HAL_StatusTypeDef bq40z50_read_u8(uint8_t cmd, uint8_t* data)
{
	return HAL_I2C_Mem_Read(bq40z50_i2c, BQ40Z50_ADDR, cmd, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);
}

HAL_StatusTypeDef bq40z50_read_u16(uint8_t cmd, uint16_t* data)
{
	uint8_t buf[2];
	HAL_StatusTypeDef ret = HAL_I2C_Mem_Read(bq40z50_i2c, BQ40Z50_ADDR, cmd, I2C_MEMADD_SIZE_8BIT, buf, 2, HAL_MAX_DELAY);
	if (ret == HAL_OK)
	{
			*data = (buf[1] << 8) | buf[0];
	}
	return ret;
}

HAL_StatusTypeDef bq40z50_read_i16(uint8_t cmd, int16_t* data)
{
	uint8_t buf[2];
	HAL_StatusTypeDef ret = HAL_I2C_Mem_Read(bq40z50_i2c, BQ40Z50_ADDR, cmd, I2C_MEMADD_SIZE_8BIT, buf, 2, HAL_MAX_DELAY);
	if (ret == HAL_OK)
	{
			*data = (int16_t)((buf[1] << 8) | buf[0]);
	}
	return ret;
}

HAL_StatusTypeDef BQ40Z50_ReadAll(infor_bq40z50_t* info)
{
	HAL_StatusTypeDef status = HAL_OK;

	status |= bq40z50_read_u8(0x0D, &info->soc);  // SOC %
	status |= bq40z50_read_u16(0x09, &info->volt); // Voltage mV
	status |= bq40z50_read_i16(0x0A, &info->current); // Current mA

	uint16_t temp_raw;
	status |= bq40z50_read_u16(0x08, &temp_raw); // Temperature (0.1 K)
	info->temperature_celsius = ((float)temp_raw * 0.1f) - 273.15f;

	status |= bq40z50_read_u16(0x0F, &info->remaining_capacity); // mAh
	status |= bq40z50_read_u16(0x10, &info->full_charge_capacity); // mAh

	return status;
}