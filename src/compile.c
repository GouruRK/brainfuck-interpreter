#include "compile.h"

#include <stdio.h>

#include "bf.h"
#include "errors.h"

#define BUFFER_SIZE 256

/**
 * @brief Print C-file header and start of main function
 * 
 */
static void print_header(void) {
    printf("// Brainfuck code compiled using https://github.com/GouruRK/"
           "brainfuck-interpreter\n\n"
           "#include <stdio.h>\n\n"
           "int main(void) {\n"
           "\tint pointer = 0;\n"
           "\tint array[30000] = {};\n\n");
}

/**
 * @brief Print C-file footer
 * 
 */
static void print_footer(void) {
    printf("\treturn 0;\n"
           "}\n");
}

/**
 * @brief Update the value in the array by adding 'n'
 * 
 * @param n value to add to the array
 * @return next value to add
 */
static int update_values(int n) {
    if (n) {
        printf("\tarray[pointer] += %d;\n", n);
    }
    return 0;
}

/**
 * @brief Update the pointer value by adding 'n'
 * 
 * @param n value to add to the pointer
 * @return next value to add
 */
static int update_pointer(int n) {
    if (n) {
        printf("\tpointer += %d;\n", n);
    }
    return 0;
}

/**
 * @brief Transform the given character into C code
 * 
 * @param c character to translate
 * @return error code
 */
static Error translate_char(char c) {
    // To translate brainfuck code to C, this function basically reproduce the
    // behaviour of the "decode" function. The file produced contains two main
    // variables : the array and an index that correspond to the brainfuck
    // pointer. Based on the reading character, we either update the pointer,
    // the value in the array and so on. The loops are while-loops and it uses
    // stdio functions 'getchar' and 'putchar' for IO interactions.

    // To prevent having a lot of incrementations by one on both pointer and 
    // values, this function uses two static variables written below to 
    // accumulate the values and then write the full incrementation. For
    // example, the brainfuck code '>>>' will not be 'pointer++;pointer++;
    // pointer++;' but 'pointer += 3;'. It prints the values when an other
    // character is read

    // accumulator of the array index
    static int pointer_acc = 0;

    // accumulator for the array values
    static int values_acc = 0;

    switch (c) {
        case TABULATION: // 
        case NEW_LINE:   // Characters to skip
        case SPACE:      // 
            break;
        case INCREMENT:  // '>'
            values_acc = update_values(values_acc);
            pointer_acc++;
            break;
        case DECREMENT: // '<'
            values_acc = update_values(values_acc);
            pointer_acc--;
            break;
        case ADD:       // '+'
            pointer_acc = update_pointer(pointer_acc);
            values_acc++;
            break;
        case SUB:       // '-'
            pointer_acc = update_pointer(pointer_acc);
            values_acc--;
            break;
        case OUTPUT:    // '.'
            pointer_acc = update_pointer(pointer_acc);
            values_acc = update_values(values_acc);
            printf("\tputchar(array[pointer]);\n");
            break;
        case INPUT:     // ','
            pointer_acc = update_pointer(pointer_acc);
            values_acc = update_values(values_acc);
            printf("\tarray[pointer] = getchar();\n");
            break;
        case LOOP_START:    // '['
            pointer_acc = update_pointer(pointer_acc);
            values_acc = update_values(values_acc);
            printf("\twhile(array[pointer]) {\n");
            break;
        case LOOP_END:      // ']'
            pointer_acc = update_pointer(pointer_acc);
            values_acc = update_values(values_acc);
            printf("\t}\n");
            break;
        default:
            invalid_bf_char();
            return INVALID_SENTENCE;
    }
    return OK;
}

/**
 * @brief Convert a string of brainfuck code
 * 
 * @param string string to convert
 * @return error code
 */
static Error convert_sentence(char* string) {
    for (int i = 0; string[i] != '\0'; i++) {
        if (translate_char(string[i]) != OK) {
            return INVALID_SENTENCE;
        }
    }
    return OK;
}

Error compile(char* input) {
    FILE* file = fopen(input, "r");
    print_header();

    if (!file) {
        if (convert_sentence(input) != OK) {
            return INVALID_SENTENCE;
        }
    } else {
        char buffer[BUFFER_SIZE];
        while (fgets(buffer, BUFFER_SIZE, file)) {
            if (convert_sentence(buffer) != OK) {
                fclose(file);
                return INVALID_SENTENCE;
            }
        }
        fclose(file);
    }
    print_footer();
    return OK;
}
