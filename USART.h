/*
 * USART.h
 *
 * Created: 01.09.2022 22:27:49
 *  Author: Aboba
 */ 


#ifndef USART_H_
#define USART_H_

void USART_Init(int speed, unsigned char parity, unsigned char stopBits);
void USART_Transmit(unsigned char data);


#endif /* USART_H_ */