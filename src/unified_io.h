#ifndef UNITED_IO_H
#define UNITED_IO_H
#include <stdio.h>
#include "stack.h"


typedef Stack IOBuffer;

void print_io_buffer(char **error, IOBuffer *io_buffer);
int io_read(char **error, IOBuffer *io_buffer);
void io_write(char **error, IOBuffer *io_buffer, int value);

#endif
