#include "../include/struct.h"

#include <stdbool.h>
#include <stdlib.h>

#define DEFAULT_LENGTH 5

int init_brainfuck(BrainFuck *bf, bool from_file) {
    bf->stack = (long*)malloc(sizeof(long)*DEFAULT_LENGTH);
    if (!(bf->stack)) {
        return 0;
    }
    bf->curlen = 0;
    bf->maxlen = DEFAULT_LENGTH;
    bf->from_file = from_file;
    return 1;
}

int realloc_brainfuck(BrainFuck *bf) {
    long* temp = bf->stack;
    temp = realloc(temp, sizeof(long)*(bf->maxlen + DEFAULT_LENGTH));
    if (!temp) {
        return 0;
    }
    bf->stack = temp;
    bf->maxlen += DEFAULT_LENGTH;
    return 1;
}

void free_brainfuck(BrainFuck *bf) {
    if (bf && bf->stack) {
        free(bf->stack);
        bf->curlen = 0;
        bf->maxlen = 0;
    }
}
