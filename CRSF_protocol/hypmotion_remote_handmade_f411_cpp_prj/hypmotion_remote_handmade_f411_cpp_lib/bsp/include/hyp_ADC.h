/**
  ******************************************************************************
  * @file    hyp_ADC.h
  * @author  HYPMOTION Firmware Team
  * @version V2.0.0
  * @date    ${date}
  * @brief   This file contains all the functions prototypes for the hypmotion_common.c
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

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef BSP_INCLUDE_HYP_ADC_H_
#define BSP_INCLUDE_HYP_ADC_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdint.h"
#include "math.h"

#include "common/include/hyp_common.h"
/* Defines -------------------------------------------------------------------*/
//#define ADC_channels_numbers 	8
#define ADC_channels_numbers 	4
/* Typedef -------------------------------------------------------------------*/
typedef struct
{
	volatile uint32_t adc_value_0;
	volatile uint32_t adc_value_1;
	volatile uint32_t adc_value_2;
	volatile uint32_t adc_value_3;
	volatile uint32_t adc_value_4;
	volatile uint32_t adc_value_5;
	volatile uint32_t adc_value_6;
	volatile uint32_t adc_value_7;

}adc_lowpass_value_t;

typedef struct __T_Hypmotion_ADC
{

	uint16_t 				ADC_VALUE_DMA[ADC_channels_numbers];

	adc_lowpass_value_t 	adc_lowpass;

}hypmotion_adc_t;


/* Function -------------------------------------------------------------------*/
E_HYP_ReturnCode hypmotion_ADC_init(ADC_HandleTypeDef *hadc, hypmotion_adc_t *handle);

E_HYP_ReturnCode hypmotion_ADC_Process(hypmotion_adc_t *handle);

#ifdef __cplusplus
}
#endif // extern "C"

#endif /* BSP_INCLUDE_HYP_ADC_H_ */

/************************ (C) COPYRIGHT HYPMOTION *****END OF FILE****************/

