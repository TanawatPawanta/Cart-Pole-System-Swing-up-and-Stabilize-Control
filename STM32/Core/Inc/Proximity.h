/*
 * Proximity.h
 *
 *  Created on: Apr 24, 2024
 *      Author: tanawatp
 */

#ifndef INC_PROXIMITY_H_
#define INC_PROXIMITY_H_
#include "main.h"

typedef struct ProxVariables
{
	int8_t Prox_A;
	int8_t Prox_B;
}Proximity;

void Proximity_init(Proximity* proximity);

#endif /* INC_PROXIMITY_H_ */
