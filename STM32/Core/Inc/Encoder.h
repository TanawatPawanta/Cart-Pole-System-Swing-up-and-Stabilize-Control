/*
 * Encoder.h
 *
 *  Created on: Mar 15, 2024
 *      Author: tanawatp
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_
#include "main.h"
#include "tim.h"
typedef struct EncoderVariables
{
	int16_t QEI_read;
	int16_t QEI_read_m1;
	int16_t diff_QEI;
	int16_t deg;
	int16_t deg_m1;
	int16_t diff_deg;
	uint8_t freq;
	TIM_HandleTypeDef* htim_ch;
}Encoder;

void Encoder_init(Encoder* encoder, TIM_HandleTypeDef* htim_ch, uint8_t freq);
void Encoder_getFeedback(Encoder* encoder);
void Pole_pulse2degree(Encoder* encoder);

#endif /* INC_ENCODER_H_ */
