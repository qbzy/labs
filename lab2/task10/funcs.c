#include "funcs.h"
double calculate(double a, double **coeffs, int power){
    double result = 0;
    double cur_a = 1;
    for (int i = 0; i <= power; i++){

        result += (*coeffs)[i] * cur_a;
        cur_a *= a;

    }
    return result;
}
enum Errors refactor(double epsilon, double a, double **res, int power, ...){
    double * coeffs;
    double cur_coef;
    double factorial;
    int cur_power;
    double temp;
    if (!res){
        return NULL_PTR_ERROR;
    }
    if (epsilon <= 0 || epsilon > 1 || power < 0){
        return INVALID_INPUT;
    }

    va_list args;
    va_start(args, power);
    *res = (double *) malloc(sizeof(double ) * (power + 1));
    if (!(*res)){
        return MEMORY_ERROR;
    }
    coeffs = (double *) malloc(sizeof(double ) * (power + 1));
    if (!coeffs){
        free(*res);
        return MEMORY_ERROR;
    }


    for (int i = 0; i <= power; ++i){
        coeffs[i] = va_arg(args, double);
    }
    va_end(args);

    cur_power = power;
    factorial = 1.0;
    cur_coef = 0;
    for (int i = 0; i <= power; ++i) {

        cur_coef = calculate(a, &coeffs, cur_power);
        if (isinf(cur_coef) || isnan(cur_coef)){
            free(coeffs);
            free(*res);
            return RANGE_ERROR;
        }

        if (i > 1) {
            factorial *= i;
            if (isinf(factorial)){
                free(coeffs);
                free(*res);
                return RANGE_ERROR;
            }
            cur_coef /= factorial;
        }

        (*res)[i] = cur_coef;

        for(int j = 0; j < cur_power; j++){
            temp = coeffs[j+1];
            coeffs[j] = temp * (j+1);
        }
        cur_power--;
    }

    free(coeffs);
    return OK;
}


