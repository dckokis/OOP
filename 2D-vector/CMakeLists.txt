cmake_minimum_required(VERSION 3.17)
project(2D_vector)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(Google_Tests/googletest)
include_directories(Google_Tests/googletest/googletest/include)
add_executable(2D_vector main.cpp Vector.cpp Vector.h)
target_link_libraries(2D_vector gtest gtest_main)