cmake_minimum_required(VERSION 3.20)
project(lab_graph_traversal)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(GoogleTest/googletest)
include_directories(GoogleTest/googletest/googletest/include)
add_executable(lab_graph_traversal main.cpp Graph.hpp TraverseStrategy.hpp Finder.hpp DFS.hpp BFS.hpp PathFinder.hpp PathTo.hpp)
target_link_libraries(lab_graph_traversal gtest gtest_main)