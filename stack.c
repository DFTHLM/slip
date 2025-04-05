#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void init(Stack *stack) {
    stack->top = -1;
}

int8_t is_empty(Stack *stack) {
    return stack->top == (uint8_t)-1;
}

int8_t is_full(Stack *stack) {
    return stack->top == 255;
}

void push(Stack *stack, int8_t value) {
    if (is_full(stack)) {
        printf("Stack overflow\n");
        exit(1);
    }
    stack->arr[++stack->top] = value;
}

int8_t pop(Stack *stack) {
    if (is_empty(stack)) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack->arr[stack->top--];
}

int8_t peek(Stack *stack) {
    if (is_empty(stack)) {
        printf("Stack is empty\n");
        exit(1);
    }
    return stack->arr[stack->top];
}

