cmake_minimum_required(VERSION 3.17)
project(2Dvector)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Google_Test/googletest)
include_directories(Google_Test/googletest/googletest/include)
add_executable(2Dvector main.cpp Vector.cpp Vector.hpp)
target_link_libraries(2Dvector gtest gtest_main)