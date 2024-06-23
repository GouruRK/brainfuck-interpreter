#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>

#include "../include/encode.h"
#include "../include/errors.h"
#include "../include/decode.h"
#include "../include/parser.h"
#include "../include/struct.h"

static int manage_input(Args args) {
    int array[ARRAY_SIZE] = {};
    
    if (args.act == ENCODE) {
        return encode(args.input, array);
    } else {
        return decode(args.input, array);
    }
}

int main(int argc, char* argv[]) {
    Args args = init_args();
    Error err = parse(&args, argc, argv);
    if (err != OK) {
        print_error(err);
        return 1;
    }
    if (args.help) {
        print_help();
        return 0;
    }
    
    err = manage_input(args);
    if (err != OK) {
        printf("%d\n", err);
        print_error(err);
        return 1;
    }
    return 0;
}
