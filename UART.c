/*
 * UART.c
 *
 *  Created on: 13 Oct 2015
 *      Author: Cobus
 */

#include "UART.h"

void initUART(unsigned int ubrr){
	/*
	 * This Function will setup the registers
	 * for serial communication.
	 */

	/*Calculate ubrr value*/


	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/*Enable receiver and transmitter*/
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = (3<<UCSZ00);

}

void printStr(unsigned char charArray[]){
	/**
	 * This Function will transmit the character array
	 * over serial
	 */

	for(uint8_t i=0; i<sizeof(charArray); i++){

		if(charArray[i]){
			//Transmit each character individually
			transmitUART(charArray[i]);
		}else{
			//Send new line charicter and exit for loop
			//transmitUART('\n');
			break;

		}
	}
}

void transmitUART(unsigned char data){
	//Standard UART transmit from data sheet pg177

	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;

}
