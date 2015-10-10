/*
 * motor.c
 *
 *  Created on: 9 Oct 2015
 *      Author: Cobus
 */
#include "motor.h"

struct Motor{
	volatile uint8_t *ddrc, *prt;   //Pointers to the addres of the registers
	uint8_t dir;   //Direction either FORWARD, REVERSE or STOP

};

