#include "../include/encode.h"

#include <stdio.h>

#include "../include/errors.h"
#include "../include/struct.h"
#include "../include/tools.h"

#define BUFFER_SIZE 256

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

static void write_new_line(void) {
    putchar(INCREMENT);
    write_n_times(ADD, '\n');
    putchar(OUTPUT);
    putchar(INCREMENT);
}

static int convert(char c, int pointer, int array[]) {
    int delta = c - array[pointer];
    int loop = 10;
    if (array[pointer] == c) {
        putchar(OUTPUT);
    } else if (abs(delta) < loop) {
        if (delta < 0) {
            write_n_times(SUB, -delta);
        } else {
            write_n_times(ADD, delta);
        }
        putchar(OUTPUT);
        array[pointer] += delta;
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
    } else { // means that in order to get the wanted char, it needs to decrease
        putchar(INCREMENT);
        return convert(c, pointer + 1, array);
    }
    return pointer;
}

static int convert_sentence(char* sentence, int array[], int pointer) {
    for (int i = 0; sentence[i] != '\0'; i++) {
        if (sentence[i] == NEW_LINE) {
            write_new_line();
            continue;
        }
        pointer = convert(sentence[i], pointer, array);
    }
    return pointer;
}

Error encode(char* input, int array[]) {
    int pointer = 0;

    FILE* file = fopen(input, "r");
    if (!file) {
        convert_sentence(input, array, pointer);
    } else {
        char buffer[BUFFER_SIZE];
        while (fgets(buffer, BUFFER_SIZE, file)) {
            pointer = convert_sentence(buffer, array, pointer);
        }
        fclose(file);
    }
    putchar('\n');
    return OK;
}
