cmake_minimum_required(VERSION 3.15)
project(cpp_extended)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")
set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        main.cpp
)
set(HEADER_FILES
        utils.hpp
)
add_executable(cpp_extended ${SOURCE_FILES} ${HEADER_FILES})

include_directories(algo)
add_subdirectory(algo)
add_subdirectory(tests)

target_link_libraries(cpp_extended algo)