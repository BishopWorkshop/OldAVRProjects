/*
 * MusicBox.c
 *lya_mal
 * Created: 21.01.2017 16:25:58
 * Author : Bishop
 */ 

#include <avr/io.h>
#include <util/delay.h> 
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#define  BAUD 9600  //Скорость приёма-передачи UART в бодах
#define  UBRR_VAL F_CPU/16/BAUD-1 //Расчёт регистра скорость из заданных параметров

#define CMDLENGTH 15 //Буфер строковых команд терминала длиной 15 символов
char termIn[CMDLENGTH]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};

//Список команд терминала


//Текстовые данные для вывода в терминал
const char helpTxt[] PROGMEM ="This terminal supports these commands:   \rhelp \rinfo  \rclrscr \r\rcuznechik  \rimperial\r";
const char infoTxt[] PROGMEM ="\rAVR teminal \r \rversion 000.5 \rcreated by Bishop Workshop    \r\r\rMusicBoxEdition \r\rThere are songs in memory:\r\rStarWars Imperial march\rRussian folk song Cuznechik\r" ;
const char cnf[] PROGMEM ="Command not found";
const char initUART[] PROGMEM="POWER ON\r\rUART connected";
const char impMrchpl[] PROGMEM="\rPlay Imperial march";
const char czpl[] PROGMEM="\rPlay V trave sidel Cuznechik";
const char onwarpl[] PROGMEM = "\rPlaing Na tebe kak na woyne";


char isComparable(char *a, char *b);

//переменная входной буфер терминала и счётчик введённых символов
char in;
char termCount;


#define  pauz 666 //частоты нот


#define  rediz_mal  25714
#define  mi_mal		24270
#define  fadiz_mal  21622
#define  sol_mal	20408
#define  soldiz_mal	19324
#define  lya_mal	18182
#define  sibem_mal	17161
#define  si_mal		16197

#define  do_1		15289
#define  dodiz_1	14431
#define  re_1		13621
#define  rediz_1	12856
#define  mi_1		12135
#define  fa_1		11454
#define  fadiz_1	10811
#define  sol_1		10204//Таблица доступных нот

//ноты для 8 битного ШИМа (басс партия)

#define mi_bol8 189
#define fadiz_bol8 168
#define sol_bol8 158
#define soldiz_bol8  150
#define lya_bol8 141
#define si_bol8 126
#define do_mal8 118
#define re_mal8 105
#define mi_mal8 94

//массив нот песни "Кузнечик"
unsigned int cz[60][2]  ={lya_mal,2,   
			
			mi_mal,2,
			lya_mal,2,
			mi_mal,2,
			lya_mal,2,
			
			soldiz_mal,2,
			soldiz_mal,4,
			soldiz_mal,2,
			
			mi_mal,2,
			soldiz_mal, 2,
			mi_mal,2,
			soldiz_mal, 2,
			
			lya_mal,2,
			lya_mal,4,
			lya_mal,2,
			
			mi_mal,2,
			lya_mal,2,
			mi_mal,2,
			lya_mal,2,
			
			soldiz_mal,2,
			soldiz_mal,4,
			soldiz_mal,2,
			
			mi_mal,2,
			soldiz_mal, 2,
			mi_mal,2,
			soldiz_mal, 2,
			
			lya_mal,6,
			lya_mal,2,
			
			si_mal,2,
			si_mal,1,
			si_mal,1,
			si_mal,2,
			si_mal,2,
			
			do_1, 2,
			do_1,1,
			do_1,1,
			do_1, 2,
			do_1, 2,
			
			do_1,2,
			si_mal,2,
			lya_mal, 2,
			soldiz_mal,2,
			
			lya_mal,2,
			lya_mal,4,
			lya_mal,2,
			
			si_mal,2,
			si_mal,1,
			si_mal,1,
			si_mal,2,
			si_mal,2,
			
			do_1, 2,
			do_1,1,
			do_1,1,
			do_1, 2,
			do_1, 2,
			
			do_1,2,
			si_mal,2,
			lya_mal, 2,
			soldiz_mal,2,
			
			lya_mal,8};  
//массив нот Имперского марша
unsigned int impmarsh[72][2]  ={sol_mal, 4,
	sol_mal, 4,
	sol_mal, 4,
	rediz_mal, 12,
	sibem_mal, 16,
	
	 sol_mal, 4,
	 rediz_mal, 12,
	 sibem_mal, 16,
	 sol_mal, 4,
	 pauz, 4, 
	 
	 re_1, 4, 
	 re_1, 4, 
	 re_1, 4, 
	 rediz_1 , 12,
	 sibem_mal, 16, 
	 
	 fadiz_mal, 4, 
	 rediz_mal , 12,
	 sibem_mal, 16, 
	 sol_mal,  2, 
	 
	 sol_1, 4,
	 sol_mal, 12, 
	 sol_mal, 16, 
	 sol_1, 4, 
	 fadiz_1, 12, 
	 fa_1, 16, 
	 
	 mi_1 , 16, 
	 rediz_1, 16, 
	 mi_1, 8, 
	 pauz, 8, 
	 soldiz_mal, 8, 
	 dodiz_1 , 4,
	 do_1, 12, 
	 si_mal, 16,
	 
	 sibem_mal, 16,
	 lya_mal, 16, 
	 sibem_mal, 8, 
	 pauz, 8,
	 rediz_mal, 8, 
	 fadiz_mal , 4, 
	 rediz_mal, 12, 
	 fadiz_mal, 16, 
	 
	 sibem_mal , 4, 
	 sol_mal , 12,
	 sibem_mal, 16, 
	 re_1, 2,
	 
	 sol_1, 4,
	 sol_mal, 12,
	 sol_mal, 16,
	 sol_1, 4,
	 fadiz_1, 12, 
	 re_1, 16, 
	 
	 mi_1 , 16,
	 rediz_1, 16,
	 mi_1, 8,
	 pauz, 8,
	 soldiz_mal, 8,
	 dodiz_1 , 4,
	 do_1 , 12,
	 si_mal , 16,
	 
	  sibem_mal, 16,
	  lya_mal, 16,
	  sibem_mal, 8,
	  pauz, 8,
	  rediz_mal, 8,
	  fadiz_mal , 4,
	  rediz_mal, 12,
	  sibem_mal, 16,
	  
	  sol_mal, 4,	  
	  rediz_mal, 12,
	  sibem_mal , 16,
	  sol_mal, 2};
//массив нот На войне
unsigned int bassOnWar[28]={
	lya_bol8, mi_bol8, sol_bol8, lya_bol8, mi_bol8, 
	lya_bol8, soldiz_bol8, sol_bol8, mi_bol8, fadiz_bol8,
	sol_bol8, mi_bol8, fadiz_bol8, sol_bol8, do_mal8,
	lya_bol8, si_bol8, do_mal8, lya_bol8, do_mal8,
	re_mal8, mi_mal8, do_mal8, re_mal8, mi_mal8, re_mal8,
	do_mal8, re_mal8};




//Подпрограмма воспроизведения имперского марша
void imperiamarsh(void)
{
	termPrintPM(impMrchpl);
	for(register char nota = 0;nota<72;nota++)
	{
		if( impmarsh[nota][0]==pauz)
		TCCR1B&=~(1<<CS10);
		else
		{
			OCR1A=impmarsh[nota][0];
			TCCR1B|=(1<<CS10);
		}
		switch(impmarsh[nota][1])
		{
			case 2:
			_delay_ms(500*2);
			break;
			
			case 4:
			_delay_ms(250*2);
			break;
			
			case 8:
			_delay_ms(125*2);
			break;
			
			case 12:
			_delay_ms(188*2);
			break;
			
			case 16:
			_delay_ms(63*2);
			break;			
			
		}
		TCCR1B&=~(1<<CS10);
		_delay_ms(5);
		
		
	}
	
	
}
//Подпрограмма воспроизведения кузнечика
void cuznechik(void)
{
	termPrintPM(czpl);
	for(register char nota = 0;nota<60;nota++)
	{
		OCR1A=cz[nota][0];
		TCCR1B|=(1<<CS10);
		switch(cz[nota][1])
			{
				case 1:
				_delay_ms(125);
				break;
				case 2:
				_delay_ms(250);
				break;
				case 4:
				_delay_ms(500);
				break;
				case 6:
				_delay_ms(750);
				break;
				case 8:
				_delay_ms(1000);
				break;
				
			}
		TCCR1B&=~(1<<CS10);
		_delay_ms(5);
		
		
	}	
	
}
//Программа На тебе как на войне
void onwar()
{
	
	termPrintPM(onwarpl);
	char *u = bassOnWar;
	
	while(*u!='\0')
	{
		OCR2=*u;
		TCCR2=(1<<CS22)|(1<<CS21)|(1<<CS20);
		
			_delay_ms(63);
			
		TCCR2&=~(1<<CS22)|(1<<CS21)|(1<<CS20);
		_delay_ms(5);
		u++;
	
	}
}


int main(void)
{
	
	//initializationUART();
	
	//termInClear();
	
	musicBoxInit();
	
	//termPrintPM(PSTR("UART TERMINAL is ready\r"));
	
	//termPrintPM(helpTxt);
	sei();
	
	imperiamarsh();
			
	while (1) 
    {
				
    }
	
	
}


void musicBoxInit() //Инициализация и настройка музыкальной шкатулки 
{
	DDRB =(1<<PB1)|(1<<PB2);//установка ноги на выход (вывод ШИМ)
	
	
	
	
	//таймер пищалки
	TCCR1A =0;
	TCCR1B=0;
	TCCR2 =0;
	
	TCCR2|=(1<<WGM21)|(1<<COM21);//|(1<<CS22)|(1<<CS21)|(1<<CS20);
	
	TCCR1A|=(1<<COM1A0);
	TCCR1A|=(1<<WGM12);
	//TCCR1B|=(1<<CS10);
	
	TIMSK=(1<<OCIE1A)|(1<<OCIE2);
	//OCR1A=9090;
	
}

 void initializationUART() //Настройка работы UART
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
	 
	 termPrintPM(initUART);
	 
	 
 }
 
 
 void termInClear() //Очистка входных буферов терминала
{
	for(register char i=0; i<CMDLENGTH;i++)
	termIn[i] =0;
	
	termCount=0;
	
	in=0;
	
}

void termPrintPM(char *string)//Метод вывода текста в терминал из Flash памяти 
{
	
	_
	UDR=0x0D;
	
	while(pgm_read_byte(string)!='\0')
	{
		UDR = pgm_read_byte(string);
		_delay_ms(1);
		string++;
	}
	UDR=0x0D;
	;
	
}

void commandNotFound()
{
	termPrintPM(cnf);	
}





void executComand(char termIn[]) //выполнение команд пришедших с терминала
{ 
	register char CMDCount =0;
	char *u=termIn;	
	
	while (*u!='\0')
	{
	CMDCount++;
	u++;		
	}
	
	switch (CMDCount)
	{
		case 1:
		if(termIn[0]=='?')
		termPrintPM(helpTxt);
		break;
		
		case 4:
		{
			
			if(isComparable(termIn,"help")==1)
			termPrintPM(helpTxt);
			else if(isComparable(termIn,"info")==1)
			termPrintPM(infoTxt);
			else
			commandNotFound();
		}
			break;	
			
		case 5:
			{
				if(isComparable(termIn, "onwar")==1)
				musicBoxPlayer(3);
				else
				commandNotFound();
				
			}
			break;
		case 6:
			{
				if(isComparable(termIn,"clrscr")==1)
				clearScreen();
				else
				commandNotFound();
			}	
			break;	
		case 8:
			{
				if(isComparable(termIn,"imperial")==1)
				musicBoxPlayer(0);
				else
				commandNotFound();
			}		
			break;
		
		case 9:
		{
			if(isComparable(termIn,"cuznechik")==1)
			musicBoxPlayer(1);
			else
			commandNotFound();
		}
		
			break; 
		default:
		commandNotFound();
		break;
	}
		
	
}

void clearScreen()
{
	for(register char i=0;i<50;i++)
	{
	UDR=0x0C;
	_delay_ms(2);	
		
	}
	
	
}

char isComparable(  char *a, char *b)
{
	while(*a!='\0')
	{
		if(*a!=*b)
		
		return 0;
		a++;
		b++;
		
			
	}
	return 1;
}

void musicBoxPlayer(char song)
{
	sei();
	switch (song)
	{
	case 0:
	imperiamarsh();
	break;
	case 1:
	cuznechik();
	break;	
	case 3:
	onwar();
	break;
		
	}
	
	
}


//Обработка прерываний
ISR(TIMER1_COMPA_vect) //прерывание очистки счётчика ШИМ генератора
{
	TCNT1=0;
	
} 
ISR(USART_RXC_vect) //Прерывание при поступлении символа в ПОРТ UART
{
	cli();
	in=UDR; //запись в переменную
	
	//UCSRB&=~(1<<RXEN); //отключение приёмника
	
	_delay_us(700);
	
	UDR= in; //Вывод введённого символа на терминал
	
	switch (in)
	{
		case 0x0D:
		executComand(termIn);
		termInClear();
		break;
		
		case 0x0A:
		executComand(termIn);
		termInClear();
		break;
		
		case 0x08:
		if(termCount!=0)
		termCount--;
		termIn[termCount]=0;
		break;
		
		default:
		if(termCount<CMDLENGTH)
		{
			termIn[termCount]=in;
			termCount++;
		}
		else
		{
			
			commandNotFound();
			termInClear();
			
		}
		break;
		
		
	}
	
	
	
	
	//UCSRB|=(1<<RXEN); //включение приёмника
	sei();
	
}


