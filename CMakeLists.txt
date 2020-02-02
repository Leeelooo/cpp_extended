cmake_minimum_required(VERSION 3.15)
project(cpp_extended)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")
set(CMAKE_CXX_STANDARD 17)

include_directories(./algo)
include_directories(./algo/graph)
include_directories(./algo/math)
include_directories(./algo/matrix)

set(ALGO_SOURCES
#        ./algo/graph/graph.hpp ./algo/graph/graph.cpp
        ./algo/math/integral.hpp ./algo/math/integral.cpp
        ./algo/matrix/matrix_utils.hpp ./algo/matrix/matrix_utils.cpp
        ./algo/algo.hpp
)
add_executable(cpp_extended main.cpp utils.hpp ${ALGO_SOURCES})