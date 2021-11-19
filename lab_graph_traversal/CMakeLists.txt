cmake_minimum_required(VERSION 3.20)
project(lab_graph_traversal)

set(CMAKE_CXX_STANDARD 23)

add_executable(lab_graph_traversal main.cpp Graph.hpp Strategy.hpp Traverse.hpp)
