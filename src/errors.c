#include "../include/errors.h"

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

void invalid_bf_char(void) {
    fprintf(stderr, RED "SENTENCE ERROR " RESET ": the given sentence "
                    "contains invalid brainfuck characters\n"
                    "Check" PURPLE "'./brainfuck -h'" RESET 
                    "for more help\n");
}

void print_help(void) {
    printf("Brainfuck interpreter\n\n"
           "./brainfuck [OPTIONS ...] <FILE | INPUT>\n"
           "\t[-d, --decode] Indicate to decode the given sentence\n"
           "\t[-e, --encode] Indicate to encode the given sentence\n"
           "\t[-h, --help] Print this message\n");
}
