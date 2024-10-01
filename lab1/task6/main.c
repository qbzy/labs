
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
    if (argc != 2) {
        return INVALID_INPUT;
    }

    if (str_to_double(argv[1], epsilon) != OK || *epsilon <= 0.0) {
        return INVALID_INPUT;
    }

    return OK;
}

double integrate(double (*f)(double), double epsilon) {

    double n = 1;
    double a = 0.0, b = 1.0;
    double h, sum, prev_res = 0.0, res = 0.0;


    do {
        prev_res = res;
        h = (b - a) / n;
        sum = (double) (f(a + epsilon) + f(b - epsilon)) / 2.0;



        for (long i = 0; i < n; i++) {
            double x = a + i * h;
            sum += f(x);
        }

        res = h * sum;
        n *= 2;


    } while (fabs(res - prev_res) > epsilon);

    return h * sum;




}

double integral_a(double x) {
    if (x == 0) {
        return 0;
    }
    return (log(1 + x)) / x;
}

double integral_b(double x) {
    double result = exp(-(x * x) / 2);
    return result;
}

double integral_c(double x) {
    if (x == 1) {
        return 0;
    }
    return log(1 / (1 - x));
}

double integral_d(double x) {
    double result = pow(x, x);
    return result;
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


    double int_a = integrate(integral_a, value);
    printf("%.20lf\n", int_a);

    double int_b = integrate(integral_b, value);
    printf("%.20lf\n", int_b);

    double int_c = integrate(integral_c, value);
    printf("%.20lf\n", int_c);

    double int_d = integrate(integral_d, value);
    printf("%.20lf\n", int_d);

    return 0;
}
