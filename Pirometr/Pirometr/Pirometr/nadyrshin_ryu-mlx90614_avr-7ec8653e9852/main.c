//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// Это программное обеспечение распространяется свободно. Вы можете размещать
// его на вашем сайте, но не забудьте указать ссылку на мой YouTube-канал 
// "Электроника в объектике" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// Автор: Надыршин Руслан / Nadyrshin Ruslan
//------------------------------------------------------------------------------
#include <ioavr.h>
#include <inavr.h>
#include "delay\delay.h"
#include "mlx9061x\mlx9061x.h"
#include "hd44780\hd44780.h"
#include "main.h"
#include <stdio.h>


float Ta, To1, To2;

void main( void )
{
  hd44780_init();
  mlx90614_init();

  while (1)
  {
    int8_t ErrTa = mlx9061x_ReadTa(MLX9061X_I2C_ADDR, &Ta);
    int8_t ErrTo1 = mlx9061x_ReadTo1(MLX9061X_I2C_ADDR, &To1);
    //int8_t ErrTo2 = mlx9061x_ReadTo2(I2C1, MLX9061X_I2C_ADDR, &To2);
  
    hd44780_goto_xy(0, 0);
    
    if (ErrTa)
      hd44780_printf("Tamb = Err%d \r\n", ErrTa);
    else
      hd44780_printf("Tamb = %3.1f \r\n", Ta);
    
    if (ErrTo1)
      hd44780_printf("Tobj = Err%d ", ErrTo1);
    else
      hd44780_printf("Tobj = %3.1f ", To1);

    delay_ms(100);
  }
}
