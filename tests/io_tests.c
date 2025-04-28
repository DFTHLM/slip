#include "../src/unified_io.h"
#include "unity/unity.h"
#include <stdio.h>

#define IO_SIZE 256
IOBuffer buffer;
char *error;

void setUp(void) {
    init(&buffer, IO_SIZE);
}

void tearDown(void) {
    free(buffer.arr);
}

void test_io_write(void) {
    FILE *orig_stdout = stdout;
    FILE *tmpfile = fopen("./tests/test_output.txt", "w+");
    TEST_ASSERT_NOT_NULL(tmpfile);
    stdout = tmpfile;

    io_write(&error, &buffer, 'A');
    io_write(&error, &buffer, 'B');
    io_write(&error, &buffer, 'C');

    fflush(stdout);
    stdout = orig_stdout;

    tmpfile = fopen("./tests/test_output.txt", "r");
    TEST_ASSERT_NOT_NULL(tmpfile);
    char output[256] = {0};
    fgets(output, sizeof(output), tmpfile);
    fclose(tmpfile);
    remove("./tests/test_output.txt");

    TEST_ASSERT_EQUAL_STRING("\x1B[2K\rA\x1B[2K\rAB\x1B[2K\rABC", output);
}

void test_io_read(void) {
    FILE *orig_stdout = stdout;
    FILE *tmpfile = fopen("./tests/test_output.txt", "w+");
    TEST_ASSERT_NOT_NULL(tmpfile);
    stdout = tmpfile;

    io_write(&error, &buffer, 'A');
    io_write(&error, &buffer, 'B');
    io_read(&error, &buffer);

    fflush(stdout);
    stdout = orig_stdout;

    tmpfile = fopen("./tests/test_output.txt", "r");
    TEST_ASSERT_NOT_NULL(tmpfile);
    char output[256] = {0};
    fgets(output, sizeof(output), tmpfile);
    fclose(tmpfile);
    remove("./tests/test_output.txt");

    TEST_ASSERT_EQUAL_STRING("\x1B[2K\rA\x1B[2K\rAB\x1B[2K\rA", output);
}

void test_buffer_overflow(void) {
    remove("stderr.txt");
    remove("./tests/test_output.txt");
    IOBuffer temp_buffer;
    init(&temp_buffer, 10);

    for (int i = 0; i <= 10; i++) {
        io_write(&error, &temp_buffer, 'A');
    }

    freopen("stderr.txt", "w", stderr);
    io_write(&error, &temp_buffer, 'B');
    freopen("/dev/tty", "w", stderr);  // Reset stderr
    free(temp_buffer.arr);
    
    FILE *fp = fopen("stderr.txt", "r");
    char error[256];
    fgets(error, sizeof(error), fp);
    fclose(fp);
    remove("stderr.txt");
    TEST_ASSERT_EQUAL_STRING("\x1B[2K\rA\x1B[2K\rAB\x1B[2K\rA", error);

}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_io_write);
    RUN_TEST(test_io_read);
    RUN_TEST(test_buffer_overflow);

    return UNITY_END();
}

