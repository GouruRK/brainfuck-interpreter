#ifndef __INIT_PARSER__
#define __INIT_PARSER__

#include "errors.h"
#include "struct.h"

typedef struct {
    char* sentence;
    Action act;
    bool help;
} Args;

Args init_args(void);

Error parse_arguments(Args* args, int argc, char* argv[]);

Error parse(Args* args, int argc, char* argv[]);

#endif
