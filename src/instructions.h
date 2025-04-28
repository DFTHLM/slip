#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include "unified_io.h"
#include "stack.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef enum {
    OP_NOP,
    OP_ADD,
    OP_SUB,
    OP_READ,
    OP_WRITE,
    OP_INT,
    OP_POP,
    OP_PUSH,
    OP_SWAP,
    COUNT
} OpCode;


typedef struct {
    OpCode op;
    int8_t arg;
} Instruction;

int op_add(char **error, Stack *stack, int line);
int op_sub(char **error, Stack *stack, int line);
int op_read(char **error, Stack *stack, IOBuffer *buffer, int line);
int op_write(char **error, Stack *stack, IOBuffer *buffer, int line);
int op_int(char **error, Stack *stack, Instruction **pc, int *program_size, int line);
int op_pop(char **error, Stack *stack, int line);
int op_push(char **error, Instruction *inst, Stack *stack, int line);
int op_swap(char **error, Stack *stack, int line);

#endif // INSTRUCTIONS_H
