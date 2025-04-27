cmake_minimum_required(VERSION 3.10)
project(slip)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(WARNINGS "Enable all compiler warnings" ON)

if(WARNINGS)
    if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        add_compile_options(-Wall -Wextra -pedantic)
    endif()
endif()

set(SOURCES
    src/slip.c
    src/stack.c
    src/unified_io.c
    src/instructions.c
)

add_executable(slip ${SOURCES})

#==================================================
#=                  Testing                       =
#==================================================

enable_testing()

set(STACK_TEST_SOURCES
    tests/stack_tests.c
    tests/unity/unity.c
    src/stack.c
)

add_executable(stack_tests ${STACK_TEST_SOURCES})

target_include_directories(stack_tests PRIVATE src tests)

add_test(NAME StackTests
    COMMAND stack_tests
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

set(IO_TEST_SOURCES
    tests/io_tests.c
    tests/unity/unity.c
    src/unified_io.c
    src/stack.c
)

add_executable(io_tests ${IO_TEST_SOURCES})

target_include_directories(io_tests PRIVATE src tests)

add_test(NAME IOTests
    COMMAND io_tests
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

