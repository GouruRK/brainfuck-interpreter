#include "decode.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "errors.h"
#include "stack.h"
#include "bf.h"

#define SEPARATORS " \t\r\n"

// Value to be update whenever the 'OUTPUT' character has been read
static bool has_print = false;

/**
 * @brief Decode the given character and update the pointer
 * 
 * @param c charactrer to decode
 * @return event associated with the character
 */
static DecodeEvent execute(char c) {
    // The main purpose of this function is to update the pointer on the array
    // and update the values inside the array. This function, based on the given
    // character can also handle IO functions such as printing a character or
    // reading one from stdin.

    // The execute function does not handle loop instances, and only return the
    // associated event code.

    // pointer in the array
    static int pointer = 0;
    
    // array
    static int array[ARRAY_SIZE] = {};
    
    switch (c) {
        case INCREMENT:     // the '>' sign: increment the pointer
            pointer++;
            break;
        case DECREMENT:     // the '<' sign: decrement the pointer
            pointer--;
            break;
        case ADD:               // the '+' sign: increment the value at 
            array[pointer]++;   // the current pointer in the array
            break;
        case SUB:               // the '-' sign: decrement the value at the 
            array[pointer]--;   // current pointer in the array
            break;
        case OUTPUT:                    // the '.' sign: point the character at
            putchar(array[pointer]);    // the current pointer in the array
            has_print = true;
            break;
        case INPUT:                                         // the ',' sign: 
            array[pointer] = getchar();                     // read a character
            if (!array[pointer] || array[pointer] == EOF) { // from stdin and 
                return STOP;                                // set it to the
            }                                               // current pointer
            break;                                          // in the array
        case LOOP_START: // the '[' sign: start a loop
            if (array[pointer]) {  // if the value in the array is non-zero, 
                return BEGIN_LOOP; // then start the loop
            } else {               // else if it is zero, the loop is not
                return SKIP_LOOP;  // computed
            }
            break;
        case LOOP_END:  // the ']' sign: end of a loop
            if (array[pointer]) {   // if the value in the array is non-zero
                return REWIND_LOOP; // the loop needs to be computed again
            } else {                // else we continue decoding
                return CONTINUE;
            }
        default: // character is not a known brainfuck character
            for (int i = 0; SEPARATORS[i] != '\0'; i++) {
                if (c == SEPARATORS[i]) {
                    return OK;
                }
            }
            invalid_bf_char(c);
            return ERROR;
    }
    return CONTINUE;
}

/**
 * @brief Manage event when decoding
 * 
 * @param stack current stack data
 * @param data input stream. Could be either a FILE* stream or a char* string
 * @param code event code to interpret
 * @param index current index
 * @param from_file indicate if stream input is a file or not
 * @return next index to read
 */
static int manage_event(Stack *stack, void* data, DecodeEvent code, long index,
                        bool from_file) {
    // The main idea of this function is to manage the stack based on the 
    // event returned by the 'execute' function and what characters it is
    // reading. This is essencially based on loop management. To prevent having
    // two differents function to handle file stream and string input, we use
    // the 'data' statement and the 'from_file' boolean.
    
    // The 'stack' structure contains an array with and a pointer that indicate
    // the head of the stack. The stack itself contains indexes (or offsets if
    // the input comes from a file) whenever a loop has started. Like that, we
    // can easily know where to go back if we need to compute it again.
    
    if (code == BEGIN_LOOP) {
        // if a loop begins, we need to add the current index in the stack
        if (stack->curlen == stack->maxlen) {
            if (realloc_stack(stack) != OK) {
                allocation_error();
                return ERROR;
            }
        }
        stack->values[stack->curlen++] = index;
        return index;
    } else if (code == SKIP_LOOP) {
        // in some cases we might need to skip a loop (for example, when a loop
        // starts and the value in the array is zero). If so, the loop isn't
        // computed and we can skip directly to the end loop statement
        if (from_file) {
            char c;
            FILE* file = (FILE*)data;
            while ((c = fgetc(file)) != LOOP_END);
            return ftell(file) + 1;
        } else {
            for (; ((char*)data)[index] != LOOP_END; index++);
            return index;
        }
    } else if (code == REWIND_LOOP) {
        // if a loop needs to be computed again (for example, when the array
        // contains a non-zero value on an loop end character), we just start
        // again at the last pushed element
        return stack->values[stack->curlen - 1];
    }
    return index;
}

/**
 * @brief Read the entier input and decode the brainfuck code
 * 
 * @param data input stream. Could be either a FILE* stream or a char* string
 * @param from_file indicate if stream input is a file or not
 * @return EXIT_SUCCESS | EXIT_FAILURE
 */
static int run(void* data, bool from_file) {
    int code;
    Stack stack;
    long index = 0;

    if (init_stack(&stack) != OK) {
        return ERROR;
    }

    if (!from_file) {
        while (((char*)data)[index] != '\0') {
            code = execute(((char*)data)[index]);
            if (code == STOP || code == ERROR) {
                free_stack(&stack);
                return code == STOP ? OK: ERROR;
            }
            index = manage_event(&stack, data, code, index, from_file);
            index++;
        }
    } else {
        char c;
        while ((c = fgetc((FILE*)data)) != EOF) {
            code = execute(c);
            if (code == STOP || code == ERROR) {
                free_stack(&stack);
                return code == STOP ? OK: ERROR;
            }
            index = manage_event(&stack, data, code, index, from_file);
            fseek((FILE*)data, index, SEEK_SET);
        }
    }
    free_stack(&stack);
    return OK;
}

Error decode(char* input) {
    int output;
    FILE* file = fopen(input, "r");
    
    if (!file) {
        output = run(input, false);
    } else {
        output = run(file, true);
        fclose(file);
    }
    
    if (has_print) {
        putchar('\n');
    }
    return output;
}
