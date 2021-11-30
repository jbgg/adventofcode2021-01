#ifndef _CMD_H_
#define _CMD_H_

#define CMDLINEMAXSIZE 100

struct cmd_t {
        char *name;
        int (*f)(char *args);
};

int cmd_loop();
int cmd_findcmd(struct cmd_t cmds[], char l[CMDLINEMAXSIZE], int *ip);

#endif /* _CMD_H_ */
