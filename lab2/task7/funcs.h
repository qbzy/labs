#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

enum Errors {
    OK,
    NO_CONVERGENCE,
    INVALID_INTERVAL,
    INVALID_INPUT,
    NULL_PTR_ERROR,
};

enum Errors dichotomy(double (*func)(double), double a, double b, double epsilon, double *root);
