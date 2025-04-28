#include "../src/instructions.h"
#include "unity/unity.h"

Stack stack;
IOBuffer buffer;
char *error;

void setUp(void) {
    init(&stack, 2);
    init(&buffer, 2);
}

void tearDown(void) {
    free(stack.arr);
    free(buffer.arr);
}

void test_push(void) {
    Instruction program[] = {
        {OP_PUSH, 1},
        {OP_PUSH, 2},
    };

    op_push(&error, &program[0], &stack, 0);
    op_push(&error, &program[1], &stack, 1);

    TEST_ASSERT_EQUAL(1, stack.arr[0]);
    TEST_ASSERT_EQUAL(2, stack.arr[1]);
}

void test_pop(void) {
    stack.arr[0] = 1;
    stack.arr[1] = 2;
    stack.top = 1;

    op_pop(&error, &stack, 0);

    TEST_ASSERT_EQUAL(1, stack.arr[0]);
}

void test_add(void) {
    stack.arr[0] = 1;
    stack.arr[1] = 2;
    stack.top = 1;

    op_add(&error, &stack, 0);

    TEST_ASSERT_EQUAL(3, stack.arr[0]);
}

void test_sub(void) {
    stack.arr[0] = 2;
    stack.arr[1] = 3;
    stack.top = 1;

    op_sub(&error, &stack, 0);

    TEST_ASSERT_EQUAL(1, stack.arr[0]);
}

void test_write(void) {
    stack.arr[0] = 1;
    stack.top = 0;

    op_write(&error, &stack, &buffer, 0);

    TEST_ASSERT_EQUAL(buffer.arr[0], stack.arr[0]);
}

void test_read(void) {
    buffer.arr[0] = 1;
    buffer.top = 0;

    op_read(&error, &stack, &buffer, 0);

    TEST_ASSERT_EQUAL(1, stack.arr[0]);
}

void test_int(void) {
    stack.arr[0] = 2;
    stack.arr[1] = 0;
    Instruction program[] = {
        {OP_INT, 0},
    };

    Instruction *pc = program;

    op_int(&error, &stack, &pc, 0, 1);

    TEST_ASSERT_EQUAL(0, pc[0].op);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_push);
    RUN_TEST(test_pop);
    RUN_TEST(test_add);
    RUN_TEST(test_sub);
    RUN_TEST(test_write);
    RUN_TEST(test_read);
    return UNITY_END();
}

