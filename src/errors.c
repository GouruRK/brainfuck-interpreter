#include "../include/errors.h"

#include <stdio.h>

void print_error(Error err) {
    switch (err) {
        case ALLOCATION_ERROR:
            print_allocation_error();
            break;
        case ARGUMENT_REQUIRED:
            print_argument_required_error();
            break;
        case INVALID_SENTENCE:
            print_invalid_sentence_error();
            break;
        default:
            break;
    }
}

void print_allocation_error(void) {
    fprintf(stderr, "%sALLOCATION ERROR%s : error while allocating memory\n", RED, RESET);
}

void print_argument_required_error(void) {
    fprintf(stderr, "%sINVALID ARGUMENTS ERROR%s : invalid parameters given to the programm\n", RED, RESET);
    fprintf(stderr, "Check %s'./brainfuck -h'%s for more help\n", PURPLE, RESET);
}

void print_invalid_sentence_error(void) {
    fprintf(stderr, "%sSENTENCE ERROR%s : the given sentence contains invalid brainfuck characters\n", RED, RESET);
    fprintf(stderr, "Check %s'./brainfuck -h'%s for more help\n", PURPLE, RESET);
}

void print_help(void) {
    printf("Brainfuck interpreter\n\n");
    printf("./brainfuck [-d, --decode sentence] [-e, --encode sentence] [-h, --help]\n");
    printf("\t[-d, --decode] Indicate to decode the given sentence\n");
    printf("\t\tRequire a non null string that contains a brainfuck sentence\n");
    printf("\t\tA sentence must be composed by the characters : '<', '>', ',', '.', '+', '-', '[' and ']'\n");
    printf("\t[-e, --encode] Indicate to encode the given sentence\n");
    printf("\t\tRequire a non null sentence\n");
    printf("\t[-h, --help] Print this message\n");
}
