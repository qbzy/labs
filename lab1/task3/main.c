
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

enum Errors {
    OK,
    INVALID_INPUT,
    RANGE_ERROR,
    NULL_PTR_ERROR,
};


enum Errors str_to_double(const char *str, long double *epsilon) {

    if (epsilon == NULL || str == NULL) {
        return NULL_PTR_ERROR;
    }


    char *endptr;
    *epsilon = strtod(str, &endptr);

    if (((*epsilon == HUGE_VALL) || (*epsilon == -HUGE_VALL))) {
        return RANGE_ERROR;
    }

    if (*endptr != '\0') {
        return INVALID_INPUT;
    }


    return OK;
}

enum Errors validation(int argc, char *argv[]) {

    if (argv == NULL) {
        return NULL_PTR_ERROR;
    }
    if (!(argc == 5 || argc == 4 || argc == 6)) {
        return INVALID_INPUT;
    }


    return OK;
}

enum Errors str_to_long(const char *str, long long int *converted_x) {
    if (str == NULL || converted_x == NULL) {
        return NULL_PTR_ERROR;
    }
    char *endptr;

    *converted_x = strtoll(str, &endptr, 10);

    if (*converted_x == LLONG_MAX || *converted_x == LLONG_MIN) {
        return RANGE_ERROR;
    }

    if (*converted_x == 0) {
        return INVALID_INPUT;
    }


    if (*endptr != '\0') {
        return INVALID_INPUT;
    }

    return OK;
}


enum Errors flags_validation(int argc, char *argv[]) {

    if (argv == NULL) {
        return NULL_PTR_ERROR;
    }

    if (!(argc == 4 || argc == 6)) {
        return INVALID_INPUT;
    }

    if (argv[1][0] != '-' && argv[1][0] != '/') {
        return INVALID_INPUT;
    }
    if (strlen(argv[1]) > 2) {
        return INVALID_INPUT;
    }
    if (argv[1][1] != 'q' && argv[1][1] != 'm'
        && argv[1][1] != 't') {
        return INVALID_INPUT;
    }

    return OK;
}

enum Errors divisibles(long long int num1, long long int num2) {
    return  (num1 % num2 != 0);
}

int range_double(long double num1, long double num2) {
    return (num1 <= HUGE_VALL / num2);
}

enum Errors check_triangle(long double side1, long double side2, long double side3, int *result, long double epsilon) {
    if (result == NULL) {
        return NULL_PTR_ERROR;
    }

    if (!range_double(side1, side1) || !range_double(side2, side2) || !range_double(side3, side3))
        return RANGE_ERROR;

    if (side1 <= epsilon || side2 <= epsilon || side3 <= epsilon)
        return INVALID_INPUT;

    if (fabsl(side1 * side1 + side2 * side2 - side3 * side3) <= epsilon ||
        fabsl(side1 * side1 + side3 * side3 - side2 * side2) <= epsilon ||
        fabsl(side2 * side2 + side3 * side3 - side1 * side1) <= epsilon)
        *result = 1;
    else
        *result = 0;

    return OK;

}

enum Errors combinations(long double c1, long double c2, long double c3, long double result[6][3], int *counter, long double epsilon) {
    if (result == NULL || counter == NULL) {
        return NULL_PTR_ERROR;
    }

    long double arr[3] = {c1, c2, c3};


    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                if (i != j && j != k && i != k) {
                    long double ar[3];
                    ar[0] = arr[i];
                    ar[1] = arr[j];
                    ar[2] = arr[k];
                    int flag = 0;
                    int gflag = 0;
                    for (int c = 0; c < *counter; c++) {
                        for (int l = 0; l < 3; l++) {
                            if (result[c][l] - ar[l] <= epsilon){
                                flag++;
                            }
                        }
                        if (flag == 3){
                            gflag = 1;
                        }
                        flag = 0;
                    }
                    if (gflag!=1){
                        for (int cnt = 0; cnt < 3; ++cnt){
                            result[*counter][cnt] = ar[cnt];
                        }
                        (*counter)++;
                    }
                }
            }
        }
    }
    return OK;
}
int main(int argc, char *argv[]) {
    switch (validation(argc, argv)) {
        case (INVALID_INPUT):
            printf("ERROR: Invalid input");
            return INVALID_INPUT;
        case (NULL_PTR_ERROR):
            printf("ERROR: Null pointer error");
            return NULL_PTR_ERROR;
        case (RANGE_ERROR):
            printf("ERROR: Range error");
            return RANGE_ERROR;
        case (OK):
            break;
    }

    switch (flags_validation(argc, argv)) {
        case (INVALID_INPUT):
            printf("ERROR: Invalid input");
            return INVALID_INPUT;
        case (NULL_PTR_ERROR):
            printf("ERROR: Null pointer error");
            return NULL_PTR_ERROR;
        case (RANGE_ERROR):
            printf("ERROR: Range error");
            return RANGE_ERROR;
        case (OK):
            break;
    }

    switch (argv[1][1]) {
        case ('m'):
            if (argc != 4){
                printf("ERROR: Invalid input");
                return INVALID_INPUT;
            }
            long long int num1, num2;
            switch (str_to_long(argv[2], &num1)) {
                case (INVALID_INPUT):
                    printf("ERROR: Invalid input");
                    return INVALID_INPUT;
                case (NULL_PTR_ERROR):
                    printf("ERROR: Null pointer error");
                    return NULL_PTR_ERROR;
                case (RANGE_ERROR):
                    printf("ERROR: Range error");
                    return RANGE_ERROR;
                case (OK):
                    switch (str_to_long(argv[3], &num2)) {
                        case (INVALID_INPUT):
                            printf("ERROR: Invalid input");
                            return INVALID_INPUT;
                        case (NULL_PTR_ERROR):
                            printf("ERROR: Null pointer error");
                            return NULL_PTR_ERROR;
                        case (RANGE_ERROR):
                            printf("ERROR: Range error");
                            return RANGE_ERROR;
                        case (OK):
                            int result = divisibles(num1, num2);
                            if (result == 1) {
                                printf("Number 1 = %lld is not divisible by number 2 = %lld", num1, num2);

                            } else {
                                printf("Number 1 = %lld is divisible by number 2 = %lld", num1, num2);
                            }
                            break;
                    }
                    break;
            }
            break;
        case ('t'):
            if (argc != 6){
                printf("ERROR: Invalid input");
                return INVALID_INPUT;
            }
            long double epsilon, side1, side2, side3;
            int result;
            switch (str_to_double(argv[2], &epsilon)) {
                case (INVALID_INPUT):
                    printf("ERROR: Invalid input");
                    return INVALID_INPUT;
                case (NULL_PTR_ERROR):
                    printf("ERROR: Null pointer error");
                    return NULL_PTR_ERROR;
                case (RANGE_ERROR):
                    printf("ERROR: Range error");
                    return RANGE_ERROR;
                case (OK):
                    if ((epsilon < 0) || (epsilon >= 1)){
                        printf("ERROR: Range error");
                        return RANGE_ERROR;
                    }
                    break;
            }
            switch (str_to_double(argv[3], &side1)) {
                case (INVALID_INPUT):
                    printf("ERROR: Invalid input");
                    return INVALID_INPUT;
                case (NULL_PTR_ERROR):
                    printf("ERROR: Null pointer error");
                    return NULL_PTR_ERROR;
                case (RANGE_ERROR):
                    printf("ERROR: Range error");
                    return RANGE_ERROR;
                case (OK):
                    break;
            }
            switch (str_to_double(argv[4], &side2)) {
                case (INVALID_INPUT):
                    printf("ERROR: Invalid input");
                    return INVALID_INPUT;
                case (NULL_PTR_ERROR):
                    printf("ERROR: Null pointer error");
                    return NULL_PTR_ERROR;
                case (RANGE_ERROR):
                    printf("ERROR: Range error");
                    return RANGE_ERROR;
                case (OK):
                    break;
            }
            switch (str_to_double(argv[5], &side3)) {
                case (INVALID_INPUT):
                    printf("ERROR: Invalid input");
                    return INVALID_INPUT;
                case (NULL_PTR_ERROR):
                    printf("ERROR: Null pointer error");
                    return NULL_PTR_ERROR;
                case (RANGE_ERROR):
                    printf("ERROR: Range error");
                    return RANGE_ERROR;
                case (OK):
                    break;
            }

            switch (check_triangle(side1, side2, side3, &result, epsilon)) {
                case (INVALID_INPUT):
                    printf("ERROR: Invalid input");
                    return INVALID_INPUT;
                case (NULL_PTR_ERROR):
                    printf("ERROR: Null pointer error");
                    return NULL_PTR_ERROR;
                case (RANGE_ERROR):
                    printf("ERROR: Range error");
                    return RANGE_ERROR;
                case (OK):
                    if (result == 1) {
                        printf("This is a right triangle with sides: %Lf, %Lf, %Lf", side1, side2, side3);
                        break;
                    } else {
                        printf("This is not a right triangle with sides: %Lf, %Lf, %Lf", side1, side2, side3);
                        break;
                    }
            }
            break;
        case('q'):
            if (argc != 6){
                printf("ERROR: Invalid input");
                return INVALID_INPUT;
            }
            long double eps, coef1, coef2, coef3;
            switch (str_to_double(argv[2], &eps)) {
                case (INVALID_INPUT):
                    printf("ERROR: Invalid input");
                    return INVALID_INPUT;
                case (NULL_PTR_ERROR):
                    printf("ERROR: Null pointer error");
                    return NULL_PTR_ERROR;
                case (RANGE_ERROR):
                    printf("ERROR: Range error");
                    return RANGE_ERROR;
                case (OK):
                    if ((eps < 0) || (eps >= 1)){
                        printf("ERROR: Range error");
                        return RANGE_ERROR;
                    }
                    break;
            }
            switch (str_to_double(argv[3], &coef1)) {
                case (INVALID_INPUT):
                    printf("ERROR: Invalid input");
                    return INVALID_INPUT;
                case (NULL_PTR_ERROR):
                    printf("ERROR: Null pointer error");
                    return NULL_PTR_ERROR;
                case (RANGE_ERROR):
                    printf("ERROR: Range error");
                    return RANGE_ERROR;
                case (OK):
                    break;
            }
            switch (str_to_double(argv[4], &coef2)) {
                case (INVALID_INPUT):
                    printf("ERROR: Invalid input");
                    return INVALID_INPUT;
                case (NULL_PTR_ERROR):
                    printf("ERROR: Null pointer error");
                    return NULL_PTR_ERROR;
                case (RANGE_ERROR):
                    printf("ERROR: Range error");
                    return RANGE_ERROR;
                case (OK):
                    break;
            }
            switch (str_to_double(argv[5], &coef3)) {
                case (INVALID_INPUT):
                    printf("ERROR: Invalid input");
                    return INVALID_INPUT;
                case (NULL_PTR_ERROR):
                    printf("ERROR: Null pointer error");
                    return NULL_PTR_ERROR;
                case (RANGE_ERROR):
                    printf("ERROR: Range error");
                    return RANGE_ERROR;
                case (OK):
                    break;
            }
            long double res[6][3];
            int counter;
            switch (combinations(coef1, coef2, coef3, res, &counter, eps)) {
                case (INVALID_INPUT):
                    printf("ERROR: Invalid input");
                    return INVALID_INPUT;
                case (NULL_PTR_ERROR):
                    printf("ERROR: Null pointer error");
                    return NULL_PTR_ERROR;
                case (RANGE_ERROR):
                    printf("ERROR: Range error");
                    return RANGE_ERROR;
                case (OK):
                    for (int i = 0; i < counter; ++i){
                        printf("Equation %d: %Lfx^2 %+Lfx %+Lf\n", i + 1, res[i][0], res[i][1], res[i][2]);
                        long double a = res[i][0];
                        long double b = res[i][1];
                        long double c = res[i][2];
                        long double discriminant = b * b - 4.0 * a * c;
                        if (discriminant < 0)
                        {
                            printf("There is no valid roots\n");
                        }
                        else
                        {
                            discriminant = sqrtl(discriminant);
                            b *= -1.0;
                            long double x1 = (b - discriminant) / (2.0 * a);
                            long double x2 = (b + discriminant) / (2.0 * a);
                            printf("x1 = %Lf\n", x1);
                            printf("x2 = %Lf\n", x2);
                        }
                        printf("\n");
                    }


            }
    }
}