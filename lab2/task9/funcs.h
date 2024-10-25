#pragma once


#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-10

enum Errors
{
    OK,
    MEMORY_ERROR,
    INVALID_INPUT
};


long int gcd(long int a, long int b);

int is_finite_representation(double number, int base);

enum Errors check_finite_representation(double **res, int base, int *idx, int count, ...);


