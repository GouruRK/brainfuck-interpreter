#include "../include/decode.h"

#include <stdio.h>
#include <stdbool.h>

#include "../include/errors.h"
#include "../include/struct.h"
#include "../include/tools.h"

bool is_char_valid(char c) {
    for (int i = 0; i < NB_CHARACTERS; i++) {
        if (c == VALID_CHARACTERS[i]) {
            return true;
        }
    }
    return false;
}

bool is_sentence_valid(char* sentence, int* max_stack_size) {
    int current_stack_size = 0;
    int parenthesis = 0;
    for (int i = 0; sentence[i] != '\0'; i++) {
        if (!is_char_valid(sentence[i])) {
            return false;
        }
        if (sentence[i] == '[') {
            parenthesis++;
            current_stack_size = max(current_stack_size, parenthesis);
        } else if (sentence[i] == ']') {
            parenthesis--;
        }
        if (parenthesis < 0) {
            return false;
        }
    }
    *max_stack_size = current_stack_size;
    return !parenthesis;
}

void execute(BrainFuck* bf, char* sentence, int array[], bool* print) {
    switch (sentence[bf->index]) {
        case ' ':
            break;
        case '>':
            bf->pointer++;
            break;
        case '<':
            bf->pointer--;
            break;
        case '+':
            array[bf->pointer]++;
            break;
        case '-':
            array[bf->pointer]--;
            break;
        case '.':
            putchar(array[bf->pointer]);
            *print = true;
            break;
        case ',':
            array[bf->pointer] = getchar();
            break;
        case '[':
            if (array[bf->pointer]) {
                bf->stack[bf->depth++] = bf->index;
            } else {
                for (; sentence[bf->index] != ']'; bf->index++);
            }
            break;
        case ']':
            if (array[bf->pointer]) {
                bf->index = bf->stack[bf->depth - 1];
            } else {
                bf->depth--;
            }
            break;
    }
    bf->index++;
}

Error decode(char* sentence, int array[]) {
    int max_stack_size;
    BrainFuck bf;
    bool print = false;
    if (!is_sentence_valid(sentence, &max_stack_size)) {
        return INVALID_SENTENCE;
    }
    if (init_brainfuck(&bf, max_stack_size) != OK) {
        return ALLOCATION_ERROR;
    }
    while (sentence[bf.index] != '\0') {
        execute(&bf, sentence, array, &print);
    }
    if (print) {
        putchar('\n');
    }
    free_brainfuck(&bf);
    return OK;
}
