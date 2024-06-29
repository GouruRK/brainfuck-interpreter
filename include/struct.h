#ifndef __INIT_STRUCT__
#define __INIT_STRUCT__

#include <stdbool.h>

#include "errors.h"

#define NB_CHARACTERS 9
#define ARRAY_SIZE 30000

typedef enum {
    INCREMENT  = '>',
    DECREMENT  = '<',
    ADD        = '+',
    SUB        = '-',
    OUTPUT     = '.',
    INPUT      = ',',
    LOOP_START = '[',
    LOOP_END   = ']',
    SPACE      = ' ',
    NEW_LINE   = '\n' 
} Characters;

typedef enum {
    ENCODE,
    DECODE,
    NONE
} Action;

typedef struct {
    bool from_file;
    int curlen;
    int maxlen;
    long *stack;
} BrainFuck;

int init_brainfuck(BrainFuck *bf, bool from_file);
int realloc_brainfuck(BrainFuck *bf);
void free_brainfuck(BrainFuck *bf);

#endif
