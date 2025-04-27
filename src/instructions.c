#include "instructions.h"

int op_add(Stack *stack, Instruction *inst, int line) 
{
    for (int r = 0; r < inst->count ; r++){
        int8_t a, b;

        if (!is_empty(stack)) {
            a = pop(stack);
        } else {
            printf("Stack underflow in ADD\n");
            exit(1);
        }

        if (!is_empty(stack)) {
            b = pop(stack);
        } else {
            printf("Stack underflow in ADD\n");
            exit(1);
        }

        push(stack, a + b);
    }
    return line + inst->count;
}

int op_sub(Stack *stack, Instruction *inst, int line)
{
    for (int r = 0; r < inst->count ; r++){
        int8_t a, b;

        if (!is_empty(stack)) {
            a = pop(stack);
        } else {
            printf("Stack underflow in SUB\n");
            exit(1);
        }

        if (!is_empty(stack)) {
            b = pop(stack);
        } else {
            printf("Stack underflow in SUB\n");
            exit(1);
        }

        push(stack, a - b);
    }
    return line + inst->count;
}

int op_write(Stack *stack, IOBuffer *buffer, Instruction *inst, int line)
{
    for (int r = 0; r < inst->count ; r++){
        if (is_empty(stack)) {
            printf("Stack underflow in WRITE\n");
            exit(1);
        }

        int8_t a = peek(stack);

        io_write(buffer, a);
    }
    return line + inst->count;
}

int op_read(Stack *stack, IOBuffer *buffer, Instruction *inst, int line)
{
    for (int r = 0; r < inst->count ; r++){
        int8_t a = io_read(buffer);

        if (a == EOF) {
            printf("Input error\n");
            exit(1);
        }

        push(stack, a);
    }
    return line + inst->count;
}

int op_int(Stack *stack, Instruction *inst, Instruction **pc, int *program_size, int line)
{
            for (int r = 0; r < inst->count ; r++){
                int8_t x, y;

                if (!is_empty(stack)) {
                    x = pop(stack);
                } else {
                    printf("Stack underflow in INT\n");
                    exit(1);
                }

                if (x > COUNT || x < 0) {
                    continue;
                }

                if (!is_empty(stack)) {
                    y = pop(stack);
                } else {
                    printf("Stack underflow in INT\n");
                    exit(1);
                }
                
                int target_line = line + y;

                if (target_line >= 0 && target_line < *program_size) {
                    line = target_line;
                    (*pc)[target_line].count = 1;
                    (*pc)[target_line].op = x;
                    (*pc)[target_line].arg = 0;

                } else {
                    int new_size = *program_size + 2;
                    
                    if (*program_size > INT_MAX - 2) {
                        printf("Program size overflow\n");
                        exit(1);
                    }

                    Instruction *new_pc = realloc(*pc, sizeof(Instruction) * new_size);
                    if (!new_pc) {
                        printf("Memory allocation failed\n");
                        exit(1);
                    }
                    *pc = new_pc;  // update the pointer in main()
                    
                    int old_size = *program_size;
                    *program_size = new_size;  // update size

                    if (target_line < 0) {
                        memmove((*pc) + 2, (*pc), sizeof(Instruction) * *program_size);
                        (*pc)[0].count = 1;
                        (*pc)[0].op = x;
                        (*pc)[0].arg = 0;
                        (*pc)[1].count = abs(target_line) - 1;
                        (*pc)[1].op = OP_NOP;
                        (*pc)[1].arg = 0;
                        line = 0;

                    } else {
                        (*pc)[old_size].count = 1;
                        (*pc)[old_size].op = x;
                        (*pc)[old_size].arg = 0;
                        (*pc)[old_size - 1].count = target_line - old_size - 1;
                        (*pc)[old_size - 1].op = OP_NOP;
                        (*pc)[old_size - 1].arg = 0;
                        line = old_size;
                    }

                    *program_size = new_size;
                }
            }

            return line;
}

int op_pop(Stack *stack, Instruction *inst, int line)
{
    for (int r = 0; r < inst->count ; r++){
        if (is_empty(stack)) {
            printf("Stack underflow in POP\n");
            exit(1);
        }

        pop(stack);
    }

    return line + inst->count;
}

int op_push(Stack *stack, Instruction *inst, int line)
{
    for (int r = 0; r < inst->count ; r++){
        int8_t a = inst->arg;

        if (is_full(stack)) {
            printf("Stack overflow in PUSH\n");
            exit(1);
        }

        push(stack, a);
    }
    return line + 1;
}

