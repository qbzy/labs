#include "funcs.h"


long int gcd(long int a, long int b)
{
    while (a > 0 && b > 0)
    {
        if (a > b)
        {
            a = a % b;
        }
        else
        {
            b = b % a;
        }
    }
    if (a == 0)
    {
        return b;
    }
    return a;
}


int is_finite_representation(double number, int base)
{
    long int numerator, denominator = 1;

    while (fabs(number - floor(number)) > EPSILON)
    {
        number *= 10;
        denominator *= 10;
    }

    numerator = (long int)number;


    long int gcd_ = gcd(numerator, denominator);
    if(gcd_ != 1)
    {
        denominator /= gcd_;
    }

    long int i = 2;
    if(denominator % i == 0 && base % i != 0)
    {
        return 0;
    }
    while(denominator % i == 0)
        denominator /= i;

    for(i = 3; i * i <= denominator; i+=2)
    {
        if(denominator % i == 0 && base % i != 0)
        {
            return 0;
        }
        while(denominator % i == 0)
            denominator /= i;
    }


    return 1;
}

enum Errors check_finite_representation(double **res, int base, int *idx, int count, ...)
{
    if (base < 2)
    {
        return INVALID_INPUT;
    }

    va_list args;
    va_start(args, count);

    *res = (double *)malloc(sizeof(double) * count);
    if (*res == NULL)
    {
        return MEMORY_ERROR;
    }

    *idx = 0;

    for (int i = 0; i < count; ++i)
    {
        double number = va_arg(args, double);

        if (number > 1 - EPSILON || number < EPSILON)
        {
            printf("fraction %lf is invalid\n", number);
            continue;
        }

        if (is_finite_representation(number, base) == 1)
        {
            (*res)[(*idx)++] = number;
        }
    }

    if (*idx == 0)
    {
        free(*res);
        *res = NULL;
    }

    va_end(args);
    return OK;
}
