/**
  ******************************************************************************
  * @file    hypmotion_common.c
  * @author  HYPMOTION Firmware Team
  * @version V1.0.0
  * @date    ${date}
  * @brief
  *
  ******************************************************************************
  * @Copyright
  * COPYRIGHT NOTICE: (c) ${year} NST.
  * All rights reserved.
  *
  * The information contained herein is confidential
  * property of Company. The use, copying, transfer or
  * disclosure of such information is prohibited except
  * by express written agreement with Company.
  *
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "common/include/hyp_common.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static TIM_HandleTypeDef *htim_common = NULL;

/* Private function prototypes -----------------------------------------------*/
/* @brief: This function used for delay
 * @param: micrpseconds
 * @return: no return
 * */
void hyp_delayUS(uint32_t us)
{
	__HAL_TIM_SET_COUNTER(htim_common, 0);	// Set the counter value 0.

	while(__HAL_TIM_GET_COUNTER(htim_common) < us); // Wait for the counter to reach the us input parameter.
}

/* @brief: This function used for delay
 * @param: miliseconds
 * @return: no return
 * */
void hyp_delayMS(uint16_t ms)
{
	uint16_t current_time = ms;

	while(--current_time > 0){ // every --current time, we will delay 1000us.
		hyp_delayUS(1000);
	}
}

/* @brief: This function used for get time us at the time
 * @param: pointer timer
 * @return: time us
 * */

uint32_t hyp_getTimeUS(void)
{
	static uint32_t overflow_count = 0;
	static uint32_t last_count = 0;

	// Get counter value from CNT register
	uint16_t current_count = ((TIM_TypeDef *)htim_common->Instance)->CNT;

	// Check overflow
	if(current_count < last_count)
	{
		overflow_count++;
	}

	// Update last counter value for the next call
	last_count = current_count;


	return (overflow_count * 65536) + current_count;
}

/* @brief: This function used for get time ms at the time
 * @param: pointer timer
 * @return: time ms
 * */
uint32_t hyp_getTimeMS(void)
{
	uint32_t microsenconds = hyp_getTimeUS();

	return microsenconds/1000;
}


uint32_t hyp_lowpassFilter(uint32_t adc_filter, uint32_t adc_raw, uint8_t filter_alpha)
{
    return (adc_filter * filter_alpha + adc_raw) / (1 + filter_alpha);
}


float hyp_lowpassFilter_float(float adc_filter, float adc_raw, uint8_t filter_alpha)
{
    return (adc_filter * filter_alpha + adc_raw) / (1 + filter_alpha);
}


int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/* Private functions ---------------------------------------------------------*/
/**
@brief      This function use for initialize common library
@return     Hypmotion system return code
*/
E_HYP_ReturnCode hyp_common_initialize(TIM_HandleTypeDef *htim)
{
	if(htim == NULL)
	{
		return HYP_SYSTEM_RETURN_CODE_POINTER_IS_NULL;
	}

	/*---------- Timer initialization----------- */
	HAL_StatusTypeDef status = HAL_OK;

	status = HAL_TIM_Base_Start(htim);

	// Check timer status
	if(status != HAL_OK)
	{
		return HYP_SYSTEM_RETURN_CODE_COMM_INIT_FAILED;
	}

	// Assign timer pointer
	htim_common = htim;


	return HYP_SYSTEM_RETURN_CODE_SUCCESS;
}



/************************ (C) COPYRIGHT HYPMOTION *****END OF FILE****************/
