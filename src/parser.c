#include "parser.h"

int is_valid_integer(const char *str, int *out_value) {
    char *endptr;
    errno = 0;
    long val = strtol(str, &endptr, 10);

    if (errno != 0) {
        return 0;
    }
    if (endptr == str) {
        return 0;
    }

    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            return 0;
        }
        endptr++;
    }

    if (val < -256 || val > 256) {
        return 0;
    }

    *out_value = (int)val;
    return 1;
}

int parse_opcode(const char *str) {
    if (strcmp(str, "NOP") == 0) return OP_NOP;
    if (strcmp(str, "ADD") == 0) return OP_ADD;
    if (strcmp(str, "SUB") == 0) return OP_SUB;
    if (strcmp(str, "READ") == 0) return OP_READ;
    if (strcmp(str, "WRITE") == 0) return OP_WRITE;
    if (strcmp(str, "INT") == 0) return OP_INT;
    if (strcmp(str, "POP") == 0) return OP_POP;
    if (strcmp(str, "PUSH") == 0) return OP_PUSH;
    if (strcmp(str, "SWAP") == 0) return OP_SWAP;

    return -1; // Invalid opcode
}

Instruction *parse(char *filename, int *out_program_size)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    Instruction *program = malloc(MAX_PROGRAM_SIZE * sizeof(Instruction));
    if (program == NULL)
    {
        printf("Error allocating memory for program\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    int program_size = 0;
    int line_number = 0;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        line_number++;
        char *tokens[4];
        int token_count = 0;

        char *token = strtok(line, " \t\n");
        while (token && token_count < 4) {
            tokens[token_count++] = token;
            token = strtok(NULL, " \t\n");
        }
        if (token_count == 0 || tokens[0][0] == ';') {
            continue;
        }

        OpCode op = parse_opcode(tokens[0]);
        if (op == -1) {
            fprintf(stderr, "Invalid operation: %s at line %d\n", tokens[0], line_number);
            free(program);
            fclose(file);
            exit(EXIT_FAILURE);
        }

        int arg = 0;

        if (op == OP_PUSH) {
            if (token_count >= 2) {
                if (!is_valid_integer(tokens[1], &arg)) {
                    fprintf(stderr, "Invalid argument: %s on line: %d\n", tokens[1], line_number);
                    exit(EXIT_FAILURE);
                }
            } else {
                fprintf(stderr, "Missing argument for %s on line: %d\n", tokens[0], line_number);
                exit(EXIT_FAILURE);
            }
        }

        program[program_size].op = op;
        program[program_size].arg = arg;
        program_size++;
    }

    fclose(file);
    *out_program_size = program_size;
    return program;
}
