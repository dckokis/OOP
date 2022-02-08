cmake_minimum_required(VERSION 3.21)
project(lab_logger)

set(CMAKE_CXX_STANDARD 23)

add_executable(lab_logger main.cpp LoggerStrategy.cpp LoggerStrategy.hpp Logger.cpp Logger.hpp)
