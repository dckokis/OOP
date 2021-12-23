cmake_minimum_required(VERSION 3.21)
project(lab_bloom_filter)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 11)
add_subdirectory(GoogleTest/googletest)
include_directories(GoogleTest/googletest/googletest/include)
add_executable(lab_bloom_filter old.h old.c bloomFilter.hpp Adapter.hpp testForAll.cpp)
target_link_libraries(lab_bloom_filter gtest gtest_main)