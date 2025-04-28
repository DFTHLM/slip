#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H
#include <stdarg.h>
#include <stdio.h>
#include "instructions.h"
#include "stack.h"

static const char* OPCODE_NAMES[] = {
    "NOP",
    "ADD",
    "SUB",
    "READ",
    "WRITE",
    "INT",
    "POP",
    "PUSH"
};

void fatal_error(char **message, Instruction *pc, Stack *stack, int line, int program_size);

#endif // ERROR_HANDLING_H

