
#include <stdio.h>
#include <string.h>

#include "io.h"
#include "delay.h"
#include "cmd.h"

int cmd_void(char *args);
int cmd_test(char *args);
int cmd_solve1(char *args);
int cmd_solve2(char *args);
int cmd_input(char *args);

struct cmd_t cmds[] = {
 {"", cmd_void},
 {"test", cmd_test},
 {"solve1", cmd_solve1},
 {"solve2", cmd_solve2},
 {"input", cmd_input},
 {0,}
};

void system_init();

int main(void){

 system_init();

 io_printf("XX\r\n");

 cmd_loop();

 while(1)
  ;

 return 0;
}

int cmd_void(char *args){
 return 0;
}

int cmd_test(char *args){
 io_printf("Hey!!\r\n");
 return 0;
}
