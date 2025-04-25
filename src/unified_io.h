#ifndef UNITED_IO_H
#include <stdio.h>
#include "stack.h"


typedef Stack IOBuffer;

void print_io_buffer(IOBuffer *io_buffer);
int io_read(IOBuffer *io_buffer);
void io_write(IOBuffer *io_buffer, int value);

#endif
