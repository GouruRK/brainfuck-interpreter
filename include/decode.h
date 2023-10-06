#ifndef __INIT_DECODE__
#define __INIT_DECODE__

#include <stdbool.h>

#include "errors.h"
#include "struct.h"

#define VALID_CHARACTERS (Characters[NB_CHARACTERS]){INCREMENT, DECREMENT, ADD, SUB, OUTPUT, INPUT, LOOP, END, SPACE}

bool is_char_valid(char c);

bool is_sentence_valid(char* sentence, int* max_stack_size);

void execute(BrainFuck* bf, char* sentence, int array[], bool* print);

Error decode(char* sentence, int array[]);

#endif
