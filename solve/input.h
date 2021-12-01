#ifndef __INPUT_H__
#define __INPUT_H__

struct _input_t {
 char *p;
};

typedef struct _input_t input_t[1];

void input_print();
int input_init(input_t);
int input_readnumber(input_t input, long *v);

#endif /* __INPUT_H__ */
