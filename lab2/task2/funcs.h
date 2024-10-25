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
    INVALID_DOUBLE,
    NULL_PTR_ERROR,
    RANGE_ERROR,
    INVALID_AMOUNT,
};

enum Errors geometric_avg(double *res, int count, ...);

enum Errors fast_pow(double num, int exp, double *res);

