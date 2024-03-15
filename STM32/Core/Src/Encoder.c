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
//	encoder->deg = 0;
//	encoder->deg_m1 = 0;
//	encoder->ddeg = 0;
	encoder->freq = freq;
	encoder->htim_ch = htim_ch;
}
void Encoder_getFeedback(Encoder* encoder)
{
	encoder->QEI_read = __HAL_TIM_GET_COUNTER(encoder->htim_ch);
}

