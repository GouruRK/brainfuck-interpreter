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

Error decode(char* sentence, int array[]);

#endif
