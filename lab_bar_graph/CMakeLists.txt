cmake_minimum_required(VERSION 3.17)
project(lab_bar_graph)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab_bar_graph main.cpp BarGraph.cpp BarGraph.hpp Bin.cpp Bin.hpp)