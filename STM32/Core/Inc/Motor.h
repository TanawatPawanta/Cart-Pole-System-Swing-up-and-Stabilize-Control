/*
 * Motor.h
 *
 *  Created on: Apr 26, 2024
 *      Author: tanawatp
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_
#include "main.h"
#include "tim.h"

//typedef enum
//{
//	Lock,
//	Free,
//	CW,
//	CCW,
//}MotorMode;
//
//typedef struct MotorVariablrs
//{
//	int8_t IN_A;	//CW
//	int8_t IN_B;	//CCW
//	uint16_t PWM;	// 50,000 pulse max
//	uint16_t Current;
//	MotorMode Mode;
//}Motor;
typedef enum
{
	CW,
	CCW,
	Stop,
}MotorDir;

typedef struct MotorVariablrs
{
	MotorDir Dir;	//direction
	uint16_t PWM;	// 50,000 pulse max
	float Current;
	TIM_HandleTypeDef* htim_ch;
}Motor;

void Motor_init(Motor* motor, TIM_HandleTypeDef* htim_ch);
void Motor_setPWM(Motor* motor, uint16_t pwm);
void Motor_setDir(Motor* motor, MotorDir dir);
void Motor_run(Motor* motor);

#endif /* INC_MOTOR_H_ */
