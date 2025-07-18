/**
  ******************************************************************************
  * @file    hypmotion_joystick.c
  * @author  HYPMOTION Firmware Team
  * @version V1.0.0
  * @date    ${date}
  * @brief   This file contains all the functions prototypes for the hypmotion_application.c
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

/*INCLUDE--------------------------------------------------------------*/
#include <module/include/hyp_joystick.h>

/*VARIABLE-------------------------------------------------------------*/
static hyp_joystick_t *pJoystick;

/*FUNCTION-------------------------------------------------------------*/
/*
 * @brief: this function used for debounce button with 20ms
 * @return: no return
 * */
static void debounce_buttons(hyp_joystick_t *handle)
{
//	handle->button.nv_js_north 			= debounce_read_button_state(NVJoystickNorth_port, NVJoystickNorth_pin);
//	handle->button.nv_js_south 			= debounce_read_button_state(NVJoystickSouth_port, NVJoystickSouth_pin);
//	handle->button.nv_js_east 			= debounce_read_button_state(NVJoystickEast_port, NVJoystickEast_pin);
//	handle->button.nv_js_west 			= debounce_read_button_state(NVJoystickWest_port, NVJoystickWest_pin);
//	handle->button.nv_js_validation  	= debounce_read_button_state(NVJoystickValidation_port, NVJoystickValidation_pin);

	handle->button.button_1 			= debounce_read_button_state(Button1_port, Button1_pin);
	handle->button.button_2 			= debounce_read_button_state(Button2_port, Button2_pin);
	handle->button.button_3 			= debounce_read_button_state(Button3_port, Button3_pin);
	handle->button.button_4 			= debounce_read_button_state(Button4_port, Button4_pin);
//	handle->button.button_5 			= debounce_read_button_state(Button5_port, Button5_pin);
//	handle->button.button_6 			= debounce_read_button_state(Button6_port, Button6_pin);
//	handle->button.button_7 			= debounce_read_button_state(Button7_port, Button7_pin);
}

E_HYP_ReturnCode hyp_joystick_assignValueToChannel(hyp_joystick_t *handle)
{
	if(handle == NULL) return HYP_SYSTEM_RETURN_CODE_POINTER_IS_NULL;



	return HYP_SYSTEM_RETURN_CODE_SUCCESS;
}

/*
 * @brief: this function used for debounce button with 20ms
 * @return: no return
 * */

/*===============================================================
 *  						FreeRTOS
 * =============================================================*/
void hyp_JoystickTask(void const *argument)
{
	for(;;)
	{
		hyp_joystick_process(pJoystick);

		osDelay(1);
	}

}

///--------------------------------Main function------------------------------------
/*
 * @brief: this function used for init hypmotion in api init
 * @return: no return
 * */
E_HYP_ReturnCode hyp_joystick_initialize(hyp_joystick_t *handle)
{
	if(handle == NULL) return HYP_SYSTEM_RETURN_CODE_POINTER_IS_NULL;

	/* Assign pointer FreeRTOS */
	pJoystick = handle;

	/* Create MAVLink FreeRTOS Task */
	osThreadDef(JoystickTask, hyp_JoystickTask, osPriorityAboveNormal, 0, 512);
	handle->ID.Id = osThreadCreate(osThread(JoystickTask), NULL);

	if(handle->ID.Id == NULL) return HYP_SYSTEM_RETURN_CODE_POINTER_IS_NULL;


	return HYP_SYSTEM_RETURN_CODE_SUCCESS;
}

/*
 * @brief: this function used for process hypmotion in api process
 * @return: no return
 * */
E_HYP_ReturnCode hyp_joystick_process(hyp_joystick_t *handle)
{
	if(handle == NULL) return HYP_SYSTEM_RETURN_CODE_POINTER_IS_NULL;

	hypmotion_ADC_Process(&handle->hypmotion_adc);

	debounce_buttons(handle);

    return HYP_SYSTEM_RETURN_CODE_SUCCESS;
}

/************************ (C) COPYRIGHT HYPMOTION *****END OF FILE****************/
