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
	initMotor(motorb,&DDRD,&PORTD);
	forward(motorb);

	while(1){

		_delay_ms(1000);
		stop(motora);
		_delay_ms(200);
		backward(motora);
		_delay_ms(1000);
		stop(motora);
		_delay_ms(200);
		forward(motora);


	}

	return 0;
}

