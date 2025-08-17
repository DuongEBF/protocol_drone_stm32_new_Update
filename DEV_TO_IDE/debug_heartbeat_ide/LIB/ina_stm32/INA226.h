#ifndef INA226_H
#define INA226_H

#include "stdint.h"
#include "main.h"

#define INA226_ADDR  0x40
#define INA226_REG_CONFIG      0x00
#define INA226_REG_SHUNT       0x01
#define INA226_REG_BUS         0x02
#define INA226_REG_POWER       0x03
#define INA226_REG_CURRENT     0x04
#define INA226_REG_CALIB       0x05
#define INA226_REG_MASK        0x06
#define INA226_REG_ALERT       0x07

typedef struct {
    uint16_t config;
    int16_t  shunt_voltage;   // signed
    uint16_t bus_voltage;
    uint16_t power;
    int16_t  current;         // signed
    uint16_t calibration;
    uint16_t mask_enable;
    uint16_t alert_limit;
} INA226_Data_t;


typedef enum 
{
  INA_OK       = 0x00U,
  INA_ERROR    = 0x01U,
  INA_BUSY     = 0x02U,
  INA_TIMEOUT  = 0x03U
} INA_StatusTypeDef;

void INA226_Init(I2C_HandleTypeDef* i2c);
void INA226_ReadAll(INA226_Data_t* data);
uint16_t INA226_ReadReg(uint8_t reg);
INA_StatusTypeDef INA226_WriteReg(uint8_t reg, uint16_t value);
INA_StatusTypeDef INA226_WriteCalibration(uint16_t cal_value);
#endif
