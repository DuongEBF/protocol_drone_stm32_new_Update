#include "bq40z50.h"
static I2C_HandleTypeDef* bq40z50_i2c;
#define BQ40Z50_TIMEOUT 1000
void BQ40Z50_Init(I2C_HandleTypeDef* i2c)
{
	bq40z50_i2c = i2c;
}
void I2C_ClearBus(I2C_HandleTypeDef *i2c)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	// Ð?nh nghia chân SCL và SDA (thay d?i tùy theo hardware)-
	#define I2C_SCL_PIN   GPIO_PIN_6
	#define I2C_SDA_PIN   GPIO_PIN_7
	#define I2C_PORT      GPIOB

	// B?t clock GPIO
	__HAL_RCC_GPIOB_CLK_ENABLE();

	// Ð?t SCL và SDA thành Output Open-Drain
	GPIO_InitStruct.Pin = I2C_SCL_PIN | I2C_SDA_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(I2C_PORT, &GPIO_InitStruct);

	// T?o 10 xung clock SCL d? gi?i phóng SDA n?u b? treo
	for (int i = 0; i < 10; i++)
	{
			HAL_GPIO_WritePin(I2C_PORT, I2C_SCL_PIN, GPIO_PIN_SET);

			HAL_GPIO_WritePin(I2C_PORT, I2C_SCL_PIN, GPIO_PIN_RESET);
	}

	// Ð?t SDA lên m?c cao
	HAL_GPIO_WritePin(I2C_PORT, I2C_SDA_PIN, GPIO_PIN_SET);

	// Kh?i t?o l?i I2C
	HAL_I2C_DeInit(i2c);

	HAL_I2C_Init(i2c);
}
HAL_StatusTypeDef bq40z50_read_u8(uint8_t cmd, uint8_t* data)
{
	HAL_StatusTypeDef ret = HAL_I2C_Mem_Read(bq40z50_i2c, BQ40Z50_ADDR, cmd, I2C_MEMADD_SIZE_8BIT, data, 1, BQ40Z50_TIMEOUT);
	if(ret != HAL_OK)
	{
		I2C_ClearBus(bq40z50_i2c);
		if(ret != HAL_OK) return HAL_ERROR;
	}
	return HAL_OK;
}

HAL_StatusTypeDef bq40z50_read_u16(uint8_t cmd, uint16_t* data)
{
	uint8_t buf[2];
	HAL_StatusTypeDef ret = HAL_I2C_Mem_Read(bq40z50_i2c, BQ40Z50_ADDR, cmd, I2C_MEMADD_SIZE_8BIT, buf, 2, BQ40Z50_TIMEOUT);
	if (ret != HAL_OK)
	{
		I2C_ClearBus(bq40z50_i2c);
		if(ret != HAL_OK) return HAL_ERROR;
	}
	*data = (buf[1] << 8) | buf[0];
	return HAL_OK;
}

HAL_StatusTypeDef bq40z50_read_i16(uint8_t cmd, int16_t* data)
{
	uint8_t buf[2];
	HAL_StatusTypeDef ret = HAL_I2C_Mem_Read(bq40z50_i2c, BQ40Z50_ADDR, cmd, I2C_MEMADD_SIZE_8BIT, buf, 2, BQ40Z50_TIMEOUT);
	if (ret != HAL_OK)
	{
		I2C_ClearBus(bq40z50_i2c);
		if(ret != HAL_OK) return HAL_ERROR;
	}
	*data = (int16_t)((buf[1] << 8) | buf[0]);
	return HAL_OK;
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