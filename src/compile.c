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

static void translate_char(char c) {
    switch (c) {
        case TABULATION:
        case NEW_LINE:
        case SPACE:
            break;
        case INCREMENT:
            printf("\tpointer++;\n");
            break;
        case DECREMENT:
            printf("\tpointer--;\n");
            break;
        case ADD:
            printf("\tarray[pointer]++;\n");
            break;
        case SUB:
            printf("\tarray[pointer]--;\n");
            break;
        case OUTPUT:
            printf("\tputchar(array[pointer]);\n");
            break;
        case INPUT:
            printf("\tarray[pointer] = getchar();\n");
            break;
        case LOOP_START:
            printf("\twhile(array[pointer]) {\n");
            break;
        case LOOP_END:
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
