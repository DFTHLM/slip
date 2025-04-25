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
    src/error_handling.c
)

add_executable(slip ${SOURCES})

install(TARGETS slip
    RUNTIME DESTINATION bin
)

