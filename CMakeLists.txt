cmake_minimum_required(VERSION 3.15)
project(untitled)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp algo/integral.h algo/integral.cpp algo/matrix_utils.cpp algo/matrix_utils.h algo/utils.h algo/graph.cpp algo/graph.h)