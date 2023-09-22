#ifndef __INIT_PARSER__
#define __INIT_PARSER__

#include "struct.h"

#include "errors.h"

typedef struct {
    char* sentence;
    Action act;
    bool help;
} Args;

Args init_args(void);

void free_args(Args* args);

Error parse_arguments(Args* args, int argc, char* argv[]);

Error parse(Args* args, int argc, char* argv[]);

#endif
