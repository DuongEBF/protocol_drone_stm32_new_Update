/**
  ******************************************************************************
  * @file    hypmotion_application.c
  * @author  HYPMOTION Firmware Team
  * @version V2.0.0
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

/*INCLUDE--------------------------------------------------------------*/
#include <api/include/hyp_remoteController_api.h>

extern TIM_HandleTypeDef htim3;

extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

/*FUNCTION--------------------------------------------------------------*/
E_HYP_ReturnCode hyp_remoteController_api_initialize(hyp_remoteController_api_t *handle)
{
	if(handle == NULL)  return HYP_SYSTEM_RETURN_CODE_POINTER_IS_NULL;

	/* Assign pointer */
	handle->mavlink.joystick = &handle->joystick;

	handle->crsf.joystick	 = &handle->joystick;

	handle->crsf.uart		 = &handle->bsp_uart;

	/* Initial */
	if(hypmotion_ADC_init(&hadc1, &handle->joystick.hypmotion_adc) != HYP_SYSTEM_RETURN_CODE_SUCCESS)

		return HYP_SYSTEM_RETURN_CODE_COMM_INIT_FAILED;

	if(hyp_common_initialize(&htim3) != HYP_SYSTEM_RETURN_CODE_SUCCESS)

		return HYP_SYSTEM_RETURN_CODE_COMM_INIT_FAILED;


	if(hyp_joystick_initialize(&handle->joystick) != HYP_SYSTEM_RETURN_CODE_SUCCESS)

		return HYP_SYSTEM_RETURN_CODE_COMM_INIT_FAILED;


//	if(hypmotion_crsf_protocol_initialize(&handle->crsf) != HYP_SYSTEM_RETURN_CODE_SUCCESS)
//
//		return HYP_SYSTEM_RETURN_CODE_COMM_INIT_FAILED;


	if(hyp_mavlink_initialize(&handle->mavlink) != HYP_SYSTEM_RETURN_CODE_SUCCESS)

		return HYP_SYSTEM_RETURN_CODE_COMM_INIT_FAILED;



	return HYP_SYSTEM_RETURN_CODE_SUCCESS;
}


/************************ (C) COPYRIGHT HYPMOTION *****END OF FILE****************/
