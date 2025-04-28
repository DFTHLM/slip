#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


typedef struct {
    int8_t* arr;
    int top;
} Stack;

void init(Stack *stack, int size);
int8_t is_empty(Stack *stack);
int8_t is_full(Stack *stack);
void push(char **error, Stack *stack, int8_t value);
int8_t pop(char **error, Stack *stack);
int8_t peek(char **error, Stack *stack);

#endif
