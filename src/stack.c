#include "stack.h"

#include <stdbool.h>
#include <stdlib.h>

#include "errors.h"

#define DEFAULT_LENGTH 5

Error init_stack(Stack *stack) {
    stack->values = (long*)malloc(sizeof(long)*DEFAULT_LENGTH);
    if (!(stack->values)) {
        allocation_error();
        return ERROR;
    }
    stack->curlen = 0;
    stack->maxlen = DEFAULT_LENGTH;
    return OK;
}

Error realloc_stack(Stack *stack) {
    long* temp = stack->values;
    temp = realloc(temp, sizeof(long)*(stack->maxlen + DEFAULT_LENGTH));
    if (!temp) {
        allocation_error();
        return ERROR;
    }
    stack->values = temp;
    stack->maxlen += DEFAULT_LENGTH;
    return OK;
}

void free_stack(Stack *stack) {
    if (stack && stack->values) {
        free(stack->values);
        stack->curlen = 0;
        stack->maxlen = 0;
    }
}
