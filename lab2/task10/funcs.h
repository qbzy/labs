#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>

#define EPS 1e-20

enum Errors {
    OK,
    MEMORY_ERROR,
    INVALID_INPUT,
    NULL_PTR_ERROR,
    RANGE_ERROR,
};

enum Errors refactor(double epsilon, double a, double **res, int power, ...);