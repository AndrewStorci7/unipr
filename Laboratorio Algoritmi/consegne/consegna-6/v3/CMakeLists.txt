cmake_minimum_required(VERSION 4.2)
project(v3)

set(CMAKE_CXX_STANDARD 11)

configure_file(
        ${CMAKE_SOURCE_DIR}/test002.cpp
        ${CMAKE_BINARY_DIR}/test002.cpp
        COPYONLY
)

configure_file(
        ${CMAKE_SOURCE_DIR}/test001.cpp
        ${CMAKE_BINARY_DIR}/test001.cpp
        COPYONLY
)

configure_file(
        ${CMAKE_SOURCE_DIR}/source.cpp
        ${CMAKE_BINARY_DIR}/source.cpp
        COPYONLY
)

configure_file(
        ${CMAKE_SOURCE_DIR}/source2.cpp
        ${CMAKE_BINARY_DIR}/source2.cpp
        COPYONLY
)

add_executable(LAESD_6
        functions/parser.cpp
        functions/needleman_wunsch.cpp
        sd/queue.cpp
        sd/nw_tree.cpp
        sd/stack.cpp
        consegna-6.cpp
)
