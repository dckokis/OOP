cmake_minimum_required(VERSION 3.17)
project(lab_bar_graph)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Google_Tests/googletest)
include_directories(Google_Tests/googletest/googletest/include)
add_executable(lab_bar_graph Histogram.cpp Histogram.hpp histogramExceptions.hpp test.cpp)
target_link_libraries(lab_bar_graph gtest gtest_main)