cmake_minimum_required(VERSION 3.20)
project(lab_trie)

set(CMAKE_CXX_STANDARD 23)

add_executable(lab_trie main.cpp Trie.hpp SubTrie.hpp Iterator.hpp)
