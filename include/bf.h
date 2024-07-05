#ifndef BF_H
#define BF_H

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
    NEW_LINE   = '\n',
    TABULATION = '\t'
} Characters;

#endif
