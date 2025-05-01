#include "slip.h"

Stack stack;
IOBuffer io_buffer;
Instruction* program;
int program_size;

void enable_virtual_terminal_processing() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

int8_t execute_instruction(Instruction *inst, int line) 
{
    char *error = NULL;
    int8_t result = 0;

    switch (inst->op) {
        case OP_NOP:
            return line + 1;

        case OP_ADD:
            result = op_add(&error, &stack, line);
            if (error || result == -1) {
                fatal_error(&error, program, &stack, line, program_size);
                return -1;
            }
            return result;

        case OP_SUB:
            result = op_sub(&error, &stack, line);
            if (error || result == -1) {
                fatal_error(&error, program, &stack, line, program_size);
                return -1;
            }
            return result;

        case OP_READ:
            result = op_read(&error, &stack, &io_buffer, line);
            if (error || result == -1) {
                fatal_error(&error, program, &stack, line, program_size);
                return -1;
            }
            return result;

        case OP_WRITE:
            result = op_write(&error, &stack, &io_buffer, line);
            if (error || result == -1) {
                fatal_error(&error, program, &stack, line, program_size);
                return -1;
            }
            return result;

        case OP_INT:
            result = op_int(&error, &stack, &program, &program_size, line);
            if (error || result == -1) {
                fatal_error(&error, program, &stack, line, program_size);
                return -1;
            }
            return result;

        case OP_POP:
            result = op_pop(&error, &stack, line);
            if (error || result == -1) {
                fatal_error(&error, program, &stack, line, program_size);
                return -1;
            }
            return result;

        case OP_PUSH:
            result = op_push(&error, inst, &stack, line);
            if (result < 0) {
                fatal_error(&error, program, &stack, line, program_size);
                return -1;
            }
            return result;

        case OP_SWAP:
            result = op_swap(&error, &stack, line);
            if (error || result == -1) {
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
    // Enable ANSI escape codes for Windows
#ifdef _WIN32
    enable_virtual_terminal_processing();
#endif

    int debug = 0;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <program.slip>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc == 3 && (strcmp(argv[2], "--debug") == 0 || strcmp(argv[2], "-d") == 0)) {
        debug = 1;
    }

    // Hide the cursor
    printf("\e[?25l");

    init(&stack, 2048);
    init(&io_buffer, 2048);

    int line = 0;
    program = parse(argv[1], &program_size);

    while (line < program_size) {
        if (debug) {
            printf("Executing line %d ", line);
            const char *op_name = OPCODE_NAMES[program[line].op];
            printf("program size: %d\n", program_size);
            printf("Operation: %d (%s), Arg: %d\n", program[line].op, op_name, program[line].arg);
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

    if (debug) {
        printf("Program finished successfully.\n");
        printf("\n");
        char *error = NULL;
        print_io_buffer(&error, &io_buffer);
    }

    printf("\n\e[?25h");

    return 0;
}

