/*
 * Serial_comm.h
 *
 *  Created on: Mar 15, 2024
 *      Author: tanawatp
 */

#ifndef INC_SERIAL_COMM_H_
#define INC_SERIAL_COMM_H_
#include "main.h"

void send_serial(UART_HandleTypeDef* ch,uint8_t header, uint16_t* data1, int16_t* data2);


#endif /* INC_SERIAL_COMM_H_ */
