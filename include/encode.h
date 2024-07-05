#ifndef __INIT_ENCODE__
#define __INIT_ENCODE__

#include "errors.h"

/**
 * @brief Main function to encode brainfuck code
 * 
 * @param input source to brainfuck code, either a brainfuck code or a file that
 *              contains brainfuck
 * @return 'OK' if everything's fine, else the error code
 */
Error encode(char* input);

#endif
