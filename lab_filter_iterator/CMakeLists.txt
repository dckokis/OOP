cmake_minimum_required(VERSION 3.20)
project(lab_filter_iterator)

set(CMAKE_CXX_STANDARD 23)
add_subdirectory(GoogleTests/googletest)
include_directories(GoogleTests/googletest/googletest/include)
add_executable(lab_filter_iterator FilterIterator.hpp test.cpp)
target_link_libraries(lab_filter_iterator gtest gtest_main)