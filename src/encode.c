#include "encode.h"

#include <stdio.h>

#include "errors.h"
#include "bf.h"

#define BUFFER_SIZE 256
#define LOOP 10

#define ABS(a) (((a) < 0) ? (-(a)): (a))

/**
 * @brief Write n times the given character
 * 
 * @param c character to print
 * @param n number of time to print
 */
static void write_n_times(char c, int n) {
    for (int i = 0; i < n; i++) putchar(c);
}

/**
 * @brief Write brainfuck code when a loop starts
 * 
 */
static void write_loop_entry(void) {
    putchar(LOOP_START);
    putchar(INCREMENT);
}

/**
 * @brief Write brainfuck code when a loop ends
 * 
 */
static void write_loop_end(void) {
    putchar(DECREMENT);
    putchar(SUB);
    putchar(LOOP_END);
}

/**
 * @brief Convert the given character to brainfuck code
 * 
 * @param c character to convert
 * @param pointer current pointer in the array
 * @return next pointer
 */
static void convert(char c) {
    // This function convert a character in brainfuck code. All character
    // representation is coded using their ASCII code.
    // To prevent writing too much time the same character, this code uses
    // loop strategies and look in the array if the value on the pointer is 
    // close enough to the character we want to print.
    // If the ASCII code is too far, its easier to start from zero and loop n
    // times to go to the closest possible (each time we go through a loop
    // iteration, the value in the array increments by ten) and then we
    // adjust it. If the current value in the array is close to the one we want,
    // then adjust it directly.

    // brainfuck core array
    static int array[ARRAY_SIZE] = {};

    // brainfuck pointer in the array
    static int pointer = 0;

    // delta between the value we want and the one we already have in the array
    int delta = c - array[pointer];
    
    if (array[pointer] == c) {
        // if equals, then output it
        putchar(OUTPUT);
    } else if (ABS(delta) < LOOP) {
        // if too close, adjust it
        if (delta < 0) {
            write_n_times(SUB, -delta);
        } else {
            write_n_times(ADD, delta);
        }
        array[pointer] += delta;
        putchar(OUTPUT);
    } else {
        if (array[pointer]) {
            // if the value is non-zero, go to the next zero value
            putchar(INCREMENT);
            pointer++;
        }
        // the value is too far, loop it and then adjust
        write_n_times(ADD, c / LOOP);
        write_loop_entry();
        write_n_times(ADD, LOOP);
        write_loop_end();
        putchar(INCREMENT);
        write_n_times(ADD, c % LOOP);
        putchar(OUTPUT);
        pointer++;
        array[pointer] = c;
    }
}

/**
 * @brief Convert a full sentence
 * 
 * @param sentence sentence to convert
 * @param pointer pointer in the array
 * @return next pointer
 */
static void convert_sentence(char* sentence) {
    for (int i = 0; sentence[i] != '\0'; i++) {
        // convert each character of the sentence
        convert(sentence[i]);
    }
}

Error encode(char* input) {
    FILE* file = fopen(input, "r");
    
    if (!file) {
        convert_sentence(input);
    } else {
        char buffer[BUFFER_SIZE];
        while (fgets(buffer, BUFFER_SIZE, file)) {
            convert_sentence(buffer);
        }
        fclose(file);
    }
    putchar('\n');
    return OK;
}
