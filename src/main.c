#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "encode.h"
#include "errors.h"
#include "decode.h"
#include "compile.h"
#include "parser.h"

typedef Error (*action_fun)(char*);

/**
 * @brief Print help message
 * 
 */
static void print_help(void) {
    printf("Brainfuck interpreter\n\n"
           "./brainfuck [OPTIONS ...] <FILE | INPUT>\n"
           "\t-d, --decode\tDecode the brainfuck code to ASCII\n"
           "\t-e, --encode\tEncode the ASCII input into brainfuck code\n"
           "\t-c, --compile\tCompile the brainfuck code to C\n"
           "\t-h, --help\tPrint this message\n");
}

static int manage_input(Args args) {
    static const action_fun fun[] = {
        [ENCODE] = encode,
        [DECODE] = decode,
        [COMPILE] = compile
    };
    return fun[args.act](args.input);
}

int main(int argc, char* argv[]) {
    Args args = init_args();
    if (parse(&args, argc, argv) != OK) {
        return 1;
    }
    if (args.help) {
        print_help();
        return 0;
    }
    return manage_input(args) == OK ? EXIT_SUCCESS: EXIT_FAILURE;
}
