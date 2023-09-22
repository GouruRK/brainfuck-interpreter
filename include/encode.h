#ifndef __INIT_ENCODE__
#define __INIT_ENCODE__

#include "errors.h"

void write_n_times(char c, int n);

void write_loop_entry(void);

void write_loop_end(void);

int convert(char c, int pointer, int array[]);

Error encode(char* sentence, int array[]);

#endif
