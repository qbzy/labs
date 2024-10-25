cmake_minimum_required(VERSION 3.28)
project(task2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(task2
        funcs.c
        funcs.h
        mian.c)

target_link_libraries(task2 m)