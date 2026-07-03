#cmake_minimum_required(VERSION 3.26)
#project(LABORATORIO_ALGORITMI)
#
#set(CMAKE_CXX_STANDARD 14)
#
#add_executable(LABORATORIO_ALGORITMI
#        consegne/consegna-2/v2/consegna-2.cpp)
cmake_minimum_required(VERSION 3.26)
project(LAESD_6)

set(CMAKE_CXX_STANDARD 11)

add_executable(LAESD_6
        consegne/consegna-6/v2/consegna-6.cpp
        consegne/consegna-6/v2/enums/enums.cpp
        consegne/consegna-6/v2/sd/nw_tree.cpp
        consegne/consegna-6/v2/sd/queue.cpp
)

## 2. DICHIARA LE SOTTOCARTELLE CHE CONTENGONO I FILE .H
#target_include_directories(LAESD_6 PRIVATE
#        ${CMAKE_CURRENT_SOURCE_DIR}/consegne/consegna-6/v2/enums
#        ${CMAKE_CURRENT_SOURCE_DIR}/consegne/consegna-6/v2/sd
#)