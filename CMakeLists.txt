cmake_minimum_required(VERSION 3.10)
project(print)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Отключаем предупреждения, которые ломают GTest
add_compile_options(-Wno-unused-variable -Wno-maybe-uninitialized -Wno-error)

option(BUILD_TESTS "Build tests" OFF)

add_library(print STATIC sources/print.cpp)
target_include_directories(print PUBLIC include)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(third-party/gtest)
    add_executable(check tests/test1.cpp)
    target_compile_options(check PRIVATE -Wno-unused-variable)
    target_link_libraries(check print gtest_main)
    add_test(NAME check COMMAND check)
endif()
