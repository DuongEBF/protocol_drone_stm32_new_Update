/**
  ******************************************************************************
  * @file    hypmotion_button.c
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

/*INCLUDE---------------------------------------------------------------------------*/
#include <module/include/hyp_button.h>

/*VARIABLE---------------------------------------------------------------------------*/

extern button_var_t button;

DebounceButton debounce_buttons[] = {
	{NVJoystickEast_port, NVJoystickEast_pin, GPIO_PIN_SET, 0},
	{NVJoystickNorth_port, NVJoystickNorth_pin, GPIO_PIN_SET, 0},
	{NVJoystickSouth_port, NVJoystickSouth_pin, GPIO_PIN_SET, 0},
	{NVJoystickValidation_port, NVJoystickValidation_pin, GPIO_PIN_SET, 0},
	{NVJoystickWest_port, NVJoystickWest_pin, GPIO_PIN_SET, 0},

    {Button1_port, Button1_pin, GPIO_PIN_SET, 0},
    {Button2_port, Button2_pin, GPIO_PIN_SET, 0},
    {Button3_port, Button3_pin, GPIO_PIN_SET, 0},
    {Button4_port, Button4_pin, GPIO_PIN_SET, 0},
    {Button5_port, Button5_pin, GPIO_PIN_SET, 0},
    {Button6_port, Button6_pin, GPIO_PIN_SET, 0},
    {Button7_port, Button7_pin, GPIO_PIN_SET, 0},
};

/*FUNCTION---------------------------------------------------------------------------*/
GPIO_PinState debounce_read_button_state(GPIO_TypeDef *GPIO_Port, uint16_t pin)
{
    GPIO_PinState reading = HAL_GPIO_ReadPin(GPIO_Port, pin); // Change Button_port to your port
    static uint32_t current_time;
    for (int i = 0; i < sizeof(debounce_buttons)/sizeof(debounce_buttons[0]); i++)
    {
        if (debounce_buttons[i].pin == pin && debounce_buttons[i].port == GPIO_Port)
        {
            if (reading != debounce_buttons[i].last_state) {
                current_time = HAL_GetTick();
            }

            if ((current_time - debounce_buttons[i].last_debounce_time) > DEBOUNCE_DELAY)
            {
            	debounce_buttons[i].last_debounce_time = current_time;
                debounce_buttons[i].last_state = reading;
            }

            return debounce_buttons[i].last_state;
        }
    }

    return GPIO_PIN_SET; // Default state if button not found
}

/************************ (C) COPYRIGHT HYPMOTION *****END OF FILE****************/
