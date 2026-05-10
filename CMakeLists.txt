cmake_minimum_required(VERSION 3.10)
project(print)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Убираем -Werror для совместимости с GTest
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    string(REPLACE "-Werror" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

option(BUILD_TESTS "Build tests" OFF)

add_library(print STATIC sources/print.cpp)
target_include_directories(print PUBLIC include)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(third-party/gtest)
    add_executable(check tests/test1.cpp)
    target_link_libraries(check print gtest_main)
    add_test(NAME check COMMAND check)
endif()
