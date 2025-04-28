cmake_minimum_required(VERSION 3.10)
project(slip)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-g)

option(SANITIZE "Enable ASAN/UBSAN" ON)

if(SANITIZE)
    target_compile_options(slip_lib PRIVATE -fsanitize=address,undefined)
    target_link_options(slip_lib PRIVATE -fsanitize=address,undefined)
endif()

option(WARNINGS "Enable all compiler warnings" ON)

if(WARNINGS)
    if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        add_compile_options(-Wall -Wextra -pedantic)
    endif()
endif()

set(SOURCES
    src/stack.c
    src/unified_io.c
    src/instructions.c
    src/error_handling.c
    src/parser.c
)

add_library(slip_lib STATIC ${SOURCES})
target_include_directories(slip_lib PUBLIC src)

add_executable(slip src/slip.c)
target_link_libraries(slip PRIVATE slip_lib)

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

set(INSTRUCTION_TEST_SOURCES
    tests/instruction_tests.c
    tests/unity/unity.c
    src/instructions.c
    src/stack.c
    src/unified_io.c
)

add_executable(instruction_tests ${INSTRUCTION_TEST_SOURCES})

target_include_directories(instruction_tests PRIVATE src tests)

add_test(NAME InstructionTests
    COMMAND instruction_tests
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

