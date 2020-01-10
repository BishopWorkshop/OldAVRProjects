/*
 * Заголовочный файл библиотеки CL3641BH
 *
 * Created: 16.08.2017 21:34:57
 * Author : crazy
 */ 

#define SIGMENTPORT PORTA //Порт определения горящих сегментов числа Распределние сегментов 0b DrGFEDCBA
#define SIGMENTDDR DDRA
#define NUMBERPORT PORTC //Порт опредляющий какое число горит
#define NUMBERDDR DDRC  
#define NUM1 4 //Ножка порта ответственная за первое число( с лева на право)
#define NUM2 5 //Ножка порта ответственная за второе число( с лева на право)
#define NUM3 6 //Ножка порта ответственная за третье число( с лева на право)
#define NUM4 7 //Ножка порта ответственная за четвёртое число( с лева на право)

#define SIG_A 7 //Определение на какие сегменты числа выходят разные выводы порта
#define SIG_B 5
#define SIG_C 1
#define SIG_D 3
#define SIG_E 4
#define SIG_F 6
#define SIG_G 0
#define SIG_Dr 2

void initDisplay();//Метод определяющий порты на вывод и устанавливающий их в начальное положение
void cleanDisplay();//Очистка экрана
void showNum(uint16_t num);
void decToBin(uint16_t num, uint16_t showNUM[]);// Метод перевода двоичного числа в десятичный массив
void showDisplayArr(uint16_t outnum[4]);//Метод выводящий данные четырёх значного массива на индикатор
void refactingData(uint16_t *q);//Метод подменяющий значение сигмента на маску сегмента
void showDisplay(); //Повторный водод значения массива
void errMes();//Сообщение об ошибке системы


