/**
  ******************************************************************************
  * @file    hypmotion_common.h
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

#ifndef __HYPMOTION_COMMON_H_
#define __HYPMOTION_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdbool.h"
#include "stdarg.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "common/include/hyp_osThread.h"

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#define CLAMP(x, min, max) ( (x) < (min) ? (min) : ( (x) > (max) ? (max) : (x) ) )

/* Exported types ------------------------------------------------------------*/
typedef enum __E_HYP_RETURN_CODE
{
	HYP_SYSTEM_RETURN_CODE_SUCCESS = 0x00,
	HYP_SYSTEM_RETURN_CODE_ERROR,
	HYP_SYSTEM_RETURN_CODE_COMM_INIT_FAILED,
	HYP_SYSTEM_RETURN_CODE_POINTER_IS_NULL,
	HYP_SYSTEM_RETURN_CODE_PARAM_UNVALID,
	HYP_SYSTEM_RETURN_CODE_MAVLINK_OK,
	HYP_SYSTEM_RETURN_CODE_MAVLINK_IS_LOST_CONNECTION,
	HYP_SYSTEM_RETURN_CODE_IN_RESET_PROCESS,

}E_HYP_ReturnCode;


/* Exported functions --------------------------------------------------------*/
void hyp_delayUS(uint32_t us);

void hyp_delayMS(uint16_t ms);

uint32_t hyp_getTimeUS(void);

uint32_t hyp_getTimeMS(void);

uint32_t hyp_lowpassFilter(uint32_t adc_filter, uint32_t adc_raw, uint8_t filter_alpha);

float hyp_lowpassFilter_float(float adc_filter, float adc_raw, uint8_t filter_alpha);

int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max);

/* Private function -----------------------------------------------*/
E_HYP_ReturnCode hyp_common_initialize(TIM_HandleTypeDef *htim);

#ifdef __cplusplus
}
#endif // extern "C"

#endif /* __HYPMOTION_COMMON_H_ */

/************************ (C) COPYRIGHT HYPMOTION *****END OF FILE****************/

