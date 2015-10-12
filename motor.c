/*
 * motor.c
 *
 *  Created on: 9 Oct 2015
 *      Author: Cobus
 */
#include "motor.h"


//set number of initial motors equal to 0
int num_motors=0;

void initMotor(struct Motor motor, volatile uint8_t *ddrAddr, volatile uint8_t *prtAddr, volatile uint8_t *dir, volatile uint8_t *state){
	/*
	 * This function will initialise the direction registers
	 * for the motor specified. Make sure to add the motor
	 * pins to the lower 4 bits of the port specified.
	 */
	motor.index=num_motors;

	motor.ddr=ddrAddr;
	motor.prt=prtAddr;
	*motor.ddr |= 0xFF;       				  // set lower 4bites to 1, specifying output
	motor.dir= dir;
	motor.state= state;
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

	*getMotorAtIndex(motor.index).dir=FORWARD;
}

void backward(struct Motor motor){
	/*
	 * Set the dir flag to BACKWARD for motor
	 */

	*getMotorAtIndex(motor.index).dir=BACKWARD;
}

void stop(struct Motor motor){
	/*
	 * Set the dir flag to STOP for motor
	 */

	*getMotorAtIndex(motor.index).dir=STOP;
}

void setNumMotors(int num){
	num_motors=num;
}

int getState(struct Motor motor){
	return *motor.state;
}

int getDir(struct Motor motor){
	return *motor.dir;
}

struct Motor getMotorAtIndex(int index){
	return availableMotors.mlist[index];

}


ISR(TIMER0_COMPA_vect){
	/* This is the code to be run once timer reaches
	 * 20 ticks. It is not perfect as it will clear
	 * and set pins on entire port even though only
	 * 5 pins of the port is used.
	 */
	cli();
	for(int i=0; i<num_motors; i++){
		switch (*(getMotorAtIndex(i).dir)){
		case FORWARD:
			//Want to move forward so increment state by 1
			if(*(getMotorAtIndex(i).state)<4){
				(*(getMotorAtIndex(i).state))+=1;
			}else{
				(*(getMotorAtIndex(i).state))=1;
			}break;
		case BACKWARD:
			//Want to move backwards so decrement state by 1
			if((*(getMotorAtIndex(i).state))>1){
				(*(getMotorAtIndex(i).state))-=1;
			}else{
				(*(getMotorAtIndex(i).state))=4;
			}break;
		case STOP:
			//Don't want to move so
			break;
		}

		switch (*(getMotorAtIndex(i).state)){
		//Bit 0 on each por is set as the H-Bridge enable pin
		case 1:
			//PORTB = (1<<PORTB0)|(1<<PORTB2)|(1<<PORTB4); original code
			(*(getMotorAtIndex(i).prt))=0b000010101;
			break;
		case 2:
			//PORTB = (1<<PORTB0)|(1<<PORTB2)|(1<<PORTB3); original code
			(*(getMotorAtIndex(i).prt))=0b000001101;
			break;
		case 3:
			//ORTB = (1<<PORTB0)|(1<<PORTB1)|(1<<PORTB3); original code
			(*(getMotorAtIndex(i).prt))=0b000001011;
			break;
		case 4:
			//PORTB = (1<<PORTB0)|(1<<PORTB1)|(1<<PORTB4); original code
			(*(getMotorAtIndex(i).prt))=0b000010011;
			break;

		}

	}
	sei();

	//PORTB^=0xff;
}





