#ifndef STACK_H
#define STACK_H

#include <stdint.h>


#define MAX_SIZE 256

typedef struct {
    int8_t arr[MAX_SIZE];
    int top;
} Stack;

void init(Stack *stack);
int8_t is_empty(Stack *stack);
int8_t is_full(Stack *stack);
void push(Stack *stack, int8_t value);
int8_t pop(Stack *stack);
int8_t peek(Stack *stack);

#endif
