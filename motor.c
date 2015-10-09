/*
 * motor.c
 *
 *  Created on: 9 Oct 2015
 *      Author: Cobus
 */
#include "motor.h"

struct Motor{
	volatile uint8_t *ddrc, *prt;
	uint8_t dir;

};

