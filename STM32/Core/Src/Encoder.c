/*
 * Encoder.c
 *
 *  Created on: Mar 15, 2024
 *      Author: tanawatp
 */
#include "main.h"
#include "Encoder.h"
void Encoder_init(Encoder* encoder, TIM_HandleTypeDef* htim_ch, uint8_t freq)
{
	encoder->QEI_read = 0;
	encoder->QEI_read_m1 = 0;
	encoder->diff_QEI = 0;
	encoder->deg = 0;
	encoder->deg_m1 = 0;
	encoder->diff_deg = 0;
	encoder->freq = freq;
	encoder->htim_ch = htim_ch;
}
void Encoder_getFeedback(Encoder* encoder)
{
	encoder->QEI_read = __HAL_TIM_GET_COUNTER(encoder->htim_ch);
	encoder->diff_QEI = encoder->QEI_read - encoder->QEI_read_m1;
	encoder->QEI_read_m1 = encoder->QEI_read;
}

void Pole_pulse2degree(Encoder* encoder)
{
	if(encoder->QEI_read<=2000)
	{
//		deg = (encoder->QEI_read*0.09)*100;  gain 100(make it is integer) for avoid decimal when send data to simulink.
		encoder->deg = encoder->QEI_read*9;
	}
	else
	{
//		deg = ((encoder->QEI_read-4000)*0.09)*100;
		encoder->deg = (encoder->QEI_read-4000)*9;
	}

	encoder->diff_deg = (encoder->deg - encoder->deg_m1);
	encoder->deg_m1 = encoder->deg;
}
