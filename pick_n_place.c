/*
 * pick_n_place.c
 *
 *  Created on: 9 Oct 2015
 *      Author: Cobus
 */

//#define F_CPU 16000000



#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "motor.h"






int main (){
	//DDRB=0xFF;
	sei();


	//setNumMotors(2);
	volatile uint8_t maDir=1;
	volatile uint8_t maState =1;
	struct Motor motora;
	initMotor(motora,&DDRB,&PORTB,&maDir,&maState);
	//forward(motora);


	initTimer0();
	//initMotor(motorb,&DDRD,&PORTD);
	//forward(motorb);

	while(1){

		_delay_ms(1000);
		stop(motora);
		_delay_ms(1000);
		backward(motora);
		_delay_ms(1000);
		stop(motora);
		_delay_ms(1000);
		forward(motora);


	}

	return 0;
}

