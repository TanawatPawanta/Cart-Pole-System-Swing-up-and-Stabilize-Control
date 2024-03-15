/*
 * Serial_comm.c
 *
 *  Created on: Mar 15, 2024
 *      Author: tanawatp
 */
#include "Serial_comm.h"
#include "usart.h"
//extern UART_HandleTypeDef huart2;

void send_serial(UART_HandleTypeDef* ch,uint8_t header, uint16_t* data1, int16_t* data2)
{
	uint8_t TxBuffer[7];
	TxBuffer[0] = header; // header
	TxBuffer[1] = *data1 & 0xff;
	TxBuffer[2] = (*data1 & 0xff00) >> 8;

	TxBuffer[3] = *data2 & 0xff;
	TxBuffer[4] = (*data2 & 0xff00) >> 8;
	TxBuffer[5] = 10; // /n

	HAL_UART_Transmit_DMA(ch,TxBuffer, 6);
}

