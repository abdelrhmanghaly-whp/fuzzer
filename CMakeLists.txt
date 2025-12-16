cmake_minimum_required(VERSION 3.13)
project(fuzzer CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(USE_AFL "Build with AFL++ instrumentation" ON)
if(USE_AFL)
    set(CMAKE_C_COMPILER "afl-clang-fast")
    set(CMAKE_CXX_COMPILER "afl-clang-fast++")
    add_compile_options(-g -O2 -fsanitize=address,undefined)
    add_link_options(-fsanitize=address,undefined)
    message(STATUS "Building with AFL++ instrumentation and sanitizers")
else()
    add_compile_options(-g -O0 -Wall -Wextra)
    message(STATUS "Building without AFL++ (normal debug build)")
endif()

add_library(algorithms STATIC
        src/algorithms/dijkstra.cpp
        src/reference/dijkstra_ref.cpp
        src/harness/input_parser.cpp
        src/harness/afl_harness.cpp
)

target_include_directories(algorithms PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)
add_executable(fuzzer_afl src/harness/afl_harness.cpp)
target_link_libraries(fuzzer_afl algorithms)
if(NOT USE_AFL)
    add_executable(test_manual src/harness/afl_harness.cpp)
    target_link_libraries(test_manual algorithms)
    target_compile_definitions(test_manual PRIVATE NO_AFL_MODE)
endif()