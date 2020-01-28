cmake_minimum_required(VERSION 3.15)
project(untitled)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BINARY_DIR "/cmake-build-debug")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_executable(untitled main.cpp algo/algo.h algo/utils.h algo/math/integral.h algo/math/integral.cpp algo/matrix/matrix_utils.cpp algo/matrix/matrix_utils.h algo/graph/graph.cpp algo/graph/graph.h)