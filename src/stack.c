#include "stack.h"

void init(Stack *stack, int size) {
    stack->arr = (int8_t *)malloc(size * sizeof(int8_t));
    stack->top = -1;
}

int8_t is_empty(Stack *stack) {
    return stack->top == (uint8_t)-1;
}

int8_t is_full(Stack *stack) {
    return stack->top == 255;
}

void push(char **error, Stack *stack, int8_t value) {
    if (is_full(stack)) {
        *error = strdup("Stack overflow");
        return;
    }

    stack->arr[++stack->top] = value;
}

int8_t pop(char **error, Stack *stack) {
    if (is_empty(stack)) {
        *error = strdup("Stack underflow");
        return -1;
    }

    return stack->arr[stack->top--];
}

int8_t peek(char **error, Stack *stack) {
    if (is_empty(stack)) {
        *error = strdup("Stack underflow");
        return -1;
    }

    return stack->arr[stack->top];
}

