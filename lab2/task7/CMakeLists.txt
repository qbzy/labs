cmake_minimum_required(VERSION 3.28)
project(task7 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(task7
        funcs.c
        funcs.h
        main.c)
