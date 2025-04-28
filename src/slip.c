#include "slip.h"

Stack stack;
IOBuffer io_buffer;

Instruction program[] = {
    {1, OP_PUSH,   0},
    {1, OP_PUSH,   5},
    {1, OP_PUSH,  33},
    {1, OP_PUSH, 100},
    {1, OP_PUSH, 108},
    {1, OP_PUSH, 114},
    {1, OP_PUSH, 111},
    {1, OP_PUSH,  87},
    {1, OP_PUSH,  32},
    {1, OP_PUSH,  44},
    {1, OP_PUSH, 111},
    {1, OP_PUSH, 108},
    {1, OP_PUSH, 108},
    {1, OP_PUSH, 101},
    {1, OP_PUSH,  72},
    {1, OP_INT,    0},
    {1, OP_WRITE,  0},
    {1, OP_POP,    0},
    {1, OP_PUSH,  -5},
    {1, OP_PUSH,   5},
    {1, OP_INT,    0},
    {1, OP_NOP,    0}
};

int program_size = sizeof(program) / sizeof(Instruction);
Instruction* pc;

int8_t execute_instruction(Instruction *inst, int line) 
{
    char *error = NULL;
    int8_t result = 0;

    switch (inst->op) {
        case OP_NOP:
            for (int r = 0; r < inst->count ; r++){
                continue;
            }

            return line + 1;

        case OP_ADD:
            result = op_add(&error, &stack, inst, line);
            if (error) {
                fatal_error(&error, pc, &stack, line, program_size);
                return -1;
            }
            return result;

        case OP_SUB:
            result = op_sub(&error, &stack, inst, line);
            if (error) {
                fatal_error(&error, pc, &stack, line, program_size);
                free(error);
                return -1;
            }
            return result;

        case OP_READ:
            result = op_read(&error, &stack, &io_buffer, inst, line);
            if (error) {
                fatal_error(&error, pc, &stack, line, program_size);
                free(error);
                return -1;
            }
            return result;

        case OP_WRITE:
            result = op_write(&error, &stack, &io_buffer, inst, line);
            if (error) {
                fatal_error(&error, pc, &stack, line, program_size);
                free(error);
                return -1;
            }
            return result;

        case OP_INT:
            result = op_int(&error, &stack, inst, &pc, &program_size, line);
            if (error) {
                fatal_error(&error, pc, &stack, line, program_size);
                free(error);
                return -1;
            }
            return result;

        case OP_POP:
            result = op_pop(&error, &stack, inst, line);
            if (error) {
                fatal_error(&error, pc, &stack, line, program_size);
                free(error);
                return -1;
            }
            return result;

        case OP_PUSH:
            result = op_push(&error, &stack, inst, line);
            if (result < 0) {
                fatal_error(&error, pc, &stack, line, program_size);
                free(error);
                return -1;
            }
            return result;
        
        case COUNT:
            return line;

        default:
            error = strdup("Unknown operation");
            fatal_error(&error, pc, &stack, line, program_size);
            return line + 1;
    }
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

        if (line < 0 || line >= program_size) {
            char *error = "Invalid line number";
            fatal_error(&error, pc, &stack, line, program_size);
        }

        line = execute_instruction(&pc[line], line);

        if (debug) {
            if (!is_empty(&stack)) {
                char *error = NULL;
                int8_t top = peek(&error, &stack);
                if (error) {
                    fatal_error(&error, pc, &stack, line, program_size);
                    free(error);
                    return -1;
                }
                printf("Top of stack: %d\n", top);
            }
        }
    }

    printf("\n\e[?25h");

    return 0;
}

