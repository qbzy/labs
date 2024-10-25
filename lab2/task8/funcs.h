#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

enum Errors{
    OK,
    INVALID_INPUT,
    NULL_PTR_ERROR,
    MEMORY_ERROR,
};

enum Errors summation(int base, char *result, int amount, ...);

enum Errors summationInAnyBase(int base,const char *num1, const char *num2, char **result);