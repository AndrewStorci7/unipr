cmake_minimum_required(VERSION 3.29)
project(_EvoSpan)

set(CMAKE_CXX_STANDARD 20)

add_executable(_EvoSpan main.cpp
        Classes/Activity/activity.cpp
        Classes/Activity/activity.h
        Classes/Business/Employees/employeers.cpp
        Classes/Business/Supplier/supplier.cpp
        Classes/Business/Customer/customer.cpp)
