/*
 * UART.h
 *
 *  Created on: 13 Oct 2015
 *      Author: Cobus
 */

#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

void initUART(unsigned int ubrr);
void printStr(unsigned char charArray[]);
void transmitUART(unsigned char data);



#endif /* UART_H_ */
