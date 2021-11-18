
#include <stdio.h>
#include <string.h>

#include "io.h"

void system_init();

int main(void){

 system_init();

 io_printf("XX\r\n");

 io_printf("hello world\r\n");

 char c;
 io_printf("> ");
 c = io_getchar();
 io_printf("\r\nc = %c\r\n", c);

 while(1)
  ;
}
