/*
 * pick_n_place.c
 *
 *  Created on: 9 Oct 2015
 *      Author: Cobus
 */


#include <avr/io.h>
#include <util/delay.h>
#include "motor.h"


#define F_CPU 16000000ul


int main (){

	//setNumMotors(2);
	struct Motor motora,motorb;
	initMotor(motora,&DDRC,&PORTC);
	forward(motora);
	initMotor(motorb,&DDRB,&PORTB);
	forward(motorb);

	while(1){
		//Main program loop
		//_delay_ms(1000);







	}

	return 0;
}

