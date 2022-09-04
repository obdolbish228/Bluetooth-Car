/*
 * USART.c
 *
 * Created: 01.09.2022 22:28:01
 *  Author: Aboba
 */ 
#include "main.h"
#include "USART.h"

void USART_Init(int speed, unsigned char parity, unsigned char stopBits){
	switch (speed){
		case 9600:
			UBRR0H = 0x00;
			UBRR0L = 0x67;
			break;
		case 19200:
			UBRR0H = 0x00;
			UBRR0L = 0x33;
			break;
		case 57600:
			UBRR0H = 0x00;
			UBRR0L = 0x10;
			break;
		case 115200:
			UBRR0H = 0x00;
			UBRR0L = 0x08;
			break;
		default:
			UBRR0H = 0x00;
			UBRR0L = 0x67;
			break;
	}
	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)|(1<<TXCIE0);
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	
	if(parity == 2){
		UCSR0C |= (1<<UPM01);
		UCSR0C |= (1<<UPM00);
	}
	else if (parity == 1){
		UCSR0C |= (1<<UPM01);
		UCSR0C &= ~(1<<UPM00);
	}
	else{
		UCSR0C &= ~(1<<UPM01);
		UCSR0C &= ~(1<<UPM00);
	}
	
	if (stopBits == 2){
		UCSR0C |= (1<<USBS0);
	}
	else
		UCSR0C &= ~(1<<USBS0);
}

void USART_Transmit(unsigned char data){
	while (!(UCSR0A & (1<<UDRE0)) );
	UDR0 = data;
}
