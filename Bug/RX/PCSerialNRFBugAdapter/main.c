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
#include <avr/interrupt.h>
#include "nrf24/nrf24.c"
//#include "nrf24/nrf24.h"
#include "main.h"
#include "types.h"

//Настройка таймера
 #define F_PWM 50
#define TIMER_PRESC 64
#define TOP F_CPU/(2*TIMER_PRESC*F_PWM)

#define nRF_CHANNEL     70
#define nRF_isTX_DEMO   0       // Флаг работы демо-проекта в качестве передатчика
#define nRF_PaketLen    1      // Если размер пакета = 0, то используется переменная длина пакета

// Адрес соединения с другим микроконтроллером
uint8_t Addr[] = {0x01, 0x02, 0x03, 0x04, 0x05};
// Буфер пакета
uint8_t Buff[] = {
  0xFF, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x11, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x21, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x31, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08
};

uint8_t Pipe = 0;       // Номер соединения
uint8_t Len = 0;        // Длина пакета
uint32_t Counter = 0;   // Счётчик пакетов
uint32_t TryCounter = 0;// Счётчик повторных попыток отправки пакета
uint32_t Err = 0;       // Счётчик ошибок при отправке

int DriveA = 10;
int DriveB = 10;
char connectCount = 0;
 
void initPWM(void);
void initDirPorts(void);
int DriveValue(char pwr);
void beep(void);
void longBeep(void);
void connectError(void);

int main(void)
{
	_delay_ms(1500);
	DDRD|=(1<<2);
	PORTD|=(1<<2);
  
	initDirPorts();
	initPWM();
	
  // Инициализация nRF24
    nrf24_init(nRF_CHANNEL);
  // Настройка соединения, установка адреса
  nrf24_RxPipe_Setup(0, Addr, nRF_PaketLen);  
  

beep();
_delay_ms(100);
beep();
  
  
  sei();    // Если размер пакета = 0, то используется переменная длина пакета
    
#if (nRF_isTX_DEMO)
  Len = nRF_PaketLen;
  while (1)
  {
	  
     int8_t TryNum = nrf24_Send(Addr, Buff, Len);        // Отправка пакета
     if (TryNum >= 0)            // Пакет успешно был отправлен
     {
	     Counter++;                // Считаем кол-во отправленных пакетов
	     TryCounter += TryNum;     // Считаем общее кол-во попыток отправки
     }
     else
     Err++;                    // Считаем кол-во ошибок при отправке
     
     _delay_ms(50);
  }
#else
  while (1)
  {
	  cli();
    Len = nrf24_Recv(&Pipe, Buff);      // Проверяем, есть ли входящие пакеты
	sei();
    if (Len)    // Принят пакет из соединения № Pipe длиной Len
    {
		char ControlFrame=Buff[0];
		char RightSpeed = ControlFrame&0b00001111;
		char LeftSpeed = ((ControlFrame&0b11110000)>>4);
		
		if(RightSpeed==(0b00001000||0))
			{
				PORTC &=~(1<<PORTC3);
				PORTC&=~(1<<PORTC2);
			}
		else
			DriveA= DriveValue(RightSpeed);
		
		if(LeftSpeed==(0b00001000||0))
			{
				PORTC &=~(1<<PORTC0);
				PORTC&=~(1<<PORTC1);
				
			}
		else
			DriveB=DriveValue(LeftSpeed);

		if((RightSpeed&8)!=0)
			{
				PORTC &=~(1<<PORTC2);
				PORTC|=(1<<PORTC3);
			}
		else
			{
				PORTC &=~(1<<PORTC3);
				PORTC|=(1<<PORTC2);
			
			}
		
		if((LeftSpeed&8)!=0)
			{
				PORTC &=~(1<<PORTC0);
				PORTC|=(1<<PORTC1);
			}
		else
			{
				PORTC &=~(1<<PORTC1);
				PORTC|=(1<<PORTC0);
				
			}
      // Тут ваша обработка пакета

      //Counter++;// Считаем кол-во принятых пакетов
	  connectCount=0;
	  
    }
	_delay_ms(20);
	connectCount++;
	if(connectCount>30)
	 connectError();
  }
#endif

return 0;
}

void connectError(void)
{
	
	DriveA =10;
	DriveB = 10;
	
	longBeep();
	/*tNrf24Reg00h RegValue;
	// Переключаемся в режим приёмника и переводим nRF24 в режим PowerDown
	nrf24_read_regs(NRF24_REG_CONFIG, (uint8_t *) &RegValue, 1);
	RegValue.bPRIM_RX = 1;        // Переключаемся в режим приёмника (PRX)
	RegValue.bPWR_UP = 0;         // Усыпляем nRF24
	nrf24_write_regs(NRF24_REG_CONFIG, (uint8_t *) &RegValue, 1);*/
	
	connectCount =0;
	_delay_ms(200);
	nrf24_init(nRF_CHANNEL);
	// Настройка соединения, установка адреса
	nrf24_RxPipe_Setup(0, Addr, nRF_PaketLen);
	_delay_ms(200);
}
void beep(void)
{
	char  b =0;
	while(b<200)
	{
		PORTD&=~(1<<2);
		_delay_us(250);
		PORTD|=(1<<2);
		_delay_us(250);
		b++;
		
	}
	
}

void longBeep(void)
{
	int  b =0;
	while(b<400)
	{
		PORTD&=~(1<<2);
		_delay_us(250);
		PORTD|=(1<<2);
		_delay_us(250);
		b++;
		
	}
	
}



void initPWM(void)
{
	DDRD|=(1<<PORTD4)|(1<<PORTD5); //Переключаем выводы OC1A и  OC1B на выход
	
	//Настройка регистров таймера
	TCCR1A =(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);
	TCCR1B =(1<<WGM13)|(1<<CS11)|(1<<CS10);
	//Биты COM задают режим работы выводов OC1A и  OC1B ШИМ,
	//Биты WGM Переключают ШИМ в режим коррекции фазы и частоты
	//Биты CS устанавливают предделитель на 64 TIMER_PRESC
	
	ICR1 = TOP; //Частота работы ШИМ
	
	OCR1A = DriveA; //Изначальное значение скорости двигателей
	OCR1B = DriveB;
	
	TIMSK =(1<<TICIE1); //Включаем прерывание в точке TOP
	TIFR = (1<<ICF1);
	
	
	
	
}


void initDirPorts()
{
	DDRC |=0b00001111;
	PORTC = 0;
	
	
}

int DriveValue(char pwr)
{
	pwr =pwr&7;
	
	switch(pwr)
	{
		case 0b00000001:
		return 170;
		break;
		
		case 0b00000010:
		return 175;
		break;
		
		case 0b00000011:
		return 180;
		break;
		
		case 0b00000100:
		return 220;
		break;
		
		case 0b00000101:
		return 300;
		break;
		
		case 0b00000110:
		return 600;
		break;
		
		case 0b00000111:
		return 1249;
		break;
		
		
	}

	return 10;
	
}



ISR(TIMER1_CAPT_vect)
{

	OCR1A=DriveA;

	OCR1B=DriveB;

}