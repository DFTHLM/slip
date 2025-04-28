#include "instructions.h"

int op_add(char **error, Stack *stack, Instruction *inst, int line) 
{
    for (int r = 0; r < inst->count ; r++){
        int8_t a, b;

        a = pop(error, stack);
        if (*error) {
            return 1;
        }

        b = pop(error, stack);
        if (*error) {
            return 1;
        }

        push(error, stack, a + b);

        if (*error) {
            return 1;
        }
    }
    return line + 1;
}

int op_sub(char **error, Stack *stack, Instruction *inst, int line)
{
    for (int r = 0; r < inst->count ; r++){
        int8_t a, b;

        a = pop(error, stack);
        if (*error) {
            return -1;
        }

        b = pop(error, stack);
        if (*error) {
            return -1;
        }

        push(error, stack, a - b);
        if (*error) {
            return -1;
        }
    }
    return line + 1;
}

int op_write(char **error, Stack *stack, IOBuffer *buffer, Instruction *inst, int line)
{
    for (int r = 0; r < inst->count ; r++){
        int8_t a = peek(error, stack);

        if (*error) {
            return -1;
        }

        io_write(error, buffer, a);
        if (*error) {
            return -1;
        }
    }
    return line + 1;
}

int op_read(char **error, Stack *stack, IOBuffer *buffer, Instruction *inst, int line)
{
    for (int r = 0; r < inst->count ; r++){
        int8_t a = io_read(error, buffer);
        if (*error) {
            return -1;
        }

        push(error, stack, a);
        if (*error) {
            return -1;
        }
    }
    return line + 1;
}

int op_int(char **error, Stack *stack, Instruction *inst, Instruction **pc, int *program_size, int line)
{
    int invalid = 0;
    for (int r = 0; r < inst->count ; r++){
        int8_t x, y;

        x = pop(error, stack);
        if (*error) {
            return -1;
        }

        if (x > COUNT || x < 0) {
            push(error, stack, x);
            if (*error) {
                return -1;
            }
            invalid = 1;
            continue;
        }

        y = pop(error, stack);
        if (*error) {
            return -1;
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
                *error = strdup("Program size exceeded maximum limit");
                return -1;
            }

            Instruction *new_pc = realloc(*pc, sizeof(Instruction) * new_size);
            if (new_pc == NULL) {
                *error = strdup("Memory allocation failed");
                return -1;
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

    if (invalid) {
        line += 1;
    }

    return line;
}

int op_pop(char **error, Stack *stack, Instruction *inst, int line)
{
    for (int r = 0; r < inst->count ; r++){
        pop(error, stack);
        if (*error) {
            return -1;
        }
    }

    return line + 1;
}

int op_push(char **error, Stack *stack, Instruction *inst, int line)
{
    for (int r = 0; r < inst->count ; r++){
        int8_t a = inst->arg;

        push(error, stack, a);
        if (*error) {
            return -1;
        }
    }
    return line + 1;
}

