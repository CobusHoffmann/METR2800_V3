/*
 * end_effector.c
 *
 *  Created on: 12 Oct 2015
 *      Author: Cobus
 */

#include "end_effector.h"

volatile int analogVal=1;			//analog value
volatile bool convertStatus=0;	//0 for not converting 1 for converting

void initEF(){
	/**
	 * Initialise the pins to control the IR leds
	 * and the electromagnet, as follows:
	 *  -PC0 for IR sensor, which will be analog read
	 * 	-PC1 for Electromagnet (EM)
	 * 	-PC2 for Infrared (IR) leds
	 */

	//Set the EM and IR Led pins as outputs
	DDRC = (1<<PORTC1)|(1<<PORTC2);

	//Setup the analog to digital converter on ADC0
	initADC();
}

void setChannel(volatile uint8_t adcPin){
	/*
	 * This function will be used to change between
	 * ADC channels there are only 9.
	 * ADC0->ADC8
	 */




}

void turnOnEM(){
	PORTC |=(1<<PORTC1);

}
void turnOffEM(){
	PORTC &= ~(1<<PORTC1);

}

void turnOnIR(){
	PORTC |=(1<<PORTC2);

}
void turnOffIR(){
	PORTC &= ~(1<<PORTC2);
}
void initADC(){
	/************************************************************************/
		/*
		This function will setup all the pins needed for the end effector to
		to work. The block and bin sensor will be combined into one, so I will
		use one ADC for both and then just one digital pin to control the state
		of the IR-LEDS.
		ADC-pin: ADC0
		                                                                      */
		/************************************************************************/

		//Set Vref as external and select ADC0 (default):
		ADMUX = (1<<REFS0);

		//Set ADCSRA - ADC COntrol Register:
		ADCSRA = (1<<ADEN)|(1<<ADIE)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);

		//Disable Digital input on ADC0
		DIDR0 = (1<<ADC0D);

}

int analogRead(){
	return analogVal;
}

void startADC0(){
	/************************************************************************/
		/*
		Start analog to digital conversion on the ADC0 pin                      */
		/************************************************************************/
		ADCSRA |= (1<<ADSC);
}

ISR(ADC_vect){
	/**
	 * This interrupt service routine will be called
	 * once the ADC converter finished on ADC0
	 */
	analogVal = ADC;
}
