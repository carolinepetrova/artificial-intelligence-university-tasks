cmake_minimum_required(VERSION 3.10)

project(ID3_algorithm)

add_executable(test test.cpp node.cpp entries.cpp utils.cpp id3.cpp)

set_property(TARGET test PROPERTY CXX_STANDARD 17)
