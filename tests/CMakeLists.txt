project(tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(tests
        integral_test.cpp
        matrix_test.cpp
        graph_test.cpp
)

target_link_libraries(tests algo)

target_link_libraries(tests gtest gtest_main)