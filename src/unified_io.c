#include "unified_io.h"
//extends io_buffer to make it an IO buffer

void print_io_buffer(char **error, IOBuffer *io_buffer) {
    printf("\33[2K\r");
    if (io_buffer == NULL) {
        *error = strdup("IOBuffer is NULL");
        return;
    }

    for (int i = 0; i <= io_buffer->top; i++) {
        if (io_buffer->arr[i] < 0) {
            *error = strdup("Invalid character in IOBuffer");
            return;
        }
        printf("%c", io_buffer->arr[i]);
    }
}

int io_read(char **error, IOBuffer *io_buffer)
{
    if (io_buffer == NULL) {
        *error = strdup("IOBuffer is NULL");
        return -1;
    }

    if (io_buffer->top == -1) {
        int term_input = getchar();
        return term_input;

    } else {
        int value = pop(error, io_buffer);
        if (*error) {
            return -1;
        }

        print_io_buffer(error, io_buffer);
        if (*error) {
            return -1;
        }

        return value;
    }
    
    return -1;
}

void io_write(char **error, IOBuffer *io_buffer, int value)
{
    if (io_buffer == NULL) {
        *error = strdup("IOBuffer is NULL");
        return;
    }

    push(error, io_buffer, value);
    if (*error) {
        return;
    }

    print_io_buffer(error, io_buffer);
    if (*error) {
        return;
    }


}

