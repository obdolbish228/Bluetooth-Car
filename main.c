/*
 * TupaTest.c
 *
 * Created: 01.09.2022 22:14:25
 * Author : Aboba
 */ 

#include "main.h"
#include "LCD.h"
#include "USART.h"
#include <math.h>

#define PWM_Right OCR0B //X
#define PWM_Left OCR0A //Y

char str[30] = {'\0'};
unsigned char dataRX = 0;
unsigned char befielX [4] = {0};
unsigned char befielY [4] = {0};
/*uint8_t i = 0;
uint8_t dataDigitsX = 0;
uint8_t dataDigitsY = 0;
uint8_t startParsX = 0;
uint8_t startParsY = 0;
uint8_t endParsX = 0;
uint8_t endParsY = 0;*/

int way = 0;


ISR(USART_RX_vect)
{
	dataRX = UDR0;
	
	switch(dataRX)
	{
		case 0x31:
			LCD_SetPos(0, 0);
			LCD_String((char*)"Turn Left ");
			Turn(0);
			break;
		case  0x32:
			LCD_SetPos(0, 0);
			LCD_String((char*)"Backward  ");
			backward();
			break;
		case 0x33:
			LCD_SetPos(0, 0);
			LCD_String((char*)"Turn Right");
			Turn(1);
			break;
		case 0x34:
			LCD_SetPos(0, 0);
			LCD_String((char*)"Forward   ");
			forward();
			break;
	}
}

ISR(USART_TX_vect)
{
	
}





void SetWay(uint8_t where){
	if (where == 1)
	{
		PORTD &= ~(0x10);
		PORTD &= ~(0x08);
	} 
	else
	{
		PORTD |= 0x10;
		PORTD |= 0x08;
	}
}

void forward(){
		switch(way){
			case -1:
				PWM_Right = 0xFF;
				PWM_Left = 0xFF;
				break;
			case -2:
				PWM_Right = 0xCC;
				PWM_Left = 0xCC;
				break;
			case -3:
				PWM_Right = 0x99;
				PWM_Left = 0x99;
				break;
			case -4:
				PWM_Right = 0x66;
				PWM_Left = 0x66;
				break;
			case -5:
				PWM_Right = 0x33;
				PWM_Left = 0x33;
				break;
			case 0:
			SetWay(1);
				PWM_Right = 0x33;
				PWM_Left = 0x33;
				break;
			case 1:
			SetWay(1);
				PWM_Right = 0x66;
				PWM_Left = 0x66;
				break;
			case 2:
			SetWay(1);
				PWM_Right = 0x99;
				PWM_Left = 0x99;
				break;
			case 3:
			SetWay(1);
				PWM_Right = 0xCC;
				PWM_Left = 0xCC;
				break;
			case 4:
			SetWay(1);
				PWM_Right = 0xFF;
				PWM_Left = 0xFF;
				break;
		}
		if (way < 5)
		{
			way++;
		}
		sprintf(str, "%d", way);
		LCD_String(str);
// 	if (way < 0)
// 	{
// 		PWM_Right += 0x33;
// 		PWM_Left += 0x33;
// 		way++;
// 	} else if (way == 0)
// 	{
// 		SetWay(1);
// 		PWM_Right += 0x33;
// 		PWM_Left += 0x33;
// 		way++;
// 		
// 	} else if (way > 0)
// 	{
// 		if (!(PWM_Right == 255 || PWM_Left == 255)){
// 			PWM_Right += 0x33;
// 			PWM_Left += 0x33;
// 			way++;
// 		}	
// 	}
// 	
// 	LCD_Clear();
// 	sprintf(str, "%1d", PWM_Right);
// 	LCD_String(str);
}

void backward(){
	switch(way){
		case 1:
			PWM_Right = 0x00;
			PWM_Left = 0x00;
			break;
		case 2:
			PWM_Right = 0x33;
			PWM_Left = 0x33;
			break;
		case 3:
			PWM_Right = 0x66;
			PWM_Left = 0x66;
			break;
		case 4:
			PWM_Right = 0x99;
			PWM_Left = 0x99;
			break;
		case 5:
			PWM_Right = 0xCC;
			PWM_Left = 0xCC;
			break;
		case 0:
		SetWay(0);
			PWM_Right = 0xCC;
			PWM_Left = 0xCC;
			break;
		case -1:
		SetWay(0);
			PWM_Right = 0x99;
			PWM_Left = 0x99;
			break;
		case -2:
		SetWay(0);
			PWM_Right = 0x66;
			PWM_Left = 0x66;
			break;
		case -3:
		SetWay(0);
			PWM_Right = 0x33;
			PWM_Left = 0x33;
			break;
		case -4:
		SetWay(0);
			PWM_Right = 0x00;
			PWM_Left = 0x00;
			break;
	}
	if (way > -5)
	{
		way--;
	}
	
	sprintf(str, "%d", way);
	LCD_String(str);
// 	if (way > 0)
// 	{
// 		PWM_Right -= 0x33;
// 		PWM_Left -= 0x33;
// 		way--;		
// 	} else if (way == 0)
// 	{
// 		SetWay(0);
// 		PWM_Right += 0xCD;
// 		PWM_Left += 0xCD;
// 		way--;
// 		
// 	} else if (way < 0)
// 	{
// 		if (!(PWM_Right == 0 || PWM_Left == 0)){
// 			PWM_Right -= 0x33;
// 			PWM_Left -= 0x33;
// 			way--;
// 		}
// 	}
// 	
// 	LCD_Clear();
// 	sprintf(str, "%1d", PWM_Right);
// 	LCD_String(str);
}

void Turn(uint8_t turn){
	if (way != 0)
	{
		if (turn == 0)
		{
			PWM_Left -= 0x33;
			_delay_ms(500);
			PWM_Left += 0x33;
		}
		else
		{
			PWM_Right -= 0x33;
			_delay_ms(500);
			PWM_Right += 0x33;
		}
	}
}


int main(void)
{
    DDRC = 0x3F;
    DDRB = 0x00;
    DDRD = 0x78;
    
    PORTC = 0x00;
    PORTB = 0x00;
    PORTD = 0x00;
	
	TCCR0A = 0xA3;
	TCCR0B = 0x01;
	TCNT0 = 0x00;
	PWM_Right = 0x00;
	PWM_Left = 0x00;
	
	sei();
    
    LCD_Init();
    LCD_Clear();
	
	USART_Init(9600, 0, 1);
	
	
    while (1) 
    {
				
	}
}

