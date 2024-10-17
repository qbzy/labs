
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum Errors {
    OK,
    INVALID_INPUT,
    RANGE_ERROR,
    NULL_PTR_ERROR,
};


enum Errors str_to_double(const char *str, double *epsilon) {

    if (epsilon == NULL || str == NULL) {
        return NULL_PTR_ERROR;
    }


    char *endptr;
    *epsilon = strtod(str, &endptr);

    if (((*epsilon == HUGE_VAL) || (*epsilon == -HUGE_VAL))) {
        return RANGE_ERROR;
    }

    if (*endptr != '\0') {
        return INVALID_INPUT;
    }


    return OK;
}

enum Errors validation(int argc, char *argv[], double *epsilon) {

    if (argv == NULL){
        return NULL_PTR_ERROR;
    }
    if (argc != 3) {
        return INVALID_INPUT;
    }

    if (str_to_double(argv[1], epsilon) != OK || *epsilon <= 0.0 || *epsilon > 1) {
        return INVALID_INPUT;
    }

    return OK;
}

void func_a(double x, double epsilon, double * result)
{
    int n = 0;
    *result = 0;
    double element = 1;
    while(fabs(element) > epsilon)
    {
        *result += element;
        ++n;
        element *= x/n;
    }
}

void func_b(double x, double epsilon, double* result)
{
    int n = 0;
    *result = 0;
    double element = 1;
    while(fabs(element) > epsilon)
    {
        *result += element;
        n++;
        element *= (-1.0 * x * x) / (2 * n * (2 * n - 1.0));
    }
}

void func_c(double x, double epsilon, double* result)
{
    int n = 0;
    *result = 0;
    double element = 1;
    while(fabs(element) > epsilon)
    {
        *result += element;
        ++n;
        element *= (9.0 * n * n * x * x) / (9.0 * n * n - 9.0 * n + 2.0);
    }
}

void func_d(double x, double epsilon, double* result)
{
    int n = 1;
    *result = 0;
    double element = -1.0 * x * x / 2.0;
    while(fabs(element) > epsilon)
    {
        *result += element;
        ++n;
        element *= (-1.0 * x * x * (2.0 * n - 1)) / (2.0 * n);
    }
}



int main(int argc, char *argv[]) {
    double value;
    switch (validation(argc, argv, &value)) {
        case (INVALID_INPUT):
            printf("ERROR: INVALID INPUT");
            return INVALID_INPUT;

        case (RANGE_ERROR):
            printf("ERROR: RANGE_ERROR");
            return RANGE_ERROR;
        case(NULL_PTR_ERROR):
            printf("NULL_PTR_ERROR");
            return NULL_PTR_ERROR;
        case(OK):
            break;
    }
    double number;
    switch (str_to_double(argv[2], &number)) {
        case (INVALID_INPUT):
            printf("ERROR: INVALID INPUT");
            return INVALID_INPUT;

        case (RANGE_ERROR):
            printf("ERROR: RANGE_ERROR");
            return RANGE_ERROR;
        case(NULL_PTR_ERROR):
            printf("NULL_PTR_ERROR");
            return NULL_PTR_ERROR;
        case(OK):
            double result;

            func_a(number, value, &result);
            printf("a: %.15lf\n", result);

            result = 0;

            func_b(number, value, &result);
            printf("b: %.15lf\n", result);

            if (fabs(number) >= 1){
                printf("c,d: X should be in (-1;1)\n");
            }
            else {
                result = 0;

                func_c(number, value, &result);
                printf("c: %.15lf\n", result);

                result = 0;

                func_d(number, value, &result);
                printf("d: %.15lf\n", result);
            }
            break;
    }


    return 0;
}
