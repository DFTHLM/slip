#include "slip.h"

Stack stack;
IOBuffer io_buffer;

Instruction program[] = {
    {1, OP_NOP, 0},
    {1, OP_PUSH, -5},
    {1, OP_PUSH, 0},
    {1, OP_PUSH, 65},
    {1, OP_WRITE, 0},
    {1, OP_POP, 0},
    {1, OP_INT, 0}
};

int program_size = sizeof(program) / sizeof(Instruction);
Instruction* pc;

int8_t read_input()
{
    printf("\33[2K\r");
    return 65;
}

int8_t execute_instruction(Instruction *inst, int line) 
{
    switch (inst->op) {
        case OP_NOP:
            for (int r = 0; r < inst->count ; r++){
                if (r == inst->count - 1){ break; };
                continue;
            }
            return line + 1;

        case OP_ADD:
            for (int r = 0; r < inst->count ; r++){
                int8_t a, b;

                if (!is_empty(&stack)) {
                    a = pop(&stack);
                } else {
                    printf("Stack underflow in ADD\n");
                    exit(1);
                }

                if (!is_empty(&stack)) {
                    b = pop(&stack);
                } else {
                    printf("Stack underflow in ADD\n");
                    exit(1);
                }

                push(&stack, a + b);
            }
            return line + 1;

        case OP_SUB:
            for (int r = 0; r < inst->count ; r++){
                int8_t a, b;

                if (!is_empty(&stack)) {
                    a = pop(&stack);
                } else {
                    printf("Stack underflow in SUB\n");
                    exit(1);
                }

                if (!is_empty(&stack)) {
                    b = pop(&stack);
                } else {
                    printf("Stack underflow in SUB\n");
                    exit(1);
                }

                push(&stack, a - b);
            }
            return line + 1;

        case OP_READ:
            for (int r = 0; r < inst->count ; r++){
                int8_t a = io_read(&io_buffer);

                if (a == EOF) {
                    printf("Input error\n");
                    exit(1);
                }

                push(&stack, a);
            }
            return line + 1;

        case OP_WRITE:
            for (int r = 0; r < inst->count ; r++){
                if (is_empty(&stack)) {
                    printf("Stack underflow in WRITE\n");
                    exit(1);
                }

                int8_t a = peek(&stack);

                io_write(&io_buffer, a);
            }
            return line + 1;

        case OP_INT:
            for (int r = 0; r < inst->count ; r++){
                int8_t x, y;

                if (!is_empty(&stack)) {
                    x = pop(&stack);
                } else {
                    printf("Stack underflow in INT\n");
                    exit(1);
                }

                if (x > COUNT) {
                    continue;
                }

                if (!is_empty(&stack)) {
                    y = pop(&stack);
                } else {
                    printf("Stack underflow in INT\n");
                    exit(1);
                }
                
                int target_line = line + y;

                if (target_line >= 0 && target_line < program_size) {
                    line = target_line;
                    pc[target_line].count = 1;
                    pc[target_line].op = x;
                    pc[target_line].arg = 0;
                } else {
                    printf("Invalid jump\n");
                    exit(1);
                }

            }
            break;

        case OP_POP:
            for (int r = 0; r < inst->count ; r++){
                if (is_empty(&stack)) {
                    printf("Stack underflow in DUMP\n");
                    exit(1);
                }

                int8_t a = pop(&stack);
            }
            return line + 1;

        case OP_PUSH:
            for (int r = 0; r < inst->count ; r++){
                int8_t a = inst->arg;

                if (is_full(&stack)) {
                    printf("Stack overflow in PUSH\n");
                    exit(1);
                }

                push(&stack, a);
            }
            return line + 1;
        
        case COUNT:
            return line + 1;

        default:
            printf("Unknown operation\n");
            exit(1);
            return line + 1;
    }

    return line + 1;
}

void parse(char code[]) 
{
    //TODO: Implement parsing logic
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

    return 0;
}

