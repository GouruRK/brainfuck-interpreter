#include <stdbool.h>
#include <stdlib.h>

#include "../include/struct.h"
#include "../include/errors.h"

Error init_brainfuck(BrainFuck* bf, int max_stack_size) {
    bf->pointer = 0;
    bf->index = 0;
    bf->depth = 0;
    bf->stack = (int*)malloc(sizeof(int) * max_stack_size);
    if (!(bf->stack)) {
        return ALLOCATION_ERROR;
    }
    return OK;
}

void free_brainfuck(BrainFuck* bf) {
    if (bf->stack) {
        free(bf->stack);
    }
}
