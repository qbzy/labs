#include "funcs.h"

int main(){
    double answer;
    switch (geometric_avg(&answer, 5, 1.3, 123.32421, 91234.01298308124, 1.9, 421341.01234)) {
        case (NULL_PTR_ERROR):
            printf("Error: Null pointer error");
            return NULL_PTR_ERROR;
        case(INVALID_AMOUNT):
            printf("Error: Invalid amount of arguments");
            return INVALID_AMOUNT;
        case(INVALID_DOUBLE):
            printf("Error: Invalid double inputted");
            return INVALID_DOUBLE;
        case(OK):
            printf("ANSWER is %lf", answer);
            break;
        default:
            break;
    }

    double res;
    switch (fast_pow(-3.5, 11, &res)) {
        case(NULL_PTR_ERROR):
            printf("\nError: Null pointer error");
            return NULL_PTR_ERROR;
        case(RANGE_ERROR):
            printf("\nError: Range error");
            return RANGE_ERROR;
        case(OK):
            printf("\n%.10lf", res);
            break;
        default:
            printf("\nError");
            break;
    }
}