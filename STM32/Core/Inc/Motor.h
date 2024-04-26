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

typedef enum
{
	Lock,
	Free,
	CW,
	CCW,
}MotorMode;

typedef struct MotorVariablrs
{
	int8_t IN_A;	//CW
	int8_t IN_B;	//CCW
	uint16_t PWM;	// 50,000 pulse max
	uint16_t Current;
	MotorMode Mode;
}Motor;

void Motor_init(Motor* motor);
void Motor_setCommand(Motor* motor, MotorMode mode, uint16_t PWM);

#endif /* INC_MOTOR_H_ */
