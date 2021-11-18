#include <stdio.h>
#include <stdarg.h>

#include "stm32l4xx_hal.h"

extern UART_HandleTypeDef UartHandle;

void io_printf(const char *fmt, ...){
 va_list argp;
 char str[200];
 int nsize;
 va_start(argp, fmt);
 nsize = vsnprintf(str, 200, fmt, argp);
 if(0 < nsize || nsize >= 200){
  HAL_UART_Transmit(&UartHandle, (uint8_t*)str, nsize, 0xffffffff);
 }
 va_end(argp);
}

char io_getchar(){
 char c;
 __HAL_UART_CLEAR_OREFLAG(&UartHandle);
 HAL_UART_Receive(&UartHandle, (uint8_t *)&c, 1, 0xffffffff);
 return c;
}
