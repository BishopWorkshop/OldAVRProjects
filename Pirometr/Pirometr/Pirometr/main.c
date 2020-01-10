/*
 * 
 *
 * Created: 19.08.2019 20:30:52
 
 */ 

#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>

#include "CL3641BH.c"
#include "mlx9061x.c"

#include "main.h"

void repeatShow();


uint16_t  To1;




int main(void)
{
   //Инициирование системы
   
   mlx90614_init();
   initDisplay();  
   _delay_ms(300);
  
    while (1) 
    {
		
		
		int8_t ErrTo1 = mlx9061x_ReadTo1(MLX9061X_I2C_ADDR, &To1);
		
		for(int i = 0; i<100; i ++)
		{
			if(ErrTo1) errMes();
			else
			{
				uint16_t tempnum = To1/5;
				showNum(tempnum);
				repeatShow();
				
				
				
				
			}
			
		}
		
		
	}
}



void repeatShow()
{
	for(int i = 0; i<100; i ++)showDisplay();
	
}