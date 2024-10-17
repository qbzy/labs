
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

enum Errors {
    OK,
    INVALID_INPUT,
    RANGE_ERROR,
    NULL_PTR_ERROR,
};



enum Errors str_to_long(const char *str, long long int *converted_x, int radix) {
    if (str == NULL || converted_x == NULL) {
        return NULL_PTR_ERROR;
    }
    char *endptr;

    *converted_x = strtoll(str, &endptr, radix);

    if (*converted_x == LLONG_MAX || *converted_x == LLONG_MIN) {
        return RANGE_ERROR;
    }




    if (*endptr != '\0') {
        return INVALID_INPUT;
    }

    return OK;
}

enum Errors base_input(int  * base){
    if (base == NULL){
        return NULL_PTR_ERROR;
    }

    if (!scanf("%d", base) || *base < 2 || *base > 36){
        return INVALID_INPUT;
    }

    return OK;
}

enum Errors nums_input(long long int arr[], int base, long long int *maxi, int *cnt){

    int flag = 1;
    int counter = 0;

    if (arr == NULL || maxi == NULL || cnt == NULL){
        return NULL_PTR_ERROR;
    }

    while (flag){

        long long int num;
        char number[BUFSIZ];
        char flagger[] = "Stop";


        scanf("%100s", number);

        if (strcmp(number, flagger) == 0){
            flag = 0;
        }
        else{
            enum Errors status = str_to_long(number, &num, base);
            if(status != OK){
                return status;
            }
            else{
                if (llabs(num) > llabs(*maxi)){
                    *maxi = num;
                }
                counter++;
            }
        }
    }
    *cnt = counter;

    return OK;
}


enum Errors converter(long long int number, int base, char result[], int *index, int *nflag){
    char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    *index = 0;
    *nflag = 1;
    if (result == NULL){
        return NULL_PTR_ERROR;
    }

    if (number == 0){
        result[*index] = '0';
    }

    if (number < 0){
        *nflag = -1;
        number *= *nflag;
    }

    while (number > 0){
        result[(*index)++] = digits[number % base];
        number /= base;
    }

    return OK;

}



int main() {
    int base;
    long long int result[BUFSIZ];
    long long maximum = 0;
    int counter = 0;

    switch(base_input(&base)){
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


    switch (nums_input(result, base, &maximum, &counter)) {
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
            if (counter == 0){
                printf("Numbers were not inputted\n");
            }
            else {
                int index = 0;
                int flag = 1;
                char radix_base[BUFSIZ];
                switch (converter(maximum, base, radix_base, &index, &flag)) {
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
                        printf("The maximum modulo number is ");
                        if (maximum == 0) {
                            printf("0");
                        } else {
                            if (flag == -1) {
                                printf("-");
                            }
                            for (int i = index - 1; i >= 0; i--) {
                                printf("%c", radix_base[i]);
                            }
                        }
                        printf("\n");
                        break;
                }
                index = 0;
                flag = 1;
                switch (converter(maximum, 9, radix_base, &index, &flag)) {
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
                        printf("The number in the number system 9 is ");
                        if (maximum == 0) {
                            printf("0");
                        } else {
                            if (flag == -1) {
                                printf("-");
                            }
                            for (int i = index - 1; i >= 0; i--) {
                                printf("%c", radix_base[i]);
                            }
                        }

                        printf("\n");
                        break;
                }
                index = 0;
                flag = 1;
                switch (converter(maximum, 18, radix_base, &index, &flag)) {
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
                        printf("The number in the number system 18 is ");
                        if (maximum == 0) {
                            printf("0");
                        } else {
                            if (flag == -1) {
                                printf("-");
                            }
                            for (int i = index - 1; i >= 0; i--) {
                                printf("%c", radix_base[i]);
                            }
                        }
                        printf("\n");
                        break;
                }
                index = 0;
                flag = 1;
                switch (converter(maximum, 27, radix_base, &index, &flag)) {
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
                        printf("The number in the number system 27 is ");
                        if (maximum == 0) {
                            printf("0");
                        } else {
                            if (flag == -1) {
                                printf("-");
                            }
                            for (int i = index - 1; i >= 0; i--) {
                                printf("%c", radix_base[i]);
                            }
                        }
                        printf("\n");
                        break;
                }
                index = 0;
                flag = 1;
                switch (converter(maximum, 36, radix_base, &index, &flag)) {
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
                        printf("The number in the number system 36 is ");
                        if (maximum == 0) {
                            printf("0");
                        } else {
                            if (flag == -1) {
                                printf("-");
                            }
                            for (int i = index - 1; i >= 0; i--) {
                                printf("%c", radix_base[i]);
                            }
                        }
                        printf("\n");
                        break;
                }
                break;
            }
    }


}