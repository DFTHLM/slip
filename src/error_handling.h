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
    "POP",
    "PUSH",
    "SWAP",
    "INT",
};

void fatal_error(char **message, Instruction *pc, Stack *stack, int line, int program_size);
void print_program(Instruction *pc, int line, int program_size);

#endif // ERROR_HANDLING_H

