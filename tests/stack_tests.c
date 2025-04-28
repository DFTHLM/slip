#include "unity/unity.h"
#include "../src/stack.h"

#define STACK_SIZE 256

Stack test_stack;
char *error;

void setUp(void) {
    init(&test_stack, STACK_SIZE);
}

void tearDown(void) {
    free(test_stack.arr);
}

void test_stack_initialization(void) {
    TEST_ASSERT_EQUAL(-1, test_stack.top);
    TEST_ASSERT_NOT_NULL(test_stack.arr);
}

void test_push_and_pop_single_value(void) {
    push(&error, &test_stack, 42);
    TEST_ASSERT_EQUAL(42, pop(&error, &test_stack));
}

void test_push_and_pop_multiple_values(void) {
    push(&error,&test_stack, 10);
    push(&error,&test_stack, 20);
    push(&error,&test_stack, 30);
    
    TEST_ASSERT_EQUAL(30, pop(&error, &test_stack));
    TEST_ASSERT_EQUAL(20, pop(&error, &test_stack));
    TEST_ASSERT_EQUAL(10, pop(&error, &test_stack));
}

void test_boundary_values(void) {
    push(&error,&test_stack, INT8_MAX);
    push(&error,&test_stack, INT8_MIN);
    push(&error,&test_stack, 0);
    
    TEST_ASSERT_EQUAL(0, pop(&error, &test_stack));
    TEST_ASSERT_EQUAL(INT8_MIN, pop(&error, &test_stack));
    TEST_ASSERT_EQUAL(INT8_MAX, pop(&error, &test_stack));
}

void test_peek_does_not_remove(void) {
    push(&error,&test_stack, 99);
    TEST_ASSERT_EQUAL(99, peek(&error, &test_stack));
    TEST_ASSERT_EQUAL(0, is_empty(&test_stack));
    TEST_ASSERT_EQUAL(99, pop(&error, &test_stack));
}

void test_pop_empty_stack_error(void) {
    TEST_ASSERT_EQUAL(1, is_empty(&test_stack));
    
    freopen("stderr.txt", "w", stderr);
    pop(&error, &test_stack);  // Should exit
    freopen("/dev/tty", "w", stderr);  // Reset stderr
    
    FILE *fp = fopen("stderr.txt", "r");
    char buffer[256];
    fgets(buffer, sizeof(buffer), fp);
    fclose(fp);
    remove("stderr.txt");
    TEST_ASSERT_EQUAL_STRING("Stack underflow\n", buffer);
}

void test_push_full_stack_error(void) {
    TEST_ASSERT_EQUAL(1, is_empty(&test_stack));
    
    for (int i = 0; i < STACK_SIZE; i++) {
        push(&error,&test_stack, i);
    }

    freopen("stderr.txt", "w", stderr);
    push(&error,&test_stack, 1);
    freopen("/dev/tty", "w", stderr);  // Reset stderr
    
    FILE *fp = fopen("stderr.txt", "r");
    char buffer[256];
    fgets(buffer, sizeof(buffer), fp);
    fclose(fp);
    remove("stderr.txt");
    TEST_ASSERT_EQUAL_STRING("Stack overflow\n", buffer);
}

void test_peek_empty_stack_error(void) {
    TEST_ASSERT_EQUAL(1, is_empty(&test_stack));

    freopen("stderr.txt", "w", stderr);
    peek(&error, &test_stack);  // Should exit
    freopen("/dev/tty", "w", stderr);  // Reset stderr
    
    FILE *fp = fopen("stderr.txt", "r");
    char buffer[256];
    fgets(buffer, sizeof(buffer), fp);
    fclose(fp);
    remove("stderr.txt");
    TEST_ASSERT_EQUAL_STRING("Stack is empty\n", buffer);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_stack_initialization);
    RUN_TEST(test_push_and_pop_single_value);
    RUN_TEST(test_push_and_pop_multiple_values);
    RUN_TEST(test_boundary_values);
    RUN_TEST(test_peek_does_not_remove);
    
    return UNITY_END();
}
