cmake_minimum_required(VERSION 3.13)
project(Thread_2 C)

set(CMAKE_C_STANDARD 11)
set( CMAKE_C_FLAGS " -pthread " )
add_executable(Thread_2 main.c)
set( CMAKE_C_FLAGS " -pthread " )