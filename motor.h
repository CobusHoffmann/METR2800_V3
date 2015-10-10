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
#include <avr/portpins.h>
#include <avr/interrupt.h>

#define STOP 0
#define FORWARD 1
#define BACKWARD 2

#define MAX_Motors 2

volatile int num_motors =0;

//structure to hold all the specific motor variables
struct Motor;

//struct that can contain an array of structs
struct MotorList;

//Create List of available motors that can add new motors
struct MotorList availableMotors;

void addMotorToList(struct Motor motor);

void initMotor(struct Motor motor, volatile uint8_t *ddrAddr, volatile uint8_t *prtAddr);

void forward(struct Motor motor);

void backward(struct Motor motor);

void stop(struct Motor motor);

void initTimer0();

ISR(TIMER0_COMPA_vect);

#endif /* MOTOR_H_ */
