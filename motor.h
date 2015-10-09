/*
 * motor.h
 *
 *  Created on: 9 Oct 2015
 *      Author: Cobus
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include <avr/io.h>

#define STOP 0
#define FORWARD 1
#define REVERSE 2

struct Motor;

void forward(struct Motor motor);

void backward(struct Motor motor);

void stop(struct Motor motor);

#endif /* MOTOR_H_ */
