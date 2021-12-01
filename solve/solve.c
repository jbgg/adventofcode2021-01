
#include <stdio.h>

#include "io.h"

extern char _binary_solve_input_end[];
extern char _binary_solve_input_start[];

struct _input_t {
 char *p;
};

typedef struct _input_t input_t[1];

int input_init(input_t);
int input_readnumber(input_t input, int *v);

int cmd_solve(char *args){
 io_printf("solve...\r\n");

 input_t input;

 if(input_init(input)){
  io_printf("init intput failed\r\n");
  return 1;
 }

 int prev;
 //int v;
 if(input_readnumber(input, &prev) != 0){
  io_printf("error reading first number\r\n");
  return 1;
 }
 io_printf("prev = %d\r\n", prev);

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

int input_init(input_t input){
 input->p = _binary_solve_input_start;
 return 0;
}

int input_readnumber(input_t input, int *v){
 if(v == NULL){
  return 1;
 }
 if(sscanf(input->p, "%d", v) != 1){
  return 1;
 }
 return 0;
}
