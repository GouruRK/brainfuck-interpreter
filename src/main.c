#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>

#include "encode.h"
#include "errors.h"
#include "decode.h"
#include "parser.h"
#include "struct.h"

static int manage_input(Args args) {
    if (args.act == ENCODE) {
        return encode(args.input);
    }
    return decode(args.input);
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

    return manage_input(args);
}
