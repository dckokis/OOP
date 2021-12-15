cmake_minimum_required(VERSION 3.21)
project(lab_bloom_filter)

set(CMAKE_CXX_STANDARD 23)

add_executable(lab_bloom_filter main.cpp old.h old.c bloomFilter.hpp)
