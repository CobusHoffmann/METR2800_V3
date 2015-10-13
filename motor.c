/*
 * motor.c
 *
 *  Created on: 9 Oct 2015
 *      Author: Cobus
 */
#include "motor.h"


//set number of initial motors equal to 0
volatile uint8_t num_motors=0;

volatile uint8_t dira,dirb,statea,stateb;

volatile uint16_t steps;


void initMotors(){
	/************************************************************************/
		/* Using 8 bit Timer to run the motors, chosen frequency of 400Hz (400pps),
		   this will be done with a CTC Timer setup on Timer/Counter0.
		   This function must be run after sei()
		                                                                     */
		/************************************************************************/

		dira =STOP;
		statea=1;

		dirb=STOP;
		stateb=1;


}

void move_forwardA(){
	dira = FORWARD;
}

void move_backwardA(){
	dira = BACKWARD;
}

void stopA(){
	dira = STOP;
}

void move_forwardB(){
	dirb = FORWARD;
}

void move_backwardB(){
	dirb = BACKWARD;
}

void stopB(){
	dirb = STOP;
}

void moveA(){
	/*
	 * Motor A on port B
	 */
	switch(statea){

		case 1:
		PORTB = (1<<PORTB0)|(1<<PORTB2)|(1<<PORTB4);     //state_2
		break;



		case 2:
		PORTB = (1<<PORTB0)|(1<<PORTB2)|(1<<PORTB3); //state_4
		break;



		case 3:
		PORTB = (1<<PORTB0)|(1<<PORTB1)|(1<<PORTB3);
		break;



		case 4:
		PORTB = (1<<PORTB0)|(1<<PORTB1)|(1<<PORTB4);
		break;
	}

}

void moveB(){
	/*
	 * Motor B on port D
	 */
	switch(stateb){

		case 1:
		PORTD = (0b000010101<<2);     //state_2
		break;



		case 2:
		PORTD = (0b000001101<<2); //state_4
		break;



		case 3:
		PORTD = (0b000001011<<2);
		break;



		case 4:
		PORTD = (0b000010011<<2);
		break;
	}

}

uint16_t getSteps(){
	return steps;
}





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
	num_motors+=1;							  //increment the number of motors set up

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

	*getMotorAtIndex(motor.index).dir=1;
}

void backward(struct Motor motor){
	/*
	 * Set the dir flag to BACKWARD for motor
	 */

	*getMotorAtIndex(motor.index).dir=2;
}

void stop(struct Motor motor){
	/*
	 * Set the dir flag to STOP for motor
	 */
	*getMotorAtIndex(motor.index).dir=0;
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
	/************************************************************************/
		/* This ISR will increment decrement or keep the state variable constant,
		   this will alow the move() function to not skip any steps.                                                                      */
		/************************************************************************/

		cli(); //clear the interrupt flag to allow this code to execute without interruption.
		switch (dira){
			case FORWARD:
			//increment the state variable
			if (statea<4)
			{
				statea ++;
			}else{
				statea = 1;
			}
				break;

			case BACKWARD:
			//Decrement the state variable
			if (statea>1)
			{
				statea --;
				}else{
				statea = 4;
			}
				break;

			case STOP:
			//Do nothing
				break;

		}

		switch (stateb){
		case FORWARD:
					//increment the state variable
			if (stateb<4)
			{
				stateb ++;
			}else{
				stateb = 1;
			}
				break;

			case BACKWARD:
			//Decrement the state variable
			if (stateb>1)
			{
				stateb --;
				}else{
				stateb = 4;
			}
				break;

			case STOP:
			//Do nothing
				break;


		}

		moveA();
		moveB();
		sei();
			//set the interupt flag again


}





