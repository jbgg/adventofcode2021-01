
#include <stdio.h>
#include <string.h>

#include "io.h"
#include "delay.h"

void system_init();

int main(void){

 system_init();

 io_printf("XX\r\n");

 io_printf("hello world\r\n");

 char c;
 while(1){
  io_printf("> ");
  c = io_getchar();
  io_printf("\r\nc = %c\r\n", c);

  delay(1000);
 }

}
