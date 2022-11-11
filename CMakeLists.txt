cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE CACHE BOOL "" FORCE)

include_directories(include)

project(Bitset VERSION 0.1.0 LANGUAGES C)

set(libBitsetSrc src/bitset.c include/bitset.h)

add_library(bitset SHARED ${libBitsetSrc})

add_executable(bitset_test test/test.c)

target_link_libraries(bitset_test bitset)

enable_testing()

add_test(NAME test1 COMMAND bitset_test)