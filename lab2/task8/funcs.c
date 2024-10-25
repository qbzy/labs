#include "funcs.h"

int min(int a, int b){
    if (a < b){
        return a;
    }
    return b;
}

int max(int a, int b){
    if (a > b){
        return a;
    }
    return b;
}
enum Errors summationInAnyBase(int base,const char *num1, const char *num2, char **result){
    int length1, length2;
    int rem = 0;
    int n, i, j = 0, k = 0, n1, flag=0;
    char temp[BUFSIZ];
    if (!num1 || !num2 || !result){
        return NULL_PTR_ERROR;
    }
    *result = (char *) malloc(sizeof(char *) * BUFSIZ);
    if (!(*result)){
        return MEMORY_ERROR;
    }
    length1 = (int) strlen(num1);
    length2 = (int) strlen(num2);

    n = min(length1, length2);

    for (i = 0; i < n; ++i){
        int a, b, cur;

        if (isdigit(num1[length1 - 1 - i])){
            a = num1[length1 - 1 - i] - '0';
        }else if(isalpha(num1[length1 - 1 - i])){
            a = num1[length1 - 1 - i] - 'A' + 10;
        }else{
            free(*result);
            return INVALID_INPUT;
        }
        if (isdigit(num2[length2 - 1 - i])){
            b = num2[length2 - 1 - i] - '0';
        }else if(isalpha(num2[length2 - 1 - i])){
            b = num2[length2 - 1 - i] - 'A' + 10;
        }
        else{
            free(*result);
            return INVALID_INPUT;
        }


        cur = (a + b + rem) % base;
        rem = (a + b + rem) / base;

        if (cur < 10){
            temp[j++] = (char) (cur + '0');
        } else{
            temp[j++] = (char) (cur - 10 + 'A');
        }

    }
    n1 = max(length1, length2);
    if (n1 == length1){
        flag = 1;
    }
    while (n1 - i > 0){
        if (flag == 1){
            if (rem != 0){
                int a;
                if (isdigit(num1[length1 - 1 - i])){
                    a = num1[length1 - 1 - i] - '0';
                }else if(isalpha(num1[length1 - 1 - i])){
                    a = num1[length1 - 1 - i] - 'A' + 10;
                }else{
                    free(*result);
                    return INVALID_INPUT;
                }

                int cur = (a + rem) % base;

                if (cur < 10){
                    temp[j++] = (char) (cur + '0');
                } else{
                    temp[j++] = (char) (cur - 10 + 'A');
                }
                rem = 0;
            }else {
                temp[j++] = num1[n1 - i];
            }
        }else{
            if (rem != 0){
                int a;
                if (isdigit(num2[length2 - 1 - i])){
                    a = num2[length2 - 1 - i] - '0';
                }else if(isalpha(num2[length2 - 1 - i])){
                    a = num2[length2 - 1 - i] - 'A' + 10;
                }else{
                    free(*result);
                    return INVALID_INPUT;
                }

                int cur = (a + rem) % base;

                if (cur < 10){
                    temp[j++] = (char) (cur + '0');
                } else{
                    temp[j++] = (char) (cur - 10 + 'A');
                }
                rem = 0;
            }else{
                temp[j++] = num2[n1 - i];
            }
        }
        i++;
    }
    char temp_res[BUFSIZ];
    for (i = j - 1; i >= 0; i--, k++){
        temp_res[k] = temp[i];
    }
    temp_res[k] = '\0';

    strcpy(*result, temp_res);

    return OK;
}

enum Errors summation(int base, char *result, int amount, ...){
    va_list args;
    int i;
    char temp[BUFSIZ];

    if (!result){
        return NULL_PTR_ERROR;
    }
    va_start(args, amount);
    char *current;
    current = va_arg(args, char *);
    strcpy(temp, current);
    for (i = 1; i < amount; ++i){
        char *num1 = temp;
        char *num2 = va_arg(args, char *);
        switch (summationInAnyBase(base, num1, num2, &current)) {
            case(NULL_PTR_ERROR):
                return NULL_PTR_ERROR;
            case(INVALID_INPUT):
                return INVALID_INPUT;
            default:
                break;
        }
        strcpy(temp, current);
        free(current);
    }
    va_end(args);
    strcpy(result, temp);

    return OK;
}