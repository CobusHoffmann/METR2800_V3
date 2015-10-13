/*
 * motor.h
 *
 *  Created on: 9 Oct 2015
 *      Author:
 *       - Cobus Hoffmann
 *       - Eliza Mcechnie
 *       - Liam Williams
 *
 *
 * These motor.c and motor.h files implement the functions
 * needed to setup and control stepper motors.
 * The default max number of motors is set to two,
 * this can be changed to how many ever.
 *
 * To create multiple motors just create a
 * struct Motor mName and run the initMotor()
 * function.
 *
 * Each motor needs an entire port at the moment,
 * with the assumption that the enable pin is
 * wired to bit 0.
 *
 * The frequency is hard coded to 400Hz, this
 * can be changed in the initADC0() function.
 *
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>
#include "UART.h"

#define STOP 0
#define FORWARD 1
#define BACKWARD 2

#define MAX_Motors 2




//structure to hold all the specific motor variables
struct Motor{
	volatile uint8_t index;

	volatile uint8_t *ddr, *prt;    //Pointers to the addres of the registers

	volatile uint8_t *dir; 					//Direction either FORWARD, REVERSE or STOP

	volatile uint8_t *state;					//The Bipolar motors, in full step have 4 states,
									//and need to be stepped through correctly

};

//struct that can contain an array of structs
struct MotorList{
	struct Motor mlist[MAX_Motors];
};


void initMotors();

void move_forwardA();

void move_backwardA();

void stopA();

void move_forwardB();

uint16_t getSteps();

//Create List of available motors that can add new motors
struct MotorList availableMotors;

void addMotorToList(struct Motor motor);

void initMotor(struct Motor motor, volatile uint8_t *ddrAddr, volatile uint8_t *prtAddr, volatile uint8_t *dir, volatile uint8_t *state);

void forward(struct Motor motor);

void backward(struct Motor motor);

void stop(struct Motor motor);

void setNumMotors(int num);

void initTimer0();
int getState(struct Motor motor);

int getDir(struct Motor motor);

struct Motor getMotorAtIndex(int index);

ISR(TIMER0_COMPA_vect);

#endif /* MOTOR_H_ */
