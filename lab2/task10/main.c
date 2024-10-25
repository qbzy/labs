#include "funcs.h"

int main() {
    double *result;
    switch (refactor(EPS, 1.0, &result, 3, 5.0, 0.0, 7.0, -2.0)) {
        case (MEMORY_ERROR):
            printf("Error: Memory error\n");
            return MEMORY_ERROR;
        case (RANGE_ERROR):
            printf("Error: Range error\n");
            return RANGE_ERROR;
        case (INVALID_INPUT):
            printf("Error: Invalid input\n");
            return INVALID_INPUT;
        case (NULL_PTR_ERROR):
            printf("Error: Null pointer error\n");
            return NULL_PTR_ERROR;
        case (OK):
            for (int i = 0; i <= 3; i++) {
                printf("g[%d] = %.5f\n", i, result[i]);
            }
            free(result);
            break;
    }
}