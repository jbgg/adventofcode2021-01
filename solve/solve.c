
#include "input.h"
#include "io.h"

int cmd_solve(char *args){
 io_printf("solve...\r\n");

 input_t input;

 if(input_init(input)){
  io_printf("init intput failed\r\n");
  return 1;
 }

 long prev;
 long v;

 if(input_readnumber(input, &prev) != 0){
  io_printf("error reading first number\r\n");
  return 1;
 }

 io_printf("prev = %d\r\n", prev);

 while(input->p[0] != 0){
  if(input_readnumber(input, &v) != 0){
   io_printf("error reading number\r\n");
   return 1;
  }
  io_printf("v = %d\r\n", v);
 }
 return 0;
}

int cmd_input(char *args){
 input_print();
 return 0;
}

