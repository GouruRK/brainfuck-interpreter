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

#endif
