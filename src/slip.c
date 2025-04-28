#include "slip.h"

Stack stack;
IOBuffer io_buffer;
Instruction* program;
int program_size;

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
                fatal_error(&error, program, &stack, line, program_size);
                return -1;
            }
            return result;

        case OP_SUB:
            result = op_sub(&error, &stack, inst, line);
            if (error) {
                fatal_error(&error, program, &stack, line, program_size);
                return -1;
            }
            return result;

        case OP_READ:
            result = op_read(&error, &stack, &io_buffer, inst, line);
            if (error) {
                fatal_error(&error, program, &stack, line, program_size);
                return -1;
            }
            return result;

        case OP_WRITE:
            result = op_write(&error, &stack, &io_buffer, inst, line);
            if (error) {
                fatal_error(&error, program, &stack, line, program_size);
                return -1;
            }
            return result;

        case OP_INT:
            result = op_int(&error, &stack, inst, &program, &program_size, line);
            if (error) {
                fatal_error(&error, program, &stack, line, program_size);
                return -1;
            }
            return result;

        case OP_POP:
            result = op_pop(&error, &stack, inst, line);
            if (error) {
                fatal_error(&error, program, &stack, line, program_size);
                return -1;
            }
            return result;

        case OP_PUSH:
            result = op_push(&error, &stack, inst, line);
            if (result < 0) {
                fatal_error(&error, program, &stack, line, program_size);
                return -1;
            }
            return result;
        
        case COUNT:
            return line;

        default:
            error = strdup("Unknown operation");
            fatal_error(&error, program, &stack, line, program_size);
            return line + 1;
    }
}

int main(int argc, char *argv[]) 
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <program.slip>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Hide the cursor
    printf("\e[?25l");

    int debug = 0; //set to 1 to enable debug messages
    init(&stack, 256);
    init(&io_buffer, 1024);

    int line = 0;
    program = parse(argv[1], &program_size);

    while (line < program_size) {
        if (debug) {
            printf("Executing line %d ", line);
            const char *op_name = OPCODE_NAMES[program[line].op];
            printf("program size: %d\n", program_size);
            printf("Operation: %d, Count: %s (%d), Arg: %d\n", program[line].op, op_name, program[line].count, program[line].arg);
        }

        if (line < 0 || line >= program_size) {
            char *error = strdup("Invalid line number");
            fatal_error(&error, program, &stack, line, program_size);
        }

        line = execute_instruction(&program[line], line);

        if (debug) {
            if (!is_empty(&stack)) {
                char *error = NULL;
                int8_t top = peek(&error, &stack);
                if (error) {
                    fatal_error(&error, program, &stack, line, program_size);
                    return -1;
                }
                printf("Top of stack: %d\n", top);
            }
        }
    }

    printf("\n\e[?25h");

    return 0;
}

