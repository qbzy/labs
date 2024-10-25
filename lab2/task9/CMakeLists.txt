cmake_minimum_required(VERSION 3.28)
project(task9 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(task9
        funcs.c
        funcs.h
        main.c)

target_link_libraries(task9 m)