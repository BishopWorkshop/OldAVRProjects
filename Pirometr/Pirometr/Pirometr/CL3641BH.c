/*
 * Исполняемый файл библиотекеи CL3641BH
 *
 * Created: 16.08.2017 21:34:57
 * Author : crazy
 */ 

//#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>
#include "CL3641BH.h"
uint16_t numArr[]={0,0,0,0};


void initDisplay()//Метод определяющий порты на вывод и устанавливающий их в начальное положение
	{
		SIGMENTDDR =0xFF;
		SIGMENTPORT= 0;
		
		NUMBERDDR|=(1<<NUM1)|(1<<NUM2)|(1<<NUM3)|(1<<NUM4);
		NUMBERPORT|=(1<<NUM1)|(1<<NUM2)|(1<<NUM3)|(1<<NUM4);
		_delay_ms(300);
		cleanDisplay();
		
	}

void cleanDisplay()
{
	SIGMENTPORT= 0xFF;
	NUMBERPORT&=~(1<<NUM1)|(1<<NUM2)|(1<<NUM3)|(1<<NUM4);
}


void showNum(uint16_t num)
{
	
	decToBin(num, numArr);
	
	
	refactingData(numArr);
	showDisplayArr(numArr);
	
}


void decToBin(uint16_t num, uint16_t showNUM[4])
{
	
	uint8_t subZero =0;
	uint16_t temp = 0;
	
	
	if(num<2732)subZero=1;
	
	if(subZero)temp = 2732-num;
	else temp = num - 2732;
		
	showNUM[0] = temp/1000;
	if(showNUM[0] ==0) showNUM[0]=20;
	if(subZero)num = showNUM[0]=23; 
	
	temp = temp%1000;
	showNUM[1] = temp/100;
	temp = temp%100;
	showNUM[2] = (temp/10+10);
	showNUM[3] = temp%10;
	
	
		
	
}


void showDisplayArr(uint16_t data[4])//Метод выводящий данные на индикатор
{
	
	
	
	
	for (int i = 0; i<4; i ++)
	{
		
		SIGMENTPORT = data[i];
		
		
		
		switch(i)
		{
			case 0:
			NUMBERPORT|=(1<<NUM1);
			_delay_us(10);
			NUMBERPORT&=~(1<<NUM1);
			break;
			
			case 1:
			NUMBERPORT|=(1<<NUM2);
			_delay_us(10);
			NUMBERPORT&=~(1<<NUM2);
			break;
			
			case 2:
			NUMBERPORT|=(1<<NUM3);
			_delay_us(10);
			NUMBERPORT&=~(1<<NUM3);
			break;
			
			case 3:
			NUMBERPORT|=(1<<NUM4);
			_delay_us(10);
			NUMBERPORT&=~(1<<NUM4);
			break;
			
			
		}
		
		SIGMENTPORT =0xFF;
		
	}
	
	
	
	
}


void refactingData(uint16_t data2[4])//Метод подменяющий значение сигмента на струкутуру сигмента
{
	
	for(int i = 0; i<4; i++)
	{
		switch(data2[i])
		{
			case 0:
			data2[i] = 0;
			data2[i]|=(1<<SIG_Dr)|(1<<SIG_G);
			break;
			
			case 1:
			data2[i] = 0;
			data2[i]|=(1<<SIG_Dr)|(1<<SIG_F)|(1<<SIG_A)|(1<<SIG_E)|(1<<SIG_D)|(1<<SIG_G);
			break;
			
			case 2:
			data2[i] = 0;
			data2[i]|=(1<<SIG_Dr)|(1<<SIG_F)|(1<<SIG_C);
			break;
			
			case 3:
			data2[i] = 0;
			data2[i]|=(1<<SIG_Dr)|(1<<SIG_F)|(1<<SIG_E);
			break;
			
			case 4:
			data2[i] = 0;
			data2[i]|=(1<<SIG_Dr)|(1<<SIG_A)|(1<<SIG_E)|(1<<SIG_D);
			break;
			
			case 5:
			data2[i] = 0;
			data2[i]|=(1<<SIG_Dr)|(1<<SIG_B)|(1<<SIG_E);
			break;
			
			case 6:
			data2[i] = 0;
			data2[i]|=(1<<SIG_Dr)|(1<<SIG_B);
			break;
			
			case 7:
			data2[i] = 0;
			data2[i]|=(1<<SIG_Dr)|(1<<SIG_F)|(1<<SIG_E)|(1<<SIG_D)|(1<<SIG_G);
			break;
			
			case 8:
			data2[i] = 0;
			data2[i]|=(1<<SIG_Dr);
			break;
			
			case 9:
			data2[i] = 0;
			data2[i]|=(1<<SIG_Dr)|(1<<SIG_E);
			break;
			
			case 10:
			data2[i] = 0;
			data2[i]|=(1<<SIG_G);
			break;
			
			case 11:
			data2[i] = 0;
			data2[i]|=(1<<SIG_F)|(1<<SIG_A)|(1<<SIG_E)|(1<<SIG_D)|(1<<SIG_G);
			break;
			
			case 12:
			data2[i] = 0;
			data2[i]|=(1<<SIG_F)|(1<<SIG_C);
			break;
			
			case 13:
			data2[i] = 0;
			data2[i]|=(1<<SIG_F)|(1<<SIG_E);
			break;
			
			case 14:
			data2[i] = 0;
			data2[i]|=(1<<SIG_A)|(1<<SIG_E)|(1<<SIG_D);
			break;
			
			case 15:
			data2[i] = 0;
			data2[i]|=(1<<SIG_B)|(1<<SIG_E);
			break;
			
			case 16:
			data2[i] = 0;
			data2[i]|=(1<<SIG_B);
			break;
			
			case 17:
			data2[i] = 0;
			data2[i]|=(1<<SIG_F)|(1<<SIG_E)|(1<<SIG_D)|(1<<SIG_G);
			break;
			
			case 18:
			data2[i] = 0;			
			break;
			
			case 19:
			data2[i] = 0;
			data2[i]|=(1<<SIG_E);
			break;
			
			case 20: //Пустота
			data2[i] = 0xFF;
			break;
			
			case 21: //Буква Е
			data2[i] = 0;
			data2[i]|=(1<<SIG_Dr)|(1<<SIG_C)|(1<<SIG_B);
			break;
			
			case 22://Буква r
			data2[i] = 0xFF;
			data2[i]&=~((1<<SIG_G)|(1<<SIG_E));
			break;
			
			case 23://знак минуса
			data2[i] = 0xFF;
			data2[i]&=~(1<<SIG_G);
			break;
			
			default:
			data2[i] = 0;
			data2[i]|=(1<<SIG_Dr)|(1<<SIG_C)|(1<<SIG_B);
			break;
		}
		
		
		
		
		
		
	}
	
	
	
	
}

void errMes()
{
	
	numArr[0] = 20;
	numArr[1] = 21;
	numArr[2] = 22;
	numArr[3] = 22;
	
	
	refactingData(numArr);
	 showDisplayArr(numArr);
}

void showDisplay()
{
	showDisplayArr(numArr);
	
}