/*
 * motor.h
 *
 *  Created on: 9 Oct 2015
 *      Author: Cobus Hoffmann
 *
 *  The motor code needs to be able to control two
 *  stepper motors on different ports with one timer.
 *
 *  Timer0 is used here to control the stepping
 *  of the stepper motors
 *
 *
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include <avr/io.h>
#include <stdio.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>

#define STOP 0
#define FORWARD 1
#define BACKWARD 2

#define MAX_Motors 2

int num_motors;


//structure to hold all the specific motor variables
struct Motor{
	volatile uint8_t *ddr, *prt;    //Pointers to the addres of the registers

	volatile uint8_t dir;   					//Direction either FORWARD, REVERSE or STOP

	volatile uint8_t state; 					//The Bipolar motors, in full step have 4 states,
									//and need to be stepped through correctly

};

//struct that can contain an array of structs
struct MotorList{
	struct Motor mlist[MAX_Motors];
};

//Create List of available motors that can add new motors
struct MotorList availableMotors;

void addMotorToList(struct Motor motor);

void initMotor(struct Motor motor, volatile uint8_t *ddrAddr, volatile uint8_t *prtAddr);

void forward(struct Motor motor);

void backward(struct Motor motor);

void stop(struct Motor motor);

void setNumMotors(int num);

void initTimer0();

ISR(TIMER0_COMPA_vect);

#endif /* MOTOR_H_ */
