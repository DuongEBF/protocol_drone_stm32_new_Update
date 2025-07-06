#include "INA226.h"

static I2C_HandleTypeDef* ina_i2c;
void INA226_Init(I2C_HandleTypeDef* i2c) {
    ina_i2c = i2c;
}

uint16_t INA226_ReadReg(uint8_t reg) {
    uint8_t buf[2];
    HAL_I2C_Master_Transmit(ina_i2c, INA226_ADDR << 1, &reg, 1, 100);
    HAL_I2C_Master_Receive(ina_i2c, INA226_ADDR << 1, buf, 2, 100);
    return (buf[0] << 8) | buf[1];
}

INA_StatusTypeDef INA226_WriteReg(uint8_t reg, uint16_t value) {
    uint8_t buf[3];
    buf[0] = reg;
    buf[1] = (value >> 8) & 0xFF;
    buf[2] = value & 0xFF;
    if(HAL_I2C_Master_Transmit(ina_i2c, INA226_ADDR << 1, buf, 3, 100) != HAL_OK)
		{
			return INA_ERROR;
		}
		else 
			return INA_OK;
		
}

void INA226_ReadAll(INA226_Data_t* data) {
    data->config        = INA226_ReadReg(INA226_REG_CONFIG);
    data->shunt_voltage = (int16_t)INA226_ReadReg(INA226_REG_SHUNT);
    data->bus_voltage   = INA226_ReadReg(INA226_REG_BUS);
    data->power         = INA226_ReadReg(INA226_REG_POWER);
    data->current       = (int16_t)INA226_ReadReg(INA226_REG_CURRENT);
    data->calibration   = INA226_ReadReg(INA226_REG_CALIB);
    data->mask_enable   = INA226_ReadReg(INA226_REG_MASK);
    data->alert_limit   = INA226_ReadReg(INA226_REG_ALERT);
}
INA_StatusTypeDef INA226_WriteCalibration(uint16_t cal_value) {
    if(INA226_WriteReg(INA226_REG_CALIB, cal_value) != INA_OK)
		{
			return INA_ERROR;
		}
		else
		 return INA_OK;
}