#include "funcs.h"

double func1(double x){
    return x * x - 4;
}

double func2(double x){
    return x * x;
}

double func3(double x){
    return x + 3;
}

double func4(double x){
    return x * x * x + 1;
}
double func5(double x){
    return x - 1;
}
int main(){
    double root;

    switch(dichotomy(func3, -5,  2, 1e-20, &root)){
        case(NO_CONVERGENCE):
            printf("Error: No convergence");
            return NO_CONVERGENCE;
        case(NULL_PTR_ERROR):
            printf("Error: Null pointer error");
            return NULL_PTR_ERROR;
        case(INVALID_INTERVAL):
            printf("Error: Invalid interval");
            return INVALID_INTERVAL;
        case(OK):
            printf("Root %lf", root);
            return OK;
        default:
            return -1;
    }


}

