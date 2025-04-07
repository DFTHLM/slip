#ifndef STACK_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef struct {
    int8_t* arr;
    int top;
} Stack;

void init(Stack *stack, int size);
int8_t is_empty(Stack *stack);
int8_t is_full(Stack *stack);
void push(Stack *stack, int8_t value);
int8_t pop(Stack *stack);
int8_t peek(Stack *stack);

#endif
