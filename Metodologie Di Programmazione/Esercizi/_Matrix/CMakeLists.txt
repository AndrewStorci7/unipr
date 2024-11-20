cmake_minimum_required(VERSION 3.29)
project(_Matrix)

set(CMAKE_CXX_STANDARD 20)

add_executable(_Matrix main.cpp
        Matrix/Matrix.h
        Matrix/Matrix.cpp
        Test.cpp)
