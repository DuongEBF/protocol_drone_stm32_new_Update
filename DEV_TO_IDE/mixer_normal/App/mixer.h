#ifndef _MIXER_H
#define _MIXER_H
#include "main.h"
#define PWM_MIN 1000
#define PWM_MAX 2000
void mixer_init(TIM_HandleTypeDef* mixer_pwm_out);
float clamp(float v, float min, float max);
void mixer_output(char** argv);
void mixer_handle(void);
#endif //_MIXER_H
