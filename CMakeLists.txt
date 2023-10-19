cmake_minimum_required(VERSION 3.26)
project(test1)

set(CMAKE_CXX_STANDARD 17)

add_executable(test1 main.cpp
        lib.cc
        lib.h
        lib_db.h)
