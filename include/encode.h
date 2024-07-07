#ifndef ENCODE_H
#define ENCODE_H

#include "errors.h"

/**
 * @brief Main function to encode brainfuck code
 * 
 * @param input source to encode, either a file or a string
 * @return 'OK' if everything's fine, else the error code
 */
Error encode(char* input);

#endif
