#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

#include "errors.h"

typedef enum {
    ENCODE,
    DECODE,
    COMPILE,
    NONE
} Action;

typedef struct {
    bool help;
    Action act;
    char* input;
} Args;

/**
 * @brief Initiate structure for command line arguments with their
 *        default values
 * 
 * @return
 */
Args init_args(void);

/**
 * @brief Parse command line argument with the error management
 * 
 * @param args argument structure to contains their values
 * @param argc number of argument given
 * @param argv arguments given
 * @return
 */
Error parse(Args* args, int argc, char* argv[]);

#endif
