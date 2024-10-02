#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

enum Errors {
    OK,
    INVALID_INPUT,
    RANGE_ERROR,
    NULL_PTR_ERROR,
};



enum Errors flags_validation(int argc, char *argv[]) {

    if (argv == NULL) {
        return NULL_PTR_ERROR;
    }

    if (argc != 3) {
        return INVALID_INPUT;
    }

    if (argv[2][0] != '-' && argv[2][0] != '/') {
        return INVALID_INPUT;
    }

    if (argv[2][1] != 'h' && argv[2][1] != 'p'
        && argv[2][1] != 's' && argv[2][1] != 'e'
        && argv[2][1] != 'a' && argv[2][1] != 'f') {
        return INVALID_INPUT;
    }

    return OK;
}

enum Errors str_to_long(const char *str, unsigned long long int *converted_x) {
    if (str == NULL || converted_x == NULL) {
        return NULL_PTR_ERROR;
    }
    char *endptr;

    *converted_x = strtoull(str, &endptr, 10);
    if (str[0] == '-'){
        return INVALID_INPUT;
    }
    if (*converted_x == ULLONG_MAX) {
        return RANGE_ERROR;
    }



    if (*endptr != '\0') {
        return INVALID_INPUT;
    }

    return OK;
}



int *h_func(const unsigned long long int number, int result[], int *count) {


    for (int i = 1, j = 0; i <= 100; i++) {
        if (i % number == 0) {
            result[j] = i;
            j++;
            (*count)++;
        }
    }
    return result;
}

enum Errors h_validation(const char *str_x, unsigned long long int *converted_x) {

    if (str_to_long(str_x, converted_x) != OK) {
        return str_to_long(str_x, converted_x);
    }

    if (*converted_x <= 0) {
        return INVALID_INPUT;
    }

    return OK;
}

int is_prime(unsigned long long int value) {

    for (unsigned long long int i = 2; i <= ((unsigned long long int) sqrtl(value) + 1); i++) {
        if (value % i == 0) {
            return 0;
        }
    }

    return 1;

}
enum Errors s_validation(const char *str) {
    if (str == NULL) {
        return NULL_PTR_ERROR;
    }

    if (!(isdigit(*str) || (*str == 'A') || (*str == 'B') || (*str == 'C') || (*str == 'D') || (*str == 'E')
          || (*str == 'F') || (*str == 'a') || (*str == 'b') || (*str == 'c') || (*str == 'd') || (*str == 'e')
          || (*str == 'f'))) {
        return INVALID_INPUT;
    }
    return OK;
}


enum Errors str_radix16(char *str, char result[], int *flag_n) {
    int flag = 1;
    int i = 0;
    *flag_n = 1;

    if (str == NULL || result == NULL) {
        return NULL_PTR_ERROR;
    }
    if (*str == '-'){
        *flag_n = -1;
        result[i] = '-';
        i++;
        str++;
    }

    for (;*str != '\0'; str++){
        if (*str == '0' && flag){

            continue;
        }
        else{
            flag = 0;
        }
        if (s_validation(str) != OK){
            return s_validation(str);
        }

        else {
            result[i] = *str;
            i++;
        }

        result[i] = '\0';

    }


    return OK;
}
enum Errors e_validation(const char *str, unsigned long long int *converted_x){
    if (str == NULL || converted_x == NULL){
        return NULL_PTR_ERROR;
    }

    if (str_to_long(str, converted_x) != OK){
        return str_to_long(str, converted_x);
    }

    if (*converted_x > 10 || *converted_x < 1){
        return INVALID_INPUT;
    }

    return OK;
}

enum Errors degrees_table(long int degree, unsigned long long int result[]){
    int k = 0;

    if (result == NULL) {
        return NULL_PTR_ERROR;
    }

    for (int i = 1; i < 11; i++){
        for (long int j = 1; j <= degree; j++){
            if (pow(i, j) == HUGE_VALL){
                return RANGE_ERROR;
            }
            result[k] = (unsigned long long int) pow( i, j);
            k++;
        }
    }

    return OK;
}
enum Errors a_validation(const char *str, unsigned long long int *converted_x){
    if (str == NULL || converted_x == NULL){
        return NULL_PTR_ERROR;
    }

    if (str_to_long(str, converted_x) != OK){
        return str_to_long(str, converted_x);
    }

    if (*converted_x <= 1){
        return INVALID_INPUT;
    }

    return OK;
}

enum Errors total_sum( unsigned long long int value, unsigned long long int *sum){
    *sum = 0;

    for (unsigned long long int i = 1; i <= value; i++){
        if (*sum > ULLONG_MAX - i){
            return RANGE_ERROR;
        }
        *sum += i;
    }
    return OK;
}
enum Errors f_validation(const char *str, unsigned long long int *converted_x){
    if (str == NULL || converted_x == NULL){
        return NULL_PTR_ERROR;
    }

    if (str_to_long(str, converted_x) != OK){
        return str_to_long(str, converted_x);
    }

    if (*converted_x < 0){
        return INVALID_INPUT;
    }

    return OK;
}

enum Errors factorial(unsigned long long int *factorial, unsigned long long int number){

    if (factorial == NULL){
        return NULL_PTR_ERROR;
    }

    for (long int i = 2; i <= number; i++){
        if (*factorial  > ULLONG_MAX / i){
            return RANGE_ERROR;
        }
        else{
            *factorial *= i;
        }
    }
    return OK;
}

enum Errors p_validation(const char *argv, unsigned long long int *converted_x) {


    if (str_to_long(argv, converted_x) != OK) {
        return str_to_long(argv, converted_x);
    }

    if (*converted_x <= 1) {
        return INVALID_INPUT;
    }

    return OK;
}


int main(int argc, char *argv[]) {
    unsigned long long int value;

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

    switch (argv[2][1]) {
        case ('h'):
            switch (h_validation(argv[1], &value)) {
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
                    int count = 0;
                    int arr[101];
                    int *result = h_func(value, arr, &count);
                    if (count == 0) {
                        printf("There aren`t any numbers that are completely divisible by x = %llu\n", value);
                    } else {
                        printf("Divisible numbers: ");
                        for (int i = 0; i < count; i++) {

                            printf("%d ", result[i]);

                        }
                    }
                    break;
            }
            break;
        case ('p'):

            switch (p_validation(argv[1], &value)) {
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

                    if (is_prime(value)) {
                        printf("The x = %llu is prime", value);
                        break;
                    } else {
                        printf("The x = %llu is composite", value);
                        break;
                    }

            }
            break;

        case ('s'):
            char result[BUFSIZ];
            int flag_n = 1;
            switch (str_radix16(argv[1], result, &flag_n)) {
                case (INVALID_INPUT):
                    printf("ERROR: Invalid input");
                    return INVALID_INPUT;
                case (NULL_PTR_ERROR):
                    printf("ERROR: Null pointer error");
                    return NULL_PTR_ERROR;
                case (RANGE_ERROR):
                    printf("ERROR: Range error");
                    return RANGE_ERROR;
                case(OK):

                    char *ptr;
                    ptr = result;

                    if (flag_n == -1){
                        printf("-");
                        ptr++;
                    }

                    for(;*ptr != '\0'; ptr++){
                        printf("%c ", *ptr);
                    }
            }
            break;
        case('e'):
            unsigned long long int arr[101];


            switch (e_validation(argv[1], &value)) {
                case (INVALID_INPUT):
                    printf("ERROR: Invalid input");
                    return INVALID_INPUT;
                case (NULL_PTR_ERROR):
                    printf("ERROR: Null pointer error");
                    return NULL_PTR_ERROR;
                case (RANGE_ERROR):
                    printf("ERROR: Range error");
                    return RANGE_ERROR;
                case(OK):
                    switch (degrees_table(value, arr)) {
                        case (INVALID_INPUT):
                            printf("ERROR: Invalid input");
                            return INVALID_INPUT;
                        case (NULL_PTR_ERROR):
                            printf("ERROR: Null pointer error");
                            return NULL_PTR_ERROR;
                        case (RANGE_ERROR):
                            printf("ERROR: Range error");
                            return RANGE_ERROR;
                        case(OK):

                            for (int row = 0; row < 10; row++) {
                                for (int col = 0; col < value; col++) {
                                    printf("%11llu ", arr[row * value + col]);
                                }
                                printf("\n");
                            }

                    }
            }
            break;
        case('a'):
            switch (a_validation(argv[1], &value)) {
                case (INVALID_INPUT):
                    printf("ERROR: Invalid input");
                    return INVALID_INPUT;
                case (NULL_PTR_ERROR):
                    printf("ERROR: Null pointer error");
                    return NULL_PTR_ERROR;
                case (RANGE_ERROR):
                    printf("ERROR: Range error");
                    return RANGE_ERROR;
                case(OK):
                    unsigned long long int sum;
                    switch (total_sum(value, &sum)) {
                        case (INVALID_INPUT):
                            printf("ERROR: Invalid input");
                            return INVALID_INPUT;
                        case (NULL_PTR_ERROR):
                            printf("ERROR: Null pointer error");
                            return NULL_PTR_ERROR;
                        case (RANGE_ERROR):
                            printf("ERROR: Range error");
                            return RANGE_ERROR;
                        case(OK):
                            printf("Sum from 1 to %llu is %llu", value, sum);
                    }
            }
            break;
        case ('f'):
            switch (f_validation(argv[1], &value)){
                case (INVALID_INPUT):
                    printf("ERROR: Invalid input");
                    return INVALID_INPUT;
                case (NULL_PTR_ERROR):
                    printf("ERROR: Null pointer error");
                    return NULL_PTR_ERROR;
                case (RANGE_ERROR):
                    printf("ERROR: Range error");
                    return RANGE_ERROR;
                case(OK):
                    unsigned long long int fact = 1;
                    switch (factorial(&fact, value)) {
                        case (INVALID_INPUT):
                            printf("ERROR: Invalid input");
                            return INVALID_INPUT;
                        case (NULL_PTR_ERROR):
                            printf("ERROR: Null pointer error");
                            return NULL_PTR_ERROR;
                        case (RANGE_ERROR):
                            printf("ERROR: Range error");
                            return RANGE_ERROR;
                        case(OK):
                            printf("Factorial of %llu is %llu", value, fact);
                    }
            }
        break;
    }


}

