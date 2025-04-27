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
    COUNT
} OpCode;

typedef struct {
    int count;
    OpCode op;
    int8_t arg;
} Instruction;

int op_add(Stack *stack, Instruction *inst, int line);
int op_sub(Stack *stack, Instruction *inst, int line);
int op_read(Stack *stack, IOBuffer *buffer, Instruction *inst, int line);
int op_write(Stack *stack, IOBuffer *buffer, Instruction *inst, int line);
int op_int(Stack *stack, Instruction *inst, Instruction **pc, int *program_size, int line);
int op_pop(Stack *stack, Instruction *inst, int line);
int op_push(Stack *stack, Instruction *inst, int line);

#endif // INSTRUCTIONS_H
