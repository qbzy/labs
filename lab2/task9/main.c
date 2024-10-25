#include "funcs.h"


int main()
{
    double *res = NULL;
    int count = 0;

    switch (check_finite_representation(&res, 3, &count, 3, 0.67932, 0.0080, 0.37)) {
        case(MEMORY_ERROR):
            printf("Error: Memory error\n");
            return MEMORY_ERROR;
        case(INVALID_INPUT):
            printf("Error: Invalid input\n");
            free(res);
            return INVALID_INPUT;
        case(OK):
            if (count == 0)
            {
                printf("Numbers don`t have finite representation\n");
            }
            else
            {
                for (int i = 0; i < count; i++)
                {
                    printf("%lf has finite representation in inputted base\n", res[i]);
                }

            }


            break;
    }


    free(res);
    return 0;
}