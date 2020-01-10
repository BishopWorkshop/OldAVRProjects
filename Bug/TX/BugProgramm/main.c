//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// Это программное обеспечение распространяется свободно. Вы можете размещать
// его на вашем сайте, но не забудьте указать ссылку на мой YouTube-канал 
// "Электроника в объектике" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// Автор: Надыршин Руслан / Nadyrshin Ruslan
//------------------------------------------------------------------------------

#define F_CPU 8000000L
#define BAUD 9600
#include <avr/io.h>
#include <util/delay.h>
#include "nrf24/nrf24.c"
#include "main.h"
#include <avr/interrupt.h>
#include "bwUART.c"
#include "types.h"

//Настройка таймера
// #define F_PWM 50
// #define TIMER_PRESC 64
// #define TOP F_CPU/(2*TIMER_PRESC*F_PWM)



#define nRF_CHANNEL     70
#define nRF_isTX_DEMO   1       // Флаг работы проекта в качестве передатчика
#define nRF_PaketLen    1     // Если размер пакета = 0, то используется переменная длина пакета

// Адрес соединения с другим микроконтроллером
uint8_t Addr[] = {0x01, 0x02, 0x03, 0x04, 0x05};
// Буфер пакета
uint8_t Buff[] = {
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x11, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x21, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x31, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08
};

uint8_t Pipe = 0;       // Номер соединения
uint8_t Len = 0;        // Длина пакета
uint32_t Counter = 0;   // Счётчик пакетов
uint32_t TryCounter = 0;// Счётчик повторных попыток отправки пакета
uint32_t Err = 0;       // Счётчик ошибок при отправке
  
//int DriveA = 10;
//int DriveB = 10;  
char needtransmitflag =0;
char frame =0;
  
//void initPWM(void);
//void initDirPorts(void);
//int DriveValue(char pwr);



int main(void)
{
	_delay_ms(1500);
	
  //initDirPorts();
  // Инициализация nRF24
  //initPWM();//Включаем ШИМ
  
  
  initUART();
  
  
  nrf24_init(nRF_CHANNEL);
  // Настройка соединения, установка адреса
  nrf24_RxPipe_Setup(0, Addr, nRF_PaketLen);  
  
  sei();  
  //UARTtransmitString("Booted\r") ;
  /*beep();
  _delay_ms(100);
  beep();*/
 /*UARTtransmitString("nRF enabled\r");*/
 
  
    // Если размер пакета = 0, то используется переменная длина пакета
    
#if (nRF_isTX_DEMO)
  
  Len = nRF_PaketLen;
  while (1)
  {
	  if(needtransmitflag)
	  {
		  cli();
		  Buff[0]=frame;
     int8_t TryNum = nrf24_Send(Addr, Buff, Len);        // Отправка пакета
     if (TryNum >= 0)            // Пакет успешно был отправлен
     {
	     Counter++;                // Считаем кол-во отправленных пакетов
	     TryCounter += TryNum;     // Считаем общее кол-во попыток отправки
     }
     else
     Err++;                    // Считаем кол-во ошибок при отправке
     
     needtransmitflag=0;
	 sei();
	 }
	 _delay_ms(50);
  }
#else
  while (1)
  {
	 
	  //cli();
    Len = nrf24_Recv(&Pipe, Buff);      // Проверяем, есть ли входящие пакеты
    if (Len)    // Принят пакет из соединения № Pipe длиной Len
    {
		
		
		
		
		
  Counter++;
// 	  
// 	  
// 	  // Считаем кол-во принятых пакетов
   }
// 	sei();
//UARTtransmitChar(Counter);

	//_delay_ms(30);
	
  }
#endif


}

ISR(USART_RXC_vect)
{
	frame=UDR;
	needtransmitflag=1;
	
}

