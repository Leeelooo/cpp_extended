project(algo)

set(HEADER_FILES
        graph.hpp
        integral.hpp
        matrix_utils.hpp
)

set(SOURCE_FILES
        graph.cpp
        integral.cpp
        matrix_utils.cpp
)

add_library(algo STATIC ${SOURCE_FILES} ${HEADER_FILES})