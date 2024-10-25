#include "funcs.h"

enum Errors dichotomy(double (*func)(double), double a, double b, double epsilon, double *root) {

    if (!func || !root) {
        return NULL_PTR_ERROR;
    }

    if (func(a) * func(b) >= 0) {
        return INVALID_INTERVAL;
    }

    if (epsilon <= 0 || epsilon > 1) {
        return INVALID_INPUT;
    }
    if (b < a){
        return INVALID_INTERVAL;
    }
    if (fabs(func(a) - epsilon) < 0){
        *root = a;
        return OK;
    }
    else if(fabs(func(b) - epsilon )< 0){
        *root = b;
        return OK;
    }

    double c;
    *root = (a + b) / 2;
    while (fabs(func(*root)) >= epsilon)
    {
        if(func(*root) * func(a) < 0)
        {
            b = *root;
        }
        else
        {
            a = *root;
        }
        *root = (a + b) / 2;
    }return OK;
}
