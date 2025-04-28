#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "unified_io.h"
#include "instructions.h"
#include "error_handling.h"

int8_t execute_instruction(Instruction *inst, int line);

