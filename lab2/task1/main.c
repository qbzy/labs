#include "funcs.h"

int main(int argc, char *argv[]) {
    char *result_string;
    int length = 0;
    switch (flags_validation(argv)) {
        case (NULL_PTR_ERROR):
            printf("NULL POINTER ERROR");
            return NULL_PTR_ERROR;
        case (INVALID_INPUT):
            printf("INVALID INPUT");
            return INVALID_INPUT;
        default:
            break;
    }

    switch (argv[1][1]) {
        case ('l'): {
            if (argc != 3) {
                printf("INVALID INPUT");
                return INVALID_INPUT;
            }

            switch (l_flag(argv[2], &length)) {
                case (NULL_PTR_ERROR):
                    printf("NULL POINTER ERROR");
                    return NULL_PTR_ERROR;
                default:
                    printf("The length of the inputted string (%s) is %d\n", argv[2], length);
                    break;
            }
        }
            break;
        case ('r'): {
            if (argc != 3) {
                printf("INVALID INPUT");
                return INVALID_INPUT;
            }
            switch (r_flag(argv[2], &result_string)) {
                case (NULL_PTR_ERROR):
                    printf("NULL POINTER ERROR");
                    return NULL_PTR_ERROR;
                case (MEMORY_ERROR):
                    printf("MEMORY ERROR");
                    return MEMORY_ERROR;
                default:
                    printf("The inputted string(%s) and the formated(%s)\n", argv[2], result_string);
                    free(result_string);
                    break;
            }
        }
            break;
        case ('u'): {
            if (argc != 3) {
                printf("INVALID INPUT");
                return INVALID_INPUT;
            }
            switch (u_flag(argv[2], &result_string)) {
                case (MEMORY_ERROR):
                    printf("MEMORY ERROR");
                    return MEMORY_ERROR;
                default:
                    printf("The inputted string(%s) and the formated(%s)\n", argv[2], result_string);
                    free(result_string);
            }
        }
            break;
        case ('n'): {
            if (argc != 3) {
                printf("INVALID INPUT");
                return INVALID_INPUT;
            }
            switch (n_flag(argv[2], &result_string)) {
                case (MEMORY_ERROR):
                    printf("MEMORY ERROR");
                    return MEMORY_ERROR;
                default:
                    printf("The inputted string(%s) and the formated(%s)\n", argv[2], result_string);
                    free(result_string);
            }
        }
            break;
        case ('c'):
            if (argc < 5) {
                printf("INVALID INPUT\n");
                return INVALID_INPUT;
            }

            switch (c_flag(argc, argv, &result_string)) {
                case NULL_PTR_ERROR:
                    printf("NULL POINTER ERROR\n");
                    return NULL_PTR_ERROR;
                case MEMORY_ERROR:
                    printf("MEMORY ERROR\n");
                    return MEMORY_ERROR;
                case INVALID_INPUT:
                    printf("INVALID INPUT\n");
                    return INVALID_INPUT;
                default:
                    printf("The concatenated string is: %s\n", result_string);
                    free(result_string);
                    break;
            }
            break;
        default:
            printf("INVALID INPUT: theres no such flag\n");
            return INVALID_INPUT;
    }
}