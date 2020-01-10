//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// Это программное обеспечение распространяется свободно. Вы можете размещать
// его на вашем сайте, но не забудьте указать ссылку на мой YouTube-канал 
// "Электроника в объектике" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// Автор: Надыршин Руслан / Nadyrshin Ruslan
//------------------------------------------------------------------------------
#ifndef _HD44780_H
#define _HD44780_H


// Размеры индикатора
#define HD44780_ROWS            2       // Кол-во строк
#define HD44780_COLS            16      // Кол-во столбцов

// Параметры обмена с индикатором
#define HD44780_4bitMode        1       // 4-бит режим (иначе 8-бит)  
#define HD44780_WaitBisyFlag    1       // Опрос флага занятости контроллера дисплея (иначе программная задержка)        
#define HD44780_ShortDelayUs    2       // Короткая задержка (между фронтами E)   
#define HD44780_BisyDelayUs     50      // Задержка ожидания освобождения контроллера дисплея (если HD44780_WaitBisyFlag=1)   

#define CP1251                  1251
#define CP866                   866
#define SOURCE_CODEPAGE         CP1251  // Кодировка файлов исходных кодов (для перекодирования кириллицы)


//// Ноги, управляющие интерфейсом hd44780
// Сигнал RS
#define HD44780_RS_Port         PORTC
#define HD44780_RS_DDR          DDRC
#define HD44780_RS_Mask         (1<<0)
// Сигнал RW
#define HD44780_RW_Port         PORTC
#define HD44780_RW_DDR          DDRC
#define HD44780_RW_Mask         (1<<1)
// Сигнал E
#define HD44780_E_Port          PORTC
#define HD44780_E_DDR           DDRC
#define HD44780_E_Mask          (1<<2)
// Ноги данных параллельного интерфейса hd44780
#define HD44780_Data_Port       PORTD
#define HD44780_Data_Pin        PIND
#define HD44780_Data_DDR        DDRD
#if HD44780_4bitMode
#define HD44780_Data_Shift      0       // Битовый сдвиг параллельной шины влево по порту МК
#endif


void hd44780_init(void);
void hd44780_write_cmd(unsigned char Data);
void hd44780_write_data(unsigned char Data);
void hd44780_write_buff(char *pBuff, char Len);
void hd44780_clear(void);
void hd44780_goto_xy(char Row, char Col);
void hd44780_puts(char *str);
void hd44780_printf(const char *format, ...);

#endif