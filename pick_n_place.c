/*
 * pick_n_place.c
 *
 *  Created on: 9 Oct 2015
 *      Author: Cobus
 */

//#define F_CPU 16000000

#define F_CPU 16000000
#define BAUD 9600
#define MYUBRR ((F_CPU/16/BAUD)-1)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "motor.h"
#include "end_effector.h"

char s[50];
volatile int b;

volatile uint8_t num_blocks, bin;



int main (){

	sei();

	initMotors();
	move_forwardA();
	move_forwardB();
	initTimer0();
//	initEF();
//	startADC0();
//	itoa(analogRead(),s,10);
//	initUART(MYUBRR);
//	startADC0();

	//printStr("hello\n");
	while(1){
//	    startADC0();
//	    b=analogRead();
//	    itoa(b,s,10);
//
//	    printStr("S is: ");
//	    printStr(s);
//	    printStr("\n");
//	    _delay_ms(2000);

		_delay_ms(2000);
		stopA();
		stopB();
		_delay_ms(1000);
		move_backwardA();
		move_backwardB();
		_delay_ms(2000);
		stopA();
		stopB();
		_delay_ms(1000);
		move_forwardA();
		move_forwardB();

	}

	return 0;
}

