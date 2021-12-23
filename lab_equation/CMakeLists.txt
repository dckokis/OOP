cmake_minimum_required(VERSION 3.21)
project(lab_equation)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(GoogleTest/googletest)
include_directories(GoogleTest/googletest/googletest/include)
add_executable(lab_equation main.cpp Solver.cpp Solver.hpp Secant.cpp Secant.hpp Newton.cpp Newton.hpp Bisection.cpp Bisection.hpp)
target_link_libraries(lab_equation gtest gtest_main)