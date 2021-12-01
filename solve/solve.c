
#include "input.h"
#include "io.h"

int cmd_solve2(char *args){
 input_t input;
 if(input_init(input)){
  io_printf("init intput failed\r\n");
  return 1;
 }
 int count;
 long d[3];
 long sprev;
 long s;
 int i;
 count = 0;
 sprev = 0;
 for(i=0;i<3;i++){
  if(input_readnumber(input, &d[i])){
   io_printf("readnumber failed\r\n");
   return 1;
  }
  sprev += d[i];
 }
 i = 0;
 /* TODO: create function input_endq(input) */
 while(input->p[0] != 0){
  s = sprev - d[i];
  if(input_readnumber(input, &d[i])){
   io_printf("readnumber failed\r\n");
   return 1;
  }
  s+=d[i];
  if(s > sprev){
   count++;
  }
  sprev = s;
  i = (i+1) % 3;
 }
 io_printf("%d\r\n", count);
 return 0;
}

int cmd_solve1(char *args){
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

 int count = 0;
 while(input->p[0] != 0){
  if(input_readnumber(input, &v) != 0){
   io_printf("error reading number\r\n");
   return 1;
  }
  if(v > prev){
   count++;
  }
  prev = v;
 }
 io_printf("%d\r\n", count);

 return 0;
}

int cmd_input(char *args){
 input_print();
 return 0;
}
