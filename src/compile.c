#include "compile.h"

#include <stdio.h>

#include "bf.h"
#include "errors.h"

#define BUFFER_SIZE 256

static void print_header(void) {
    printf("// Brainfuck code compile using https://github.com/GouruRK/"
           "brainfuck-interpreter\n\n"
           "#include <stdio.h>\n\n"
           "int main(void) {\n"
           "\tint pointer = 0;\n"
           "\tint array[30000] = {};\n\n");
}

static void print_footer(void) {
    printf("\treturn 0;\n"
           "}\n");
}

static int update_values(int n) {
    if (n) {
        printf("\tarray[pointer] += %d;\n", n);
    }
    return 0;
}

static int update_pointer(int n) {
    if (n) {
        printf("\tpointer += %d;\n", n);
    }
    return 0;
}

static void translate_char(char c) {
    static int pointer_acc = 0;
    static int values_acc = 0;

    switch (c) {
        case TABULATION:
        case NEW_LINE:
        case SPACE:
            break;
        case INCREMENT:
            values_acc = update_values(values_acc);
            pointer_acc++;
            break;
        case DECREMENT:
            values_acc = update_values(values_acc);
            pointer_acc--;
            break;
        case ADD:
            pointer_acc = update_pointer(pointer_acc);
            values_acc++;
            break;
        case SUB:
            pointer_acc = update_pointer(pointer_acc);
            values_acc--;
            break;
        case OUTPUT:
            pointer_acc = update_pointer(pointer_acc);
            values_acc = update_values(values_acc);
            printf("\tputchar(array[pointer]);\n");
            break;
        case INPUT:
            pointer_acc = update_pointer(pointer_acc);
            values_acc = update_values(values_acc);
            printf("\tarray[pointer] = getchar();\n");
            break;
        case LOOP_START:
            pointer_acc = update_pointer(pointer_acc);
            values_acc = update_values(values_acc);
            printf("\twhile(array[pointer]) {\n");
            break;
        case LOOP_END:
            pointer_acc = update_pointer(pointer_acc);
            values_acc = update_values(values_acc);
            printf("\t}\n");
            break;
        default:
            // TODO: manage non brainfuck characters
            break;
    }
}

static void convert_sentence(char* string) {
    for (int i = 0; string[i] != '\0'; i++) {
        translate_char(string[i]);
    }
}

Error compile(char* input) {
    FILE* file = fopen(input, "r");
    print_header();

    if (!file) {
        convert_sentence(input);
    } else {
        char buffer[BUFFER_SIZE];
        while (fgets(buffer, BUFFER_SIZE, file)) {
            convert_sentence(buffer);
        }
        fclose(file);
    }
    print_footer();
    return OK;
}
