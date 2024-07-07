#include "errors.h"

#include <stdio.h>

void allocation_error(void) {
    fprintf(stderr, RED "ALLOCATION ERROR" RESET ": error while"
                    "allocating memory\n");
}

void argument_required(void) {
    fprintf(stderr, RED "INVALID ARGUMENTS ERROR" RESET ": invalid"
                    "parameters given to the programm\n"
                    "Check" PURPLE "'./brainfuck -h'" RESET 
                    "for more help\n");
}

void invalid_bf_char(char c) {
    fprintf(stderr, RED "SENTENCE ERROR " RESET ": the given sentence "
                    "contains an invalid brainfuck character: " CYAN"'%c'\n"
                    RESET "Check" PURPLE "'./brainfuck -h'" RESET 
                    "for more help\n", c);
}
