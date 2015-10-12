/*
 * end_effector.h
 *
 *  Created on: 12 Oct 2015
 *      Author: Cobus
 */

#ifndef END_EFFECTOR_H_
#define END_EFFECTOR_H_

#define EM PORTC1
#define IR PORTC2

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>


void initEF();
void setChannel(volatile uint8_t adcPin);
void turnOnEM();
void turnOffEM();
void turnOnIR();
void turnOffIR();
void initADC();
void startADC0();
int analogRead();
ISR(ADC_vect);


#endif /* END_EFFECTOR_H_ */
