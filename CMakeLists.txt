cmake_minimum_required(VERSION 3.31)
project(proj2)

set(CMAKE_CXX_STANDARD 20)

add_executable(proj2 src/main.cpp
        src/DAG.cpp
        src/DAG.h
)
