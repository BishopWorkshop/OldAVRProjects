/*
 * bwUART.c
 *
 * Created: 21.06.2017 12:46:43
 * Author : crazy
 *библиотека для передачи и приёма данных по Uart
 
 #define  BAUD 9600 так устанавливается скорость 
 F_CPU 8000000
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

//#define  BAUD 9600
//#define  F_CPU 8000000
#define  UBRR_VAL F_CPU/16/BAUD-1

void initUART();
void UARTtransmitChar(char a);
void UARTtransmitString(char *a);



void initUART() //Настройка работы UART
{
	
	
	//Установка скорости работы UART
	UBRRH =(UBRR_VAL>>8);
	UBRRL =UBRR_VAL;
	//UCSRA = 0x00;
	
	
	
	//Передатчик
	//Разрешение работы передатчика
	UCSRB|=(1<<TXEN);
	
	
	//Приёмник
	//Разрешение работы приемника
	UCSRB|=(1<<RXEN)|(1<<RXCIE); //Разрешение прерывания по приёму
	//Формат посылки 8bt 1 stopBt контроль чётности отключен
	UCSRC|=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
	
	
	
	
}

void UARTtransmitChar(char a)
{
	while ( !( UCSRA & (1<<UDRE)) );

UDR = a;
	
	
}

void UARTtransmitString(char *a)
{
	char *u=a;
	while(*u!='\0')
	{
		UARTtransmitChar(*u++);		
		
	}
	
	
	
}