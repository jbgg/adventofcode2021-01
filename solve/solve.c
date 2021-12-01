
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

#include "io.h"

extern char _input[];

struct _input_t {
 char *p;
};

typedef struct _input_t input_t[1];

int input_init(input_t);
int input_readnumber(input_t input, long *v);

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
 char *p;
 p = _input;
 while(p[0] != 0){
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
 input->p = _input;
 return 0;
}

int input_readnumber(input_t input, long *v){
 char *q;
 if(v == NULL){
  return 1;
 }
 errno = 0;
 v[0] = strtol(input->p, &q, 10);
 if(errno != 0 || input->p == q){
  return 1;
 }
 /* skip space characters */
 while(isspace(q[0])){
  q++;
 }
 input->p = q;
 return 0;
}
