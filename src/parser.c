#include "../include/parser.h"

#include <getopt.h>
#include <stdlib.h>

#include "../include/errors.h"
#include "../include/struct.h"

Args init_args(void) {
    Args args;
    args.act = NONE;
    args.help = false;
    args.sentence = NULL;
    return args;
}

Error parse_arguments(Args* args, int argc, char* argv[]) {
    opterr = 0;
    int opt, opt_index = 0;
    static struct option long_options[] = {
        {"help", 0, 0, 'h'},
        {"encode", 0, 0, 'e'},
        {"decode", 0, 0, 'd'},
        {0, 0, 0, 0}
    };
    while ((opt = getopt_long(argc, argv, "hed", long_options, &opt_index)) != -1) {
        switch (opt) {
            case 'h':
                args->help = true;
                break;
            case 'e':
                if (args->act == NONE) {
                    args->act = ENCODE;
                }
                break;
            case 'd':
                if (args->act == NONE) {
                    args->act = DECODE;
                }
                break;
            default: 
                break;
        }
    }
    if (optind < argc) {
        if (optind == argc - 1) {
            args->sentence = argv[optind];
        }
    }
    return OK;
}

Error parse(Args* args, int argc, char* argv[]) {
    Error err = parse_arguments(args, argc, argv);
    if (err != OK) {
        return err;
    } 
    if ((!(args->sentence) || (args->act == NONE)) && !(args->help)) {
        return ARGUMENT_REQUIRED;
    }
    return OK;
}
