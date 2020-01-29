cmake_minimum_required(VERSION 3.15)
project(cpp_extended)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")
set(CMAKE_CXX_STANDARD 17)

include_directories(algo)
set(ALGO_SOURCES
#        algo/graph/graph.cpp
        algo/math/integral.cpp
        algo/matrix/matrix_utils.cpp
        algo/algo.hpp
)
add_executable(cpp_extended main.cpp utils.hpp ${ALGO_SOURCES})