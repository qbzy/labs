#include "funcs.h"

enum Errors geometric_avg(double *res, int count, ...) {
    double temp_res = 1;
    if (!res) {
        return NULL_PTR_ERROR;
    }
    if (count <= 0) {
        return INVALID_AMOUNT;
    }

    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; ++i) {
        double cur = va_arg(args, double);
        if (cur == HUGE_VAL || cur == -HUGE_VAL || cur - EPS < 0) {
            va_end(args);
            return INVALID_DOUBLE;
        }
        temp_res *= cur;

    }
    *res = pow(temp_res, 1.0 / ((double) count));

    va_end(args);
    return OK;
}


enum Errors fast_pow(double num, int exp, double *res) {
    if (!res) {
        return NULL_PTR_ERROR;
    }
    if (exp == 0) {
        *res = 1.0;
        return OK;
    }
    if (exp == 1) {
        *res = num;
        return OK;
    }
    if (exp < 0) {
        double temp_res;
        switch (fast_pow(1.0 / num, abs(exp), &temp_res)) {
            case (NULL_PTR_ERROR):
                return NULL_PTR_ERROR;
            case(RANGE_ERROR):
                return RANGE_ERROR;
            default:
                break;
        }

        *res = temp_res;
    } else if (!(exp & 1)) {
        double temp_res;
        switch (fast_pow(num, exp / 2, &temp_res)) {
            case (NULL_PTR_ERROR):
                return NULL_PTR_ERROR;
            case(RANGE_ERROR):
                return RANGE_ERROR;
            default:
                break;
        }
        *res = temp_res * temp_res;
        if (isinf(*res) || isnan(*res)){
            return RANGE_ERROR;
        }
    } else {
        double temp_res;
        switch (fast_pow(num, exp - 1, &temp_res)) {
            case (NULL_PTR_ERROR):
                return NULL_PTR_ERROR;
            case(RANGE_ERROR):
                return RANGE_ERROR;
            default:
                break;
        }

        *res = temp_res * num;
        if (isinf(*res) || isnan(*res)){
            return RANGE_ERROR;
        }
    }
    return OK;
}