/**
  ******************************************************************************
  * @file    hypmotion_joystick.h
  * @author  HYPMOTION Firmware Team
  * @version V1.0.0
  * @date    ${date}
  * @brief   This file contains all the functions prototypes for the hypmotion_joystick.c
  *          firmware library
  *
  ******************************************************************************
  * @Copyright
  * COPYRIGHT NOTICE: (c) 2024 HYPMOTION. All rights reserved.
  *
  * The information contained herein is confidential
  * property of Company. The use, copying, transfer or
  * disclosure of such information is prohibited except
  * by express written agreement with Company.
  *
  ******************************************************************************
*/

#ifndef MODULE_INCLUDE_HYP_JOYSTICK_H_
#define MODULE_INCLUDE_HYP_JOYSTICK_H_

#ifdef __cplusplus
extern "C" {
#endif

/*INCLUDE------------------------------------------------------------------*/
#include "common/include/hyp_common.h"
#include <module/include/hyp_button.h>
#include <bsp/include/hyp_ADC.h>

/*--------------------------------- Define---------------------------------*/
/// Firmware version
#define FW_SYS_MODEL 			0
#define FIRMWARE_VERSION_X 		1
#define FIRMWARE_VERSION_Y 		0
#define FIRMWARE_VERSION_Z 		2

#define sbus_min 0
#define sbus_max 2047

/*STRUCTURE----------------------------------------------------------------*/
typedef struct __channel_data_format_t
{
    uint16_t Min;
    uint16_t Max;
    uint8_t reverse;
    uint8_t hardware;
    uint16_t rc_channels_value;

}channel_data_format_t;

typedef enum __E_hardware_type
{
    HARDWARE_TYPE_J1_X,
	HARDWARE_TYPE_J1_Y,
	HARDWARE_TYPE_J2_X,
	HARDWARE_TYPE_J2_Y,
	HARDWARE_TYPE_J3,
	HARDWARE_TYPE_J4,
	HARDWARE_TYPE_J5_X,
	HARDWARE_TYPE_J5_Y,
	HARDWARE_TYPE_J5_B,
	HARDWARE_TYPE_B1,
	HARDWARE_TYPE_B2,
	HARDWARE_TYPE_B3,
	HARDWARE_TYPE_B4,
	HARDWARE_TYPE_B5,
	HARDWARE_TYPE_B6,
	HARDWARE_TYPE_B7,

	HARDWARE_TYPE_COUNT,
}hardware_type_t;

typedef enum __E_firmware_version
{
	FIRMWARE_SYS_MODEL = 0,
	FIRMWARE_VER_X,
	FIRMWARE_VER_Y,
	FIRMWARE_VER_Z,

	FIRMWARE_TYPE_COUNT,

}E_firmware_ver;

typedef struct __T_firmware_version
{
	uint8_t value;

}firmware_version_t;

typedef enum __E_hardware_trim
{
	HARDWARE_TYPE_J1_X_TRIM,
	HARDWARE_TYPE_J1_Y_TRIM,
	HARDWARE_TYPE_J2_X_TRIM,
	HARDWARE_TYPE_J2_Y_TRIM,
	HARDWARE_TYPE_J3_TRIM,
	HARDWARE_TYPE_J4_TRIM,
	HARDWARE_TYPE_J5_X_TRIM,
	HARDWARE_TYPE_J5_Y_TRIM,
	HARDWARE_TYPE_J5_B_TRIM,
	HARDWARE_TYPE_B1_TRIM,
	HARDWARE_TYPE_B2_TRIM,
	HARDWARE_TYPE_B3_TRIM,
	HARDWARE_TYPE_B4_TRIM,
	HARDWARE_TYPE_B5_TRIM,
	HARDWARE_TYPE_B6_TRIM,
	HARDWARE_TYPE_B7_TRIM,

	HARDWARE_TRIM_COUNT,
}E_hardware_trim;

typedef enum __E_joy_calib_value
{
	CALIB_VALUE_J1_X_MIN,
	CALIB_VALUE_J1_X_MIDDLE,
	CALIB_VALUE_J1_X_MAX,

	CALIB_VALUE_J1_Y_MIN,
	CALIB_VALUE_J1_Y_MIDDLE,
	CALIB_VALUE_J1_Y_MAX,

	CALIB_VALUE_J2_X_MIN,
	CALIB_VALUE_J2_X_MIDDLE,
	CALIB_VALUE_J2_X_MAX,

	CALIB_VALUE_J2_Y_MIN,
	CALIB_VALUE_J2_Y_MIDDLE,
	CALIB_VALUE_J2_Y_MAX,


	CALIB_VALUE_J3_MIN,
	CALIB_VALUE_J3_MIDDLE,
	CALIB_VALUE_J3_MAX,

	CALIB_VALUE_J4_MIN,
	CALIB_VALUE_J4_MIDDLE,
	CALIB_VALUE_J4_MAX,

	CALIB_VALUE_COUNT,

}E_joy_calib_value;

typedef struct
{
	E_joy_calib_value calib_enum;
	uint16_t* p_calib_value;

}calib_mapping_t;

typedef struct
{
	uint16_t sbus_value_j1_x;
	uint16_t sbus_value_j1_y;
	uint16_t sbus_value_j2_x;
	uint16_t sbus_value_j2_y;
	uint16_t sbus_value_j3;
	uint16_t sbus_value_j4;
	uint16_t sbus_value_j5_x;
	uint16_t sbus_value_j5_y;
	uint16_t sbus_value_j5_b;
	uint16_t sbus_value_b1;
	uint16_t sbus_value_b2;
	uint16_t sbus_value_b3;
	uint16_t sbus_value_b4;
	uint16_t sbus_value_b5;

	uint16_t sbus_value_switch_1;
	uint16_t sbus_value_switch_2;

}sbus_drone_t;

typedef struct __T_joystick_calib_value
{
	uint16_t min;
	uint16_t middle;
	uint16_t max;
	uint16_t value;

}joystick_calib_value_t;

typedef enum __E_calib_status
{
	CALIB_SUCCESS = 0,
	CALIB_FAILED,

	CALIB_COUNT,

}E_calib_status;

typedef struct
{
	uint8_t adc0;
	uint8_t adc1;
	uint8_t adc2;
	uint8_t adc3;
	uint8_t adc4;
	uint8_t adc5;

}hypmotion_adc_hardware_t;

typedef struct __T_Hypmotion_Joystick
{
	hypmotion_adc_t				hypmotion_adc;
	button_var_t 				button;

	hyp_osThread_inFo_t			ID;

	E_HYP_ReturnCode			returnCode;

}hyp_joystick_t;

/*FUNCTION----------------------------------------------------------------------*/
E_HYP_ReturnCode hyp_joystick_initialize(hyp_joystick_t *handle);

E_HYP_ReturnCode hyp_joystick_process(hyp_joystick_t *handle);

#ifdef __cplusplus
}
#endif // extern "C"

#endif /* MODULE_INCLUDE_HYP_JOYSTICK_H_ */

/************************ (C) COPYRIGHT HYPMOTION *****END OF FILE****************/
