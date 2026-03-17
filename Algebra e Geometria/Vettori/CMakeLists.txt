cmake_minimum_required(VERSION 3.26)
project(Vettori)

set(CMAKE_CXX_STANDARD 14)

include_directories(common)
include_directories(vettore)

add_executable(Vettori
        common/function.cpp
        common/function.h
        vettore/vettore.h
        main.cpp
        common/start/start.h
        common/start/start.cpp
        common/console/console.h
        common/console/console.cpp
        matrici/matrice.h
        matrici/matrice.cpp
)
