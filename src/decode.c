#include "../include/decode.h"

#include <stdio.h>
#include <stdbool.h>

#include "../include/errors.h"
#include "../include/struct.h"
#include "../include/tools.h"

static bool has_print = false;

static DecodeEvent execute(int array[], char c) {
    static int pointer = 0;
    switch (c) {
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
                return STOP;
            }
            break;
        case LOOP_START:
            if (array[pointer]) {
                return BEGIN_LOOP;
            } else {
                return SKIP_LOOP;
            }
            break;
        case LOOP_END:
            if (array[pointer]) {
                return REWIND_LOOP;
            } else {
                return CONTINUE;
            }
            break;
        default:
            invalid_bf_char();
            return ERROR;
    }
    return CONTINUE;
}

static int manage_event(BrainFuck *bf, void* data, DecodeEvent code, long index) {
    if (code == BEGIN_LOOP) {
        if (bf->curlen == bf->maxlen) {
            if (!realloc_brainfuck(bf)) {
                allocation_error();
                return ERROR;
            }
        }
        bf->stack[bf->curlen++] = index;
        return index;
    } else if (code == SKIP_LOOP) {
        char c;
        if (bf->from_file) {
            FILE* file = (FILE*)data;
            while ((c = fgetc(file)) != LOOP_END);
            return ftell(file);
        } else {
            for (; ((char*)data)[index] != ']'; index++);
            return index;
        }
    } else if (code == REWIND_LOOP) {
        return bf->stack[bf->curlen - 1];
    } 
    return index;
}

static int run(int array[], void* data, bool from_file) {
    DecodeEvent code;
    BrainFuck bf;
    long index = 0;

    if (!init_brainfuck(&bf, from_file)) {
        return 0;
    }

    if (!from_file) {
        while (((char*)data)[index] != '\0') {
            code = execute(array, ((char*)data)[index]);
            if (code == STOP || code == ERROR) {
                free_brainfuck(&bf);
                return code == STOP ? 0: 1;
            }
            index = manage_event(&bf, data, code, index);
            index++;
        }
    } else {
        char c;
        while ((c = fgetc((FILE*)data)) != EOF) {
            code = execute(array, c);
            if (code == STOP || code == ERROR) {
                free_brainfuck(&bf);
                return code == STOP ? 0: 1;
            }
            index = manage_event(&bf, data, code, index) + 1;
            fseek((FILE*)data, index, SEEK_SET);
        }
    }
    free_brainfuck(&bf);
    return 0;
}

Error decode(char* input, int array[]) {
    FILE* file = fopen(input, "r");
    int output;
    if (!file) {
        output = run(array, input, false);
    } else {
        output = run(array, file, true);
        fclose(file);
    }
    if (has_print) {
        putchar('\n');
    }
    return output;
}
