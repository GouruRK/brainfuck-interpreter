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
    NEW_LINE   = '\n',
    TABULATION = '\t'
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

/**
 * @brief Initiate brainfuck structure with the default values
 * 
 * @param bf structure to initiate
 * @param from_file indicate if the the input is a file or not
 * @return error code
 */
Error init_brainfuck(BrainFuck *bf, bool from_file);

/**
 * @brief Realloc stack for given brainfuck structure
 * 
 * @param bf structure to realloc the stack
 * @return
 */
Error realloc_brainfuck(BrainFuck *bf);

/**
 * @brief Free allocated memory for stack
 * 
 * @param bf structure to free
 */
void free_brainfuck(BrainFuck *bf);

#endif
