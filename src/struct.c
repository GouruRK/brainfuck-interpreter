#include "struct.h"

#include <stdbool.h>
#include <stdlib.h>

#include "errors.h"

#define DEFAULT_LENGTH 5

Error init_brainfuck(BrainFuck *bf, bool from_file) {
    bf->stack = (long*)malloc(sizeof(long)*DEFAULT_LENGTH);
    if (!(bf->stack)) {
        allocation_error();
        return ALLOCATION_ERROR;
    }
    bf->curlen = 0;
    bf->maxlen = DEFAULT_LENGTH;
    bf->from_file = from_file;
    return OK;
}

Error realloc_brainfuck(BrainFuck *bf) {
    long* temp = bf->stack;
    temp = realloc(temp, sizeof(long)*(bf->maxlen + DEFAULT_LENGTH));
    if (!temp) {
        allocation_error();
        return ALLOCATION_ERROR;
    }
    bf->stack = temp;
    bf->maxlen += DEFAULT_LENGTH;
    return OK;
}

void free_brainfuck(BrainFuck *bf) {
    if (bf && bf->stack) {
        free(bf->stack);
        bf->curlen = 0;
        bf->maxlen = 0;
    }
}
