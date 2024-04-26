/*
 * Motor.c
 *
 *  Created on: Apr 26, 2024
 *      Author: tanawatp
 */
#include "Motor.h"

void Motor_setCommand(Motor* motor, MotorMode mode, uint16_t PWM)
{
	motor->Mode = mode;
	switch(motor->Mode)
	{
		case Free:
			PWM = 0;
			motor->IN_A = 0;
			motor->IN_B = 0;
		break;

		case Lock:
			PWM = 0;
			motor->IN_A = 1;
			motor->IN_B = 1;
		break;

		case CW:
			motor->IN_A = 1;
			motor->IN_B = 0;
		break;

		case CCW:
			motor->IN_A = 0;
			motor->IN_B = 1;
		break;
	}
	motor->PWM = PWM;
	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4,motor->PWM);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, motor->IN_A);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, motor->IN_B);

}

void Motor_init(Motor* motor)
{
	Motor_setCommand(motor, Lock, 0);
}
