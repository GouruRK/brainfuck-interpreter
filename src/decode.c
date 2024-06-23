#include "../include/decode.h"

#include <stdio.h>
#include <stdbool.h>

#include "../include/errors.h"
#include "../include/struct.h"
#include "../include/tools.h"

static bool has_print = false;

static int run(char* sentence, int array[], int index, int last_index) {
    static int pointer = 0;

    while (sentence[index] != '\0') {
        switch (sentence[index]) {
            case NEW_LINE:
            case SPACE:
                break;
            case INCREMENT:
                pointer++;
                break;
            case DECREMENT:
                pointer--;
                break;
            case ADD:
                array[pointer]++;
                break;
            case SUB:
                array[pointer]--;
                break;
            case OUTPUT:
                putchar(array[pointer]);
                has_print = true;
                break;
            case INPUT:
                array[pointer] = getchar();
                if (!array[pointer] || array[pointer] == EOF) {
                    return -1;
                }
                break;
            case LOOP_START:
                if (array[pointer]) {
                    index = run(sentence, array, index + 1, index);
                    if (index == -1) return -1; 
                } else {
                    for (; sentence[index] != ']'; index++);
                }
                break;
            case LOOP_END:
                if (array[pointer]) {
                    index = last_index;
                } else {
                    return index;
                }
                break;
            default:
                print_error(INVALID_SENTENCE);
                return -1;
        }
        index++;
    }
    return index;
}

Error decode(char* sentence, int array[]) {
    int err;
    if ((err = run(sentence, array, 0, 0)) == -1) {    
        return INVALID_SENTENCE;
    }
    if (has_print) {
        putchar('\n');
    }
    return OK;
}
