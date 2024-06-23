#include "../include/errors.h"

#include <stdio.h>

void print_error(Error err) {
    switch (err) {
        case ALLOCATION_ERROR:
            fprintf(stderr, RED "ALLOCATION ERROR" RESET ": error while"
                            "allocating memory\n");
            break;
        case ARGUMENT_REQUIRED:
            fprintf(stderr, RED "INVALID ARGUMENTS ERROR" RESET ": invalid"
                                "parameters given to the programm\n"
                                "Check" PURPLE "'./brainfuck -h'" RESET 
                                "for more help\n");
            break;
        case INVALID_SENTENCE:
            fprintf(stderr, RED "SENTENCE ERROR " RESET ": the given sentence "
                            "contains invalid brainfuck characters\n"
                            "Check" PURPLE "'./brainfuck -h'" RESET 
                            "for more help\n");
            break;
        default:
            break;
    }
}

void print_help(void) {
    printf("Brainfuck interpreter\n\n"
           "./brainfuck [OPTIONS ...] <FILE | INPUT>\n"
           "\t[-d, --decode] Indicate to decode the given sentence\n"
           "\t[-e, --encode] Indicate to encode the given sentence\n"
           "\t[-h, --help] Print this message\n");
}
