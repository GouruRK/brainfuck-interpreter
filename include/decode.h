#ifndef __INIT_DECODE__
#define __INIT_DECODE__

#include "errors.h"
#include "struct.h"

typedef enum {
    ERROR = -1,
    BEGIN_LOOP,
    SKIP_LOOP,
    REWIND_LOOP,
    CONTINUE,
    STOP
} DecodeEvent;

/**
 * @brief Main function to decode brainfuck code
 * 
 * @param input source to brainfuck code, either a brainfuck code or a file that
 *              contains brainfuck
 * @return 'OK' if everything's fine, else the error code
 */
Error decode(char* input);

#endif
