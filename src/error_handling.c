#include "error_handling.h"

void print_program(Instruction *pc, int line, int program_size)
{
    for (int i = 0; i < program_size; i++) {
        if (i == line) {
            fprintf(stderr, "-> ");
        } else {
            fprintf(stderr, "   ");
        }

        if (pc[i].op == OP_PUSH) {
            fprintf(stderr, "%d: %s %d\n", i, OPCODE_NAMES[pc[i].op], pc[i].arg);
        } else {
            fprintf(stderr, "%d: %s\n", i, OPCODE_NAMES[pc[i].op]);
        }
    }
}

void fatal_error(char **message, Instruction *pc, Stack *stack, int line, int program_size) {
    // Print the error message
    fprintf(stderr, "%s on line %d\n", *message, line);
    fprintf(stderr, "Total prgoram size: %d\n", program_size);
    fprintf(stderr, "Total stack size: %d\n", stack->top);
    fprintf(stderr, "\n");

    //print instructions around the error
    print_program(pc, line, program_size);
    fprintf(stderr, "\n");

    // Print the stack contents
    for (int i = 0; i < stack->top; i++) {
        fprintf(stderr, "%d: %d | %c\n", i, stack->arr[i], stack->arr[i]);
    }

    printf("\n\e[?25h");
    exit(EXIT_FAILURE);
    
}

