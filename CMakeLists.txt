cmake_minimum_required(VERSION 3.21)
project(DateBase_Implementation)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DateBase_Implementation
        Car.cpp
        Car.h
        DateBase.cpp
        Engine.cpp
        Engine.h)
