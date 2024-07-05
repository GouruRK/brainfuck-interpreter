#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

#include "errors.h"

typedef struct {
    int curlen;
    int maxlen;
    long *values;
} Stack;

/**
 * @brief Initiate brainfuck structure with the default values
 * 
 * @param bf structure to initiate
 * @param from_file indicate if the the input is a file or not
 * @return error code
 */
Error init_stack(Stack *stack);

/**
 * @brief Realloc stack for given brainfuck structure
 * 
 * @param bf structure to realloc the stack
 * @return
 */
Error realloc_stack(Stack *stack);

/**
 * @brief Free allocated memory for stack
 * 
 * @param bf structure to free
 */
void free_stack(Stack *stack);

#endif
