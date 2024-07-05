#include "parser.h"

#include <getopt.h>
#include <stdlib.h>

#include "errors.h"
#include "bf.h"

Args init_args(void) {
    Args args;
    args.act = NONE;
    args.help = false;
    args.input = NULL;
    return args;
}

/**
 * @brief Read command lines arguments and fill the argument strucutre with
 *        their correct values
 * 
 * @param args argument structure
 * @param argc number of arguments given
 * @param argv arguments given
 */
static void parse_arguments(Args* args, int argc, char* argv[]) {
    opterr = 0;
    int opt, opt_index = 0;
    static struct option long_options[] = {
        {"help",   no_argument, 0, 'h'},
        {"encode", no_argument, 0, 'e'},
        {"decode", no_argument, 0, 'd'},
        {0,        0,           0, 0}
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
            args->input = argv[optind];
        }
    }
}

Error parse(Args* args, int argc, char* argv[]) {
    parse_arguments(args, argc, argv); 
    if ((!(args->input) || (args->act == NONE)) && !(args->help)) {
        argument_required();
        return ARGUMENT_REQUIRED;
    }
    return OK;
}
