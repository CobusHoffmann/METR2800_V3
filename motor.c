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

void initMotor(struct Motor motor, volatile uint8_t *ddrAddr, volatile uint8_t *prtAddr){
	/*
	 * This function will initialise the direction registers
	 * for the motor specified. Make sure to add the motor
	 * pins to the lower 4 bits of the port specified.
	 */

	motor.ddr=ddrAddr;
	motor.prt=prtAddr;
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

void forward(struct Motor motor){
	/*
	 * Se the dir flag to FORWARD for motor
	 */

	motor.dir=FORWARD;
}

void backward(struct Motor motor){
	/*
	 * Set the dir flag to BACKWARD for motor
	 */

	motor.dir=BACKWARD;
}

void stop(struct Motor motor){
	/*
	 * Set the dir flag to STOP for motor
	 */

	motor.dir=STOP;
}


ISR(TIMER0_COMPA_vect){
	/* This is the code to be run once timer reaches
	 * 20 ticks
	 */

	for(int i=0; i<num_motors; i++){
		switch (availableMotors.mlist[i].dir){
		case FORWARD:
			if(availableMotors.mlist[i].dir<4){
				availableMotors.mlist[i].dir++;
			}else{
				availableMotors.mlist[i].dir=1;
			}break;
		case BACKWARD:
			if(availableMotors.mlist[i].dir>1){
				availableMotors.mlist[i].dir--;
			}else{
				availableMotors.mlist[i].dir=4;
			}break;

		case STOP:
			//Do nothing
			break;
		}

		switch (availableMotors.mlist[i].state){

		case 1:
			//PORTB = (1<<PORTB0)|(1<<PORTB2)|(1<<PORTB4); original code
			*availableMotors.mlist[i].prt=0b000010101;
			break;
		case 2:
			//PORTB = (1<<PORTB0)|(1<<PORTB2)|(1<<PORTB3); original code
			*availableMotors.mlist[i].prt=0b000001101;
			break;
		case 3:
			//ORTB = (1<<PORTB0)|(1<<PORTB1)|(1<<PORTB3); original code
			*availableMotors.mlist[i].prt=0b000001011;
			break;
		case 4:
			//PORTB = (1<<PORTB0)|(1<<PORTB1)|(1<<PORTB4); original code
			*availableMotors.mlist[i].prt= 0b000010011;
			break;

		}

	}
}





