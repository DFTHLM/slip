#include "unified_io.h"
//extends io_buffer to make it an IO buffer

void print_io_buffer(IOBuffer *io_buffer) {
    printf("\33[2K\r");
    if (io_buffer == NULL) {
        printf("IOBuffer is NULL\n");
        return;
    }

    for (int i = io_buffer->top; i >= 0; i--) {
        printf("%c", io_buffer->arr[i]);
    }
}

int io_read(IOBuffer *io_buffer)
{
    if (io_buffer == NULL) {
        printf("IOBuffer is NULL\n");
        return -1;
    }
    if (io_buffer->top == -1) {

    }

    int value = pop(io_buffer);
    print_io_buffer(io_buffer);
    return value;
}

void io_write(IOBuffer *io_buffer, int value)
{
    if (io_buffer == NULL) {
        printf("IOBuffer is NULL\n");
        exit(1);
    }

    push(io_buffer, value);
    print_io_buffer(io_buffer);
}

