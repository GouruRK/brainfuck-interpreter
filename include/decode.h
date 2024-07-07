#ifndef DECODE_H
#define DECODE_H

#include "errors.h"

typedef enum {
    BEGIN_LOOP = 2,
    SKIP_LOOP,
    REWIND_LOOP,
    CONTINUE,
    STOP
} DecodeEvent;

/**
 * @brief Main function to decode brainfuck code
 * 
 * @param input source of brainfuck code, either a brainfuck string or a file
 *              that contains brainfuck
 * @return 'OK' if everything's fine, else the error code
 */
Error decode(char* input);

#endif
