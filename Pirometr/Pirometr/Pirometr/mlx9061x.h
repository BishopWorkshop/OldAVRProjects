//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// Это программное обеспечение распространяется свободно. Вы можете размещать
// его на вашем сайте, но не забудьте указать ссылку на мой YouTube-канал 
// "Электроника в объектике" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// Автор: Надыршин Руслан / Nadyrshin Ruslan
//------------------------------------------------------------------------------
#ifndef _MLX9061X_H
#define _MLX9061X_H

#include "types.h"
#include "i2cm.h"


#define MLX9061X_I2C_ADDR       0xB4    // I2C-адрес mlx9061x (по-умолчанию 0xB4)
#define MLX9061X_I2C_CLOCK      100000  // Допустимые для mlx90614 значения - от 10К до 100К
#define MLX9061X_I2C_TO         1000    // Таймаут операций с периферией i2c (в тиках)

// Константы, обозначающие ошибки при чтении RAM из mlx9061x
#define MLX9061X_ERR_Ok         I2C_ERR_Ok
#define MLX9061X_ERR_NotConnect I2C_ERR_NotConnect
#define MLX9061X_ERR_BadChksum  I2C_ERR_BadChksum
#define MLX9061X_ERR_HWerr      I2C_ERR_HWerr
#define MLX9061X_ERR_MeasErr    -10                     // Ошибка измерения температуры



// Процедура инициализации интерфейса обмена с mlx9061x
void mlx90614_init(void);
// Функция чтения 1 регистра из mlx9061x
int8_t mlx9061x_ReadReg(uint8_t slave_addr, uint8_t RamAddr, uint16_t *pTemp);

int8_t mlx9061x_ReadTa(uint8_t slave_addr, uint16_t *pTemp);
int8_t mlx9061x_ReadTo1(uint8_t slave_addr, uint16_t *pTemp);
int8_t mlx9061x_ReadTo2(uint8_t slave_addr, uint16_t *pTemp);


#endif