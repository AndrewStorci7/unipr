cmake_minimum_required(VERSION 3.26)
project(Vettori)

set(CMAKE_CXX_STANDARD 14)

include_directories(common)
include_directories(vettore)

add_executable(Vettori
        common/function.cpp
        common/functions.h
        vettore/vettore.h
        main.cpp)
