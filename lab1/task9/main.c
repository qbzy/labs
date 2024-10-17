#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <malloc.h>
#include <time.h>

enum Errors {
    OK,
    INVALID_INPUT,
    RANGE_ERROR,
    NULL_PTR_ERROR,
    INVALID_MEMORY
};

enum Errors str_to_long(const char *str, long int *converted_x) {
    if (str == NULL || converted_x == NULL) {
        return NULL_PTR_ERROR;
    }
    char *endptr;

    *converted_x = strtol(str, &endptr, 10);

    if (*converted_x == LONG_MAX || *converted_x == LONG_MIN) {
        return RANGE_ERROR;
    }

    if (*endptr != '\0'){
        return INVALID_INPUT;
    }


    return OK;
}

enum Errors validation(int argc, char *argv[], long int *a, long int *b) {

    if (argv == NULL) {
        return NULL_PTR_ERROR;
    }
    if (!(argc == 3 || argc == 1)) {
        return INVALID_INPUT;
    }


    enum Errors status = str_to_long(argv[1], a), status1 = str_to_long(argv[2], b);

    if (status1 != OK) {
        return status1;
    }
    if (status != OK) {
        return status;
    }

    if (*a > *b) {
        return INVALID_INPUT;
    }

    return OK;
}

enum Errors array_gen(long int **res, long int a, long int b, long int array_size) {

    if (res == NULL) {
        return NULL_PTR_ERROR;
    }

    (*res) = (long int *) malloc(array_size * sizeof(long int));

    if (*res == NULL) {
        return INVALID_MEMORY;
    }
    long con = rand();
    srand(time(NULL) + con);

    for (int i = 0; i < array_size; ++i) {
        (*res)[i] = rand() % (labs(b - a) + 1) + a;

    }
    return OK;
}

enum Errors swap_min_max(long int **array, long int size) {
    long int max_ind = 0, min_ind = 0;
    long int temp;

    if (*array == NULL) {
        return NULL_PTR_ERROR;
    }

    for (int i = 0; i < size; ++i) {
        if ((*array)[i] > (*array)[max_ind]) {
            max_ind = i;
        }
        if ((*array)[i] < (*array)[min_ind]) {
            min_ind = i;
        }
    }

    temp = (*array)[max_ind];
    (*array)[max_ind] = (*array)[min_ind];
    (*array)[min_ind] = temp;

    return OK;
}

long int find_closest(long int **array, long int size, long int number) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        long int diff = (*array)[mid] - number;
        if (diff == 0) {
            return (*array)[mid];
        }
        if (diff < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    if (labs((*array)[low] - number) > labs((*array)[high] - number)){
        return (*array)[high];
}
    return (*array)[low];
}

int comp (const void * a, const void* b)
{
    return (*((int *)(a)) - *((int*)(b)));
}

enum Errors generate_array_and_find_closest(long int **array_a, long int size_of_array_a,
                                            long int **array_b, long int size_of_array_b,
                                            long int **array_c) {

    if (array_c == NULL || array_a == NULL || array_b == NULL){
        return NULL_PTR_ERROR;
    }

    (*array_c) = (long int *) malloc(sizeof(long int) * size_of_array_a);

    if (*array_c == NULL) {
        return INVALID_MEMORY;
    }

    qsort(*array_b, size_of_array_b, sizeof(long int), comp);


    for (int i = 0; i < size_of_array_a; ++i) {
        (*array_c)[i] = (*array_a)[i] + find_closest(array_b, size_of_array_b, (*array_a)[i]);
    }
    return OK;
}


int main(int argc, char *argv[]) {
    long int a, b;
    long int *res;
    long int size = 25;



    switch (argc) {
        case 3:
            switch (validation(argc, argv, &a, &b)) {
                case (INVALID_INPUT):
                    printf("ERROR: INVALID INPUT");
                    return INVALID_INPUT;
                case (RANGE_ERROR):
                    printf("ERROR: RANGE_ERROR");
                    return RANGE_ERROR;
                case (NULL_PTR_ERROR):
                    printf("ERROR: NULL_PTR_ERROR");
                    return NULL_PTR_ERROR;
                case (INVALID_MEMORY):
                    printf("ERROR: INVALID_MEMORY");
                    return INVALID_MEMORY;
                case (OK):
                    break;
            }

            switch (array_gen(&res, a, b, size)) {
                case (INVALID_INPUT):
                    printf("ERROR: INVALID INPUT");
                    return INVALID_INPUT;
                case (RANGE_ERROR):
                    printf("ERROR: RANGE_ERROR");
                    return RANGE_ERROR;
                case (NULL_PTR_ERROR):
                    printf("ERROR: NULL_PTR_ERROR");
                    return NULL_PTR_ERROR;
                case (INVALID_MEMORY):
                    printf("ERROR: INVALID_MEMORY");
                    free(res);
                    return INVALID_MEMORY;
                case (OK):
                    break;
            }
            printf("Generated array\n");
            for (int i = 0; i < size; ++i) {
                printf("%ld ", res[i]);
            }
            printf("\n");

            switch (swap_min_max(&res, size)) {
                case (INVALID_INPUT):
                    printf("ERROR: INVALID INPUT");
                    return INVALID_INPUT;
                case (RANGE_ERROR):
                    printf("ERROR: RANGE_ERROR");
                    return RANGE_ERROR;
                case (NULL_PTR_ERROR):
                    printf("ERROR: NULL_PTR_ERROR");
                    return NULL_PTR_ERROR;
                case (INVALID_MEMORY):
                    printf("ERROR: INVALID_MEMORY");
                    free(res);
                    return INVALID_MEMORY;
                case (OK):
                    break;
            }

            printf("Max and min swapped\n");
            for (int i = 0; i < size; ++i) {
                printf("%ld ", res[i]);
            }
            printf("\n");

            free(res);
            break;
        case 1:

            long int *a_arr;
            long int *b_arr;
            long int *c_arr;

            srand(time(NULL));

            long int size_a = rand() % (10000 - 10 + 1) + 10;
            long int size_b = rand() % (10000 - 10 + 1) + 10;

            switch (array_gen(&a_arr, -1000, 1000, size_a)) {
                case (INVALID_INPUT):
                    printf("ERROR: INVALID INPUT");
                    return INVALID_INPUT;
                case (RANGE_ERROR):
                    printf("ERROR: RANGE_ERROR");
                    return RANGE_ERROR;
                case (NULL_PTR_ERROR):
                    printf("ERROR: NULL_PTR_ERROR");
                    return NULL_PTR_ERROR;
                case (INVALID_MEMORY):
                    printf("ERROR: INVALID_MEMORY");
                    free(a_arr);
                    return INVALID_MEMORY;
                case (OK):
                    break;
            }

            switch (array_gen(&b_arr, -1000, 1000, size_b)) {
                case (INVALID_INPUT):
                    printf("ERROR: INVALID INPUT");
                    return INVALID_INPUT;
                case (RANGE_ERROR):
                    printf("ERROR: RANGE_ERROR");
                    return RANGE_ERROR;
                case (NULL_PTR_ERROR):
                    printf("ERROR: NULL_PTR_ERROR");
                    return NULL_PTR_ERROR;
                case (INVALID_MEMORY):
                    printf("ERROR: INVALID_MEMORY");
                    free(a_arr);
                    free(b_arr);
                    return INVALID_MEMORY;
                case (OK):
                    break;
            }
            printf("A array\n");
            for (int i = 0; i < size_a;++i){
                printf("%ld ", a_arr[i]);
            }
            printf("\n");

            printf("B array\n");
            for (int i = 0; i < size_b;++i){
                printf("%ld ", b_arr[i]);
            }
            printf("\n");
            switch (generate_array_and_find_closest(&a_arr, size_a, &b_arr, size_b, &c_arr)) {
                case (INVALID_INPUT):
                    printf("ERROR: INVALID INPUT");
                    return INVALID_INPUT;
                case (RANGE_ERROR):
                    printf("ERROR: RANGE_ERROR");
                    return RANGE_ERROR;
                case (NULL_PTR_ERROR):
                    printf("ERROR: NULL_PTR_ERROR");
                    return NULL_PTR_ERROR;
                case (INVALID_MEMORY):
                    printf("ERROR: INVALID_MEMORY");
                    free(a_arr);
                    free(b_arr);
                    free(c_arr);
                    return INVALID_MEMORY;
                case (OK):
                    break;
            }
            printf("C array\n");
            for (int i = 0; i < size_a; ++i){
                printf("%ld ", c_arr[i]);
            }
            printf("\n");

            free(a_arr);
            free(b_arr);
            free(c_arr);
            break;
        default:
            printf("ERROR: INVALID INPUT");
            return INVALID_INPUT;
    }


}

