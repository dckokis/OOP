cmake_minimum_required(VERSION 3.20)
project(lab_binary_tree)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(GoogleTest/googletest)
include_directories(GoogleTest/googletest/googletest/include)
add_executable(lab_binary_tree main.cpp btree.hpp)
target_link_libraries(lab_binary_tree gtest gtest_main)