#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "stack.h"

typedef enum {
    OP_NOP,
    OP_ADD,
    OP_SUB,
    OP_READ,
    OP_DUMP,
    OP_WRITE,
    OP_INT,
    OP_PUSH,
    COUNT
} OpCode;

static const char* OPCODE_NAMES[] = {
    "OP_NOP",
    "OP_ADD",
    "OP_SUB",
    "OP_READ",
    "OP_DUMP",
    "OP_WRITE",
    "OP_INT",
    "OP_PUSH"
};

typedef struct {
    int count;
    OpCode op;
    int8_t arg;
} Instruction;

int8_t execute_instruction(Instruction *inst, int line);
void parse(char code[]);
int8_t read_input();
