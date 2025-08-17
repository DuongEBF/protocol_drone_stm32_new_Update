/*
 * pid_controller.h
 *
 *  Created on: Aug 13, 2025
 *      Author: duong
 */

#ifndef FAN_CONTROLLER_H_
#define FAN_CONTROLLER_H_
#include "main.h"
void fan_controller_process(void);


void fan_controller_init(TIM_HandleTypeDef* tim3);

#endif /* FAN_CONTROLLER_H_ */
