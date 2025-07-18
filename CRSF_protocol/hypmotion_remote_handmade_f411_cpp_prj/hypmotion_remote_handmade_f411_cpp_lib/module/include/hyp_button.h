/**
  ******************************************************************************
  * @file    hypmotion_button.h
  * @author  HYPMOTION Firmware Team
  * @version V2.0.0
  * @date    ${date}
  * @brief   This file contains all the functions prototypes for the hypmotion_button.c
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

#ifndef MODULE_INCLUDE_HYP_BUTTON_H_
#define MODULE_INCLUDE_HYP_BUTTON_H_

#ifdef __cplusplus
extern "C" {
#endif

/*INCLUDE-----------------------------------------------------------*/
#include "main.h"
//#include "stm32f1xx_hal_gpio.h"

/*STRUCTURE--------------------------------------------------------*/
typedef struct{
	uint16_t pin;
	GPIO_TypeDef *port;
	uint8_t stable_state;
	uint8_t last_state;
	uint32_t last_debounce_time;
}Button;

typedef struct{
	GPIO_TypeDef *port;
	uint16_t pin;
	GPIO_PinState last_state;
	uint32_t last_debounce_time;
}DebounceButton;

typedef struct{
	GPIO_PinState nv_js_east;
	GPIO_PinState nv_js_north;
	GPIO_PinState nv_js_south;
	GPIO_PinState nv_js_validation;
	GPIO_PinState nv_js_west;

	GPIO_PinState button_1;
	GPIO_PinState button_2;
	GPIO_PinState button_3;
	GPIO_PinState button_4;
	GPIO_PinState button_5;
	GPIO_PinState button_6;
	GPIO_PinState button_7;

}button_var_t;

/*DEFINE--------------------------------------------------------*/
#define NVJoystickEast_port 		GPIOC
#define NVJoystickEast_pin			GPIO_PIN_7

#define NVJoystickNorth_port		GPIOC
#define NVJoystickNorth_pin			GPIO_PIN_9

#define NVJoystickSouth_port		GPIOC
#define NVJoystickSouth_pin			GPIO_PIN_8

#define NVJoystickValidation_port	GPIOA
#define NVJoystickValidation_pin	GPIO_PIN_8

#define NVJoystickWest_port			GPIOA
#define NVJoystickWest_pin			GPIO_PIN_11

#define Button1_port			GPIOB
#define Button1_pin				GPIO_PIN_1

#define Button2_port			GPIOB
#define Button2_pin				GPIO_PIN_2

#define Button3_port			GPIOB
#define Button3_pin				GPIO_PIN_13

#define Button4_port			GPIOB
#define Button4_pin				GPIO_PIN_12

#define Button5_port			GPIOC
#define Button5_pin				GPIO_PIN_10

#define Button6_port			GPIOA
#define Button6_pin				GPIO_PIN_15

#define Button7_port			GPIOA
#define Button7_pin				GPIO_PIN_12

#define DEBOUNCE_DELAY			20

/*FUNCTION--------------------------------------------------------*/
GPIO_PinState debounce_read_button_state(GPIO_TypeDef *GPIO_Port, uint16_t pin);

#ifdef __cplusplus
}
#endif // extern "C"

#endif /* MODULE_INCLUDE_HYP_BUTTON_H_ */

/************************ (C) COPYRIGHT HYPMOTION *****END OF FILE****************/
