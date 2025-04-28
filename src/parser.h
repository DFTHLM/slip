#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include "instructions.h"

#define MAX_PROGRAM_SIZE 2048
#define MAX_LINE_LENGTH 256

Instruction *parse(char *filename, int *out_program_size);

#endif // PARSER_H
