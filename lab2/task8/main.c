#include "funcs.h"

int main(){
    char result[BUFSIZ];
    int len;
    switch (summation(16, result, 2, "FDDFFDFDFDGGFS", "F8792387492ZBNBDBFDSKJHALFJHLKJHJ")) {
        case(NULL_PTR_ERROR):
            printf("NULL PTR ERROR");
            return NULL_PTR_ERROR;
        case(INVALID_INPUT):
            printf("INVALID INPUT");
            return INVALID_INPUT;
        case(MEMORY_ERROR):
            printf("MEMORY ERROR");
            return MEMORY_ERROR;
        case(OK):
            printf("%s", result);
    }
}
