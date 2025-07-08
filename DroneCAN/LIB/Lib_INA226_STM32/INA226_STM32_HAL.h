/*
 * STM32 HAL-compatible INA226 Register Definitions and Driver Header
 * Based on original Arduino version by Korneliusz Jarzębski
 */

#ifndef __INA226_STM32_H__
#define __INA226_STM32_H__

#include "stdint.h"

#define INA226_ADDRESS              (0x40)

#define INA226_REG_CONFIG           (0x00)
#define INA226_REG_SHUNTVOLTAGE     (0x01)
#define INA226_REG_BUSVOLTAGE       (0x02)
#define INA226_REG_POWER            (0x03)
#define INA226_REG_CURRENT          (0x04)
#define INA226_REG_CALIBRATION      (0x05)
#define INA226_REG_MASKENABLE       (0x06)
#define INA226_REG_ALERTLIMIT       (0x07)

#define INA226_BIT_SOL              (0x8000)
#define INA226_BIT_SUL              (0x4000)
#define INA226_BIT_BOL              (0x2000)
#define INA226_BIT_BUL              (0x1000)
#define INA226_BIT_POL              (0x0800)
#define INA226_BIT_CNVR             (0x0400)
#define INA226_BIT_AFF              (0x0010)
#define INA226_BIT_CVRF             (0x0008)
#define INA226_BIT_OVF              (0x0004)
#define INA226_BIT_APOL             (0x0002)
#define INA226_BIT_LEN              (0x0001)
#define INA226_AVERAGES_16             (0b010)
#define INA226_BUS_CONV_TIME_1100US    (0b100)
#define INA226_SHUNT_CONV_TIME_1100US  (0b100)
#define INA226_MODE_SHUNT_BUS_CONT     (0b111)
void INA226_Begin(uint8_t address);
void INA226_Configure(uint16_t config);
void INA226_Calibrate(float rShuntValue, float iMaxExpected);
float INA226_ReadBusVoltage(void);
float INA226_ReadShuntVoltage(void);
float INA226_ReadCurrent(void);
float INA226_ReadPower(void);

#endif
