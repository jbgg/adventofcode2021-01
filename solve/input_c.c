#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

#include "input.h"
#include "io.h"

extern char _input[];

void input_print(){
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
