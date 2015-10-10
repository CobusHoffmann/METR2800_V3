/*
 * pick_n_place.c
 *
 *  Created on: 9 Oct 2015
 *      Author: Cobus
 */


#include <avr/io.h>
#include "motor.h"



int main (){

	setNumMotors(2);
	struct Motor motora;
	initMotor(motora,&DDRC,&PORTC);

	return 0;
}

