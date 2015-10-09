/*
 * motor.h
 *
 *  Created on: 9 Oct 2015
 *      Author: Cobus
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include <avr/io.h>

struct Motor;

void forward(struct Motor motor);

void backward(struct Motor motor);

void stop(struct Motor motor);

#endif /* MOTOR_H_ */
