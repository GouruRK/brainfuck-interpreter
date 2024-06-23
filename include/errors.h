#ifndef __INIT_ERRORS__
#define __INIT_ERRORS__

#define RESET  "\x1b[0m"
#define RED    "\x1b[31m"
#define GREEN  "\x1b[32m"
#define PURPLE "\x1b[35m"
#define CYAN   "\x1b[36m"

typedef enum {
    OK,
    ALLOCATION_ERROR,
    ARGUMENT_REQUIRED,
    INVALID_SENTENCE
} Error;

void print_error(Error err);

void print_help(void);

#endif
