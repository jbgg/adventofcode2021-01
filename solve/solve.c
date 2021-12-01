
#include "io.h"

//extern char _binary_solve_input_size[];
extern char _binary_solve_input_end[];
extern char _binary_solve_input_start[];

int cmd_solve(char *args){
 io_printf("solve...\r\n");
 return 0;
}

int cmd_input(char *args){
 char *p;
 p = _binary_solve_input_start;
 while(p != _binary_solve_input_end){
  if(p[0] == '\n'){
   io_printf("\r\n");
  }else{
   io_printf("%c", p[0]);
  }
  p++;
 }
 return 0;
}
