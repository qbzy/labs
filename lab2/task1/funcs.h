#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

enum Errors{
    OK,
    INVALID_INPUT,
    NULL_PTR_ERROR,
    RANGE_ERROR,
    MEMORY_ERROR,

};

enum Errors flags_validation(char *argv[]);

enum Errors str_to_ull(const char *str, unsigned long long int *converted_x);

enum Errors l_flag(char * str, int * length);

enum Errors r_flag(char *str, char **result);

enum Errors u_flag(char *str, char **result);

enum Errors n_flag(char *str, char **result);

enum Errors c_flag(int argc, char *argv[], char **result);


