#ifndef ERRORS_H
#define ERRORS_H

#define RESET  "\x1b[0m"
#define RED    "\x1b[31m"
#define GREEN  "\x1b[32m"
#define PURPLE "\x1b[35m"
#define CYAN   "\x1b[36m"

typedef enum {
    ERROR,
    OK
} Error;

/**
 * @brief Print message for an allocation error
 * 
 */
void allocation_error(void);

/**
 * @brief Print message when an command line argument is missing
 * 
 */
void argument_required(void);

/**
 * @brief Print message when the brainfuck message contains a non-brainfuck
 *        character
 * 
 */
void invalid_bf_char(char c);

#endif
