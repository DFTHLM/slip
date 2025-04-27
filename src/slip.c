#include "slip.h"

Stack stack;
IOBuffer io_buffer;

Instruction program[] = {
    {1, OP_PUSH, -7},
    {1, OP_PUSH, 0},
    {1, OP_PUSH, 65},
    {1, OP_WRITE, 0},
    {1, OP_POP, 0},
    {1, OP_INT, 0}
};

int program_size = sizeof(program) / sizeof(Instruction);
Instruction* pc;

int8_t execute_instruction(Instruction *inst, int line) 
{
    switch (inst->op) {
        case OP_NOP:
            for (int r = 0; r < inst->count ; r++){
                continue;
            }
            return line + inst->count;

        case OP_ADD:
            line = op_add(&stack, inst, line);
            return line;

        case OP_SUB:
            line = op_sub(&stack, inst, line);
            return line;

        case OP_READ:
            line = op_read(&stack, &io_buffer, inst, line);
            return line;

        case OP_WRITE:
            line = op_write(&stack, &io_buffer, inst, line);
            return line;

        case OP_INT:
            line = op_int(&stack, inst, &pc, &program_size, line);
            return line;

        case OP_POP:
            line = op_pop(&stack, inst, line);
            return line;

        case OP_PUSH:
            line = op_push(&stack, inst, line);
            return line;
        
        case COUNT:
            return line;

        default:
            printf("Unknown operation\n");
            exit(1);
            return line + 1;
    }

    return line + 1;
}

int main() 
{
    printf("\e[?25l");

    int debug = 0; //set to 1 to enable debug messages
    init(&stack, 256);
    init(&io_buffer, 1024);

    int line = 0;
    pc = (Instruction*)malloc(sizeof(Instruction) * program_size);

    for (int i = 0; i < program_size; i++) {
        pc[i] = program[i];
    }

    while (line < program_size) {
        if (debug) {
            printf("Executing line %d ", line);
            const char *op_name = OPCODE_NAMES[pc[line].op];
            printf("program size: %d\n", program_size);
            printf("Operation: %d, Count: %s (%d), Arg: %d\n", pc[line].op, op_name, pc[line].count, pc[line].arg);
        }
        line = execute_instruction(&pc[line], line);
        if (debug) {
            if (!is_empty(&stack)) {
                int8_t top = peek(&stack);
                printf("Top of stack: %d\n", top);
            }
        }
    }

    free(pc);
    free(stack.arr);
    free(io_buffer.arr);
    printf("\n\e[?25h");

    return 0;
}

