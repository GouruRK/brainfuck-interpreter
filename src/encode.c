#include "encode.h"

#include <stdio.h>

#include "errors.h"
#include "bf.h"

#define BUFFER_SIZE 256

#define ABS(a) (((a) < 0) ? (-(a)): (a))

static void write_n_times(char c, int n) {
    for (int i = 0; i < n; i++) {
        putchar(c);
    }
}

static void write_loop_entry(void) {
    putchar(LOOP_START);
    putchar(INCREMENT);
}

static void write_loop_end(void) {
    putchar(DECREMENT);
    putchar(SUB);
    putchar(LOOP_END);
}

static void write_tabulation(void) {
    putchar(INCREMENT);
    write_n_times(ADD, '\t');
    putchar(OUTPUT);
    putchar(INCREMENT);
}

static int convert(char c, int pointer, int array[]) {
    int delta = c - array[pointer];
    int loop = 10;
    if (array[pointer] == c) {
        putchar(OUTPUT);
    } else if (ABS(delta) < loop) {
        if (delta < 0) {
            write_n_times(SUB, -delta);
        } else {
            write_n_times(ADD, delta);
        }
        array[pointer] += delta;
        putchar(OUTPUT);
    } else if (loop < delta) { // means that in order to get the wanted char, it needs to add values        
        if (array[pointer]) {
            putchar(DECREMENT);
            pointer++;
        }
        int init = delta / loop;
        write_n_times(ADD, init);
        write_loop_entry();
        write_n_times(ADD, loop);
        write_loop_end();
        putchar(INCREMENT);
        write_n_times(ADD, delta % 10);
        putchar(OUTPUT);
        pointer++;
        array[pointer] = c;
    } else if (c == loop) {
        putchar(INCREMENT);
        write_n_times(ADD, c);
        putchar(OUTPUT);
        putchar(INCREMENT);
        pointer += 2;
    } else { // means that in order to get the wanted char, it needs to decrease
        putchar(INCREMENT);
        return convert(c, pointer + 1, array);
    }
    return pointer;
}

static int convert_sentence(char* sentence, int array[], int pointer) {
    for (int i = 0; sentence[i] != '\0'; i++) {
        if (sentence[i] == '\t') {
            write_tabulation();
            pointer += 2;
        } else {
            pointer = convert(sentence[i], pointer, array);
        }
    }
    return pointer;
}

Error encode(char* input) {
    int pointer = 0, array[ARRAY_SIZE] = {};
    FILE* file = fopen(input, "r");
    
    if (!file) {
        convert_sentence(input, array, pointer);
    } else {
        char buffer[BUFFER_SIZE];
        while (fgets(buffer, BUFFER_SIZE, file)) {
            pointer = convert_sentence(buffer, array, pointer);
        }
        if (file != stdin) {
            fclose(file);
        }
    }
    putchar('\n');
    return OK;
}
