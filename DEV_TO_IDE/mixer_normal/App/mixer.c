#include "mixer.h"
#include "stdlib.h"
TIM_HandleTypeDef* mixer_pwm_out;
float motor1,motor2,motor3,motor4;
uint16_t pwm1, pwm2, pwm3, pwm4;
float clamp(float v, float min, float max)
{
	if(v < min) return min;
	if(v > max) return max;
	return v;
}

void mixer_output(char** argv)
{
	float throttle,pitch,roll,yaw;
	throttle = atof(argv[0]);
	pitch = atof(argv[1]);
	roll = atof(argv[2]);
	yaw = atof(argv[3]);
	motor1 = throttle + pitch + roll - yaw;
	motor2 = throttle + pitch - roll + yaw;
	motor3 = throttle - pitch + roll + yaw;
	motor4 = throttle - pitch - roll - yaw;
	motor1 = clamp(motor1, 0.0, 1.0);
	motor2 = clamp(motor2, 0.0, 1.0);
	motor3 = clamp(motor3, 0.0, 1.0);
	motor4 = clamp(motor4, 0.0, 1.0);

	pwm1 = PWM_MIN + (uint16_t)((PWM_MAX - PWM_MIN) * motor1);
	pwm2 = PWM_MIN + (uint16_t)((PWM_MAX - PWM_MIN) * motor2);
	pwm3 = PWM_MIN + (uint16_t)((PWM_MAX - PWM_MIN) * motor3);
	pwm4 = PWM_MIN + (uint16_t)((PWM_MAX - PWM_MIN) * motor4);
}
void mixer_handle(void)
{
	__HAL_TIM_SET_COMPARE(mixer_pwm_out, TIM_CHANNEL_1, pwm1);
	__HAL_TIM_SET_COMPARE(mixer_pwm_out, TIM_CHANNEL_2, pwm2);
	__HAL_TIM_SET_COMPARE(mixer_pwm_out, TIM_CHANNEL_3, pwm3);
	__HAL_TIM_SET_COMPARE(mixer_pwm_out, TIM_CHANNEL_4, pwm4);
}
void mixer_init(TIM_HandleTypeDef* tim2)
{
	mixer_pwm_out = tim2;
	HAL_TIM_PWM_Start(tim2,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(tim2,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(tim2,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(tim2,TIM_CHANNEL_4);
}
