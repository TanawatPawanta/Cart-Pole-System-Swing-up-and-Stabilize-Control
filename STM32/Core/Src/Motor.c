/*
 * Motor.c
 *
 *  Created on: Apr 26, 2024
 *      Author: tanawatp
 */
#include "Motor.h"
void Motor_init(Motor* motor, TIM_HandleTypeDef* htim_ch)
{
	motor->Dir = Stop;
	motor->PWM = 0;
	motor->Current = 0.0;
	motor->htim_ch = htim_ch;
}
void Motor_setPWM(Motor* motor, uint16_t pwm)
{
	motor->PWM = pwm;
}
void Motor_setDir(Motor* motor, MotorDir dir)
{
	motor->Dir = dir;
}
void Motor_run(Motor* motor)
{
	switch(motor->Dir)
	{
		case Stop:
			__HAL_TIM_SET_COMPARE(motor->htim_ch,TIM_CHANNEL_4,0);
			break;
		case CW:
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, 0);
			__HAL_TIM_SET_COMPARE(motor->htim_ch,TIM_CHANNEL_4,motor->PWM);
			break;
		case CCW:
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, 1);
			__HAL_TIM_SET_COMPARE(motor->htim_ch,TIM_CHANNEL_4,motor->PWM);
			break;
	}

}
//void Motor_setCommand(Motor* motor, MotorMode mode, uint16_t PWM)
//{
//	motor->Mode = mode;
//	switch(motor->Mode)
//	{
//		case Free:
//			PWM = 0;
//			motor->IN_A = 0;
//			motor->IN_B = 0;
//		break;
//
//		case Lock:
//			PWM = 0;
//			motor->IN_A = 1;
//			motor->IN_B = 1;
//		break;
//
//		case CW:
//			motor->IN_A = 1;
//			motor->IN_B = 0;
//		break;
//
//		case CCW:
//			motor->IN_A = 0;
//			motor->IN_B = 1;
//		break;
//	}
//	motor->PWM = PWM;
//	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4,motor->PWM);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, motor->IN_A);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, motor->IN_B);
//}

//void Motor_init(Motor* motor)
//{
//	Motor_setCommand(motor, Lock, 0);
//}
