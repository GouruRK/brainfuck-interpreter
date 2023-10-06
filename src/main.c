#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>

#include "../include/encode.h"
#include "../include/errors.h"
#include "../include/decode.h"
#include "../include/parser.h"
#include "../include/struct.h"

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
    int array[ARRAY_SIZE] = {};
    if (args.act == ENCODE) {
        err = encode(args.sentence, array);
    } else if (args.act == DECODE) {
        err = decode(args.sentence, array);
    }
    if (err != OK) {
        print_error(err);
        return 1;
    }
    return 0;
}
