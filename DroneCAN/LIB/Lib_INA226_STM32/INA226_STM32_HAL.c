/* 
 * STM32 HAL-converted INA226 driver (from Arduino version)
 * Converted manually from Korneliusz Jarzębski's Arduino library
 * Requires: I2C_HandleTypeDef* passed from user
 */

#include "INA226_STM32_HAL.h"
#include "main.h"
#include "math.h"

extern I2C_HandleTypeDef hi2c1;  // or your I2C handle
#define INA_I2C &hi2c1

static uint8_t inaAddress = 0x40;  // default

static float rShunt = 0.1f;
static float vShuntMax = 0.08192f;
static float vBusMax = 36.0f;

static float currentLSB = 0.001f;  // default, set during calibration
static float powerLSB = 0.025f;    // default, set during calibration

static void writeRegister16(uint8_t reg, uint16_t val)
{
    uint8_t buf[3];
    buf[0] = reg;
    buf[1] = (val >> 8) & 0xFF;
    buf[2] = val & 0xFF;
    HAL_I2C_Master_Transmit(INA_I2C, inaAddress << 1, buf, 3, HAL_MAX_DELAY);
}

static uint16_t readRegister16(uint8_t reg)
{
    uint8_t val[2];
    HAL_I2C_Master_Transmit(INA_I2C, inaAddress << 1, &reg, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(INA_I2C, inaAddress << 1, val, 2, HAL_MAX_DELAY);
    return (val[0] << 8) | val[1];
}

void INA226_Begin(uint8_t address)
{
    inaAddress = address;
}

void INA226_Configure(uint16_t config)
{
    vShuntMax = 0.08192f;
    vBusMax = 36.0f;
    writeRegister16(INA226_REG_CONFIG, config);
}

void INA226_Calibrate(float rShuntValue, float iMaxExpected)
{
    rShunt = rShuntValue;
    float minimumLSB = iMaxExpected / 32767.0f;
    currentLSB = ceilf(minimumLSB * 10000.0f) / 10000.0f;
    powerLSB = currentLSB * 25.0f;

    uint16_t calib = (uint16_t)(0.00512f / (currentLSB * rShunt));
    writeRegister16(INA226_REG_CALIBRATION, calib);
}

float INA226_ReadBusVoltage(void)
{
    return readRegister16(INA226_REG_BUSVOLTAGE) * 0.00125f;
}

float INA226_ReadShuntVoltage(void)
{
    return readRegister16(INA226_REG_SHUNTVOLTAGE) * 0.0000025f;
}

float INA226_ReadCurrent(void)
{
    return (int16_t)readRegister16(INA226_REG_CURRENT) * currentLSB;
}

float INA226_ReadPower(void)
{
    return readRegister16(INA226_REG_POWER) * powerLSB;
}
