#include "stack.h"

void init(Stack *stack, int size) {
    stack->arr = (int16_t *)malloc(size * sizeof(int16_t));
    stack->top = -1;
}

int8_t is_empty(Stack *stack) {
    return stack->top == -1;
}

int8_t is_full(Stack *stack) {
    return stack->top == 255;
}

void push(char **error, Stack *stack, int16_t value) {
    if (is_full(stack)) {
        *error = strdup("Stack overflow");
        return;
    }

    if (value < -256 || value > 256) {
        *error = strdup("Value out of range");
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

