#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "unified_io.h"
#include "instructions.h"

static const char* OPCODE_NAMES[] = {
    "OP_NOP",
    "OP_ADD",
    "OP_SUB",
    "OP_READ",
    "OP_WRITE",
    "OP_INT",
    "OP_POP",
    "OP_PUSH"
};

int8_t execute_instruction(Instruction *inst, int line);

