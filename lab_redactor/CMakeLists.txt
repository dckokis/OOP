cmake_minimum_required(VERSION 3.17)
project(lab_redactor)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(GoogleTEST/googletest)
include_directories(GoogleTEST/googletest/googletest/include)
add_executable(lab_redactor  Parser.cpp Parser.hpp FileIO.cpp FileIO.hpp Editor.cpp Editor.hpp Command.cpp Command.hpp Utilities.cpp Utilities.hpp test.cpp)
target_link_libraries(lab_redactor gtest gtest_main)