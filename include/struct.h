#ifndef __INIT_STRUCT__
#define __INIT_STRUCT__

#include <stdbool.h>

#include "errors.h"

#define NB_CHARACTERS 9
#define ARRAY_SIZE 30000

typedef enum {
    INCREMENT = '>',
    DECREMENT = '<',
    ADD = '+',
    SUB = '-',
    OUTPUT = '.',
    INPUT = ',',
    LOOP = '[',
    END = ']',
    SPACE = ' ',
} Characters;

typedef enum {
    ENCODE,
    DECODE,
    NONE
} Action;

typedef struct {
    int pointer;
    int index;
    int* stack;
    int depth;
} BrainFuck;

Error init_brainfuck(BrainFuck* bf, int max_stack_size);

void free_brainfuck(BrainFuck* bf);

#endif
