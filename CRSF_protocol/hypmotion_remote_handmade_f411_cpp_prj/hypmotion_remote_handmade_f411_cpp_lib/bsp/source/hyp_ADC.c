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
#include <bsp/include/hyp_ADC.h>

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static ADC_HandleTypeDef *ADChandle = NULL;

/* Private function prototypes -----------------------------------------------*/
/* @brief: This function used for process lowpass filter ADC value
 * @return: no return
 * */
static void lowpass_filter_adc(hypmotion_adc_t *handle)
{
	handle->adc_lowpass.adc_value_0 = hyp_lowpassFilter(handle->adc_lowpass.adc_value_0, (uint32_t)handle->ADC_VALUE_DMA[0], 20);
	handle->adc_lowpass.adc_value_1 = hyp_lowpassFilter(handle->adc_lowpass.adc_value_1, (uint32_t)handle->ADC_VALUE_DMA[1], 20);
	handle->adc_lowpass.adc_value_2 = hyp_lowpassFilter(handle->adc_lowpass.adc_value_2, (uint32_t)handle->ADC_VALUE_DMA[2], 20);
	handle->adc_lowpass.adc_value_3 = hyp_lowpassFilter(handle->adc_lowpass.adc_value_3, (uint32_t)handle->ADC_VALUE_DMA[3], 20);
//	handle->adc_lowpass.adc_value_4 = hyp_lowpassFilter(handle->adc_lowpass.adc_value_4, (uint32_t)handle->ADC_VALUE_DMA[4], 5);
//	handle->adc_lowpass.adc_value_5 = hyp_lowpassFilter(handle->adc_lowpass.adc_value_5, (uint32_t)handle->ADC_VALUE_DMA[5], 5);
//	handle->adc_lowpass.adc_value_6 = hyp_lowpassFilter(handle->adc_lowpass.adc_value_6, (uint32_t)handle->ADC_VALUE_DMA[6], 5);
//	handle->adc_lowpass.adc_value_7 = hyp_lowpassFilter(handle->adc_lowpass.adc_value_7, (uint32_t)handle->ADC_VALUE_DMA[7], 5);
}

/* @brief: This function used for hypmotion ADC bsp initial
 * @return: hypmotion system return code
 * */
E_HYP_ReturnCode hypmotion_ADC_init(ADC_HandleTypeDef *hadc, hypmotion_adc_t *handle)
{
	if(handle == NULL || hadc == NULL) return HYP_SYSTEM_RETURN_CODE_POINTER_IS_NULL;

	// assign pointer
	ADChandle = hadc;

	// ADC start DMA in initial
	HAL_ADC_Start_DMA(ADChandle, (uint32_t*)handle->ADC_VALUE_DMA, ADC_channels_numbers);


	return HYP_SYSTEM_RETURN_CODE_SUCCESS;
}

/* @brief: This function used for hypmotion ADC bsp process
 * @return: hypmotion system return code
 * */
E_HYP_ReturnCode hypmotion_ADC_Process(hypmotion_adc_t *handle)
{
	if(handle == NULL) return HYP_SYSTEM_RETURN_CODE_POINTER_IS_NULL;


	lowpass_filter_adc(handle);


	return HYP_SYSTEM_RETURN_CODE_SUCCESS;
}

/************************ (C) COPYRIGHT HYPMOTION *****END OF FILE****************/
