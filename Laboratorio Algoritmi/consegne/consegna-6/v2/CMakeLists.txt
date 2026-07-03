cmake_minimum_required(VERSION 3.26)
project(LAESD_6)

set(CMAKE_CXX_STANDARD 11)

add_executable(LAESD_6
        consegna-6.cpp
        enums/enums.cpp
        sd/nw_tree.cpp
        sd/queue.cpp
)

# 2. DICHIARA LE SOTTOCARTELLE CHE CONTENGONO I FILE .H
target_include_directories(LAESD_6 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/enums
        ${CMAKE_CURRENT_SOURCE_DIR}/sd
)