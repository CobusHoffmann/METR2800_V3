/*
 * pick_n_place.c
 *
 *  Created on: 9 Oct 2015
 *      Author: Cobus
 */

#define F_CPU 16000000ul

#include <avr/io.h>
#include <util/delay.h>
#include "motor.h"





int main (){

	//setNumMotors(2);
	struct Motor motora,motorb;
	initMotor(motora,&DDRC,&PORTC);
	forward(motora);
	initMotor(motorb,&DDRB,&PORTB);
	forward(motorb);

	while(1){


	}

	return 0;
}

