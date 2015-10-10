/*
 * motor.c
 *
 *  Created on: 9 Oct 2015
 *      Author: Cobus
 */
#include "motor.h"

struct Motor{
	volatile uint8_t *ddr, *prt;    //Pointers to the addres of the registers

	uint8_t dir;   					//Direction either FORWARD, REVERSE or STOP

	uint8_t state; 					//The Bipolar motors, in full step have 4 states,
									//and need to be stepped through correctly


};
struct MotorList{
	struct Motor mlist[MAX_Motors];
};

void initMotor(struct Motor motor){
	/*
	 * This function will initialise the direction registers
	 * for the motor specified. Make sure to add the motor
	 * pins to the lower 4 bits of the port specified.
	 */

	*motor.ddr |= 0x0F;       				  // set lower 4bites to 1, specifying output

	addMotorToList(motor);					  //add the motor to the list of available motors
}

void addMotorToList(struct Motor motor){
	/*
	 * Add the motor to the list of available motors
	 * since the move() function will loop through this
	 * list and then change the state of each motor accordingly
	 */

	availableMotors.mlist[num_motors]=motor;  //add the motor to the list of available motors
	num_motors++;							  //increment the number of motors set up

}

void initTimer0(){
/*
 * This fuction will set up the Timer/Counter0
 * in CTC mode.
 */

	//Set CTC mode
	TCCR0A |=(1<<WGM01);


	//Set the frequency of output to 400Hz
	OCR0A = 20;

	//Set interupt enable on ouput compare match
	TIMSK0 |=(1<<OCIE0A);

	//Clock div 1024
	TCCR0B |=(1<<CS02)|(1<<CS00);

}

ISR(TIMER0_COMPA_vect){
	/* This is the code to be run once timer reaches
	 * 20 ticks
	 */

	for(int i=0; i<=num_motors; i++){
		switch (availableMotors.mlist.state){

		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;

		}

	}
}





