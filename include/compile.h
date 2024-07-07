#ifndef COMPILE_H
#define COMPILE_H

#include "errors.h"

/**
 * @brief Transform brainfuck code into C code
 * 
 * @param input source of brainfuck code, either a brainfuck string or a file
 *              that contains brainfuck
 * @return error code
 */
Error compile(char* input);

#endif
