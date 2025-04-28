#include "instructions.h"

int op_add(char **error, Stack *stack, int line) 
{
    int16_t a, b;

    a = pop(error, stack);
    if (*error) {
        return -1;
    }

    b = pop(error, stack);
    if (*error) {
        return -1;
    }

    push(error, stack, a + b);

    if (*error) {
        return -1;
    }
    return line + 1;
}

int op_sub(char **error, Stack *stack, int line)
{
    int16_t a, b;

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
    return line + 1;
}

int op_write(char **error, Stack *stack, IOBuffer *buffer, int line)
{
    int16_t a = peek(error, stack);

    if (*error) {
        return -1;
    }

    io_write(error, buffer, a);
    if (*error) {
        return -1;
    }
    return line + 1;
}

int op_read(char **error, Stack *stack, IOBuffer *buffer, int line)
{
    int8_t a = io_read(error, buffer);
    if (*error) {
        return -1;
    }

    push(error, stack, a);
    if (*error) {
        return -1;
    }
    return line + 1;
}

int op_int(char **error, Stack *stack, Instruction **pc, int *program_size, int line)
{
    int16_t x, y;

    x = pop(error, stack);
    if (*error) {
        return -1;
    }

    if (x > COUNT || x < 0) {
        push(error, stack, x);
        if (*error) {
            return -1;
        }
        return line + 1;
    }

    y = pop(error, stack);
    if (*error) {
        return -1;
    }
    
    int target_line = line + y;

    if (target_line >= 0 && target_line < *program_size) {
        line = target_line;
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
            (*pc)[0].op = x;
            (*pc)[0].arg = 0;
            (*pc)[1].op = OP_NOP;
            (*pc)[1].arg = 0;
            line = 0;

        } else {
            (*pc)[old_size].op = x;
            (*pc)[old_size].arg = 0;
            (*pc)[old_size - 1].op = OP_NOP;
            (*pc)[old_size - 1].arg = 0;
            line = old_size;
        }

        *program_size = new_size;
    }

    return line;
}

int op_pop(char **error, Stack *stack, int line)
{
    pop(error, stack);
    if (*error) {
        return -1;
    }

    return line + 1;
}

int op_push(char **error, Instruction *inst, Stack *stack, int line)
{
    int16_t a = inst->arg;

    push(error, stack, a);
    if (*error) {
        return -1;
    }

    return line + 1;
}

int op_swap(char **error, Stack *stack, int line)
{
    int16_t a, b;

    a = pop(error, stack);
    if (*error) {
        return -1;
    }

    b = pop(error, stack);
    if (*error) {
        return -1;
    }

    push(error, stack, a);
    if (*error) {
        return -1;
    }

    push(error, stack, b);
    if (*error) {
        return -1;
    }

    return line + 1;
}

