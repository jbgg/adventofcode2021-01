
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "cmd.h"
#include "io.h"

extern struct cmd_t cmds[];

void cmdloop_prompt();
int cmdloop_readline(char l[CMDLINEMAXSIZE]);

int cmd_loop(){
	char l[CMDLINEMAXSIZE];
	int index;

	while(1){
		cmdloop_prompt();
		if(cmdloop_readline(l)){
			io_printf("Bad command\r\n");
		}else
			if(cmd_findcmd(cmds, l, &index)){
				io_printf("Bad command\r\n");
			}else{
				cmds[index].f(l);
			}
	}
	return 0;
}

void cmdloop_prompt(){
	io_printf("> ");
}

int cmdloop_readline(char l[CMDLINEMAXSIZE]){
	char c;
	int i;
	i=0;
	while(1){
		c = io_getchar();
		if(c == '\r' || c == 0){
			io_printf("\r\n");
			l[i] = 0;
			return 0;
		}
		if(isprint(c)){
			l[i] = c;
			io_printf("%c", c);
			i++;
			if(i==CMDLINEMAXSIZE){
				return 1;
			}
		}else if(c == 0x7f && i>0){
			i--;
			io_printf("\b \b");
		}
	}
	return 0;
}

int cmd_findcmd(struct cmd_t cmds[], char l[CMDLINEMAXSIZE], int *ip){
 if(ip==NULL){
  return 1;
 }
 if(l[0] == 0){
  ip[0] = 0;
  return 0;
 }
 char cmdname[CMDLINEMAXSIZE];
 int i;
 if(sscanf(l, "%20s ", cmdname) != 1){
  return 1;
 }
 i=0;
 while(cmds[i].name != 0){
  if(strcmp(cmds[i].name, cmdname) == 0){
   ip[0] = i;
   return 0;
  }
  i++;
 }
 return 1;
}
