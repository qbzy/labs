
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum Errors {
    OK,
    INVALID_INPUT,
    INVALID_PATH,
    NULL_PTR_ERROR,
    INVALID_DATA,
};


enum Errors validation(int argc, char *argv[]) {
    FILE *f;
    FILE *f_out;
    if (argv == NULL) {
        return NULL_PTR_ERROR;
    }

    if (argc != 3) {
        return INVALID_INPUT;
    }
    if (strcmp(argv[1], argv[2]) == 0) {
        return INVALID_INPUT;
    }

    f = fopen(argv[1], "r");
    if (f == NULL) {
        return INVALID_PATH;
    }
    f_out = fopen(argv[2], "r+");
    if (f_out == NULL) {
        return INVALID_PATH;
    }


    fclose(f);
    fclose(f_out);

    return OK;
}

enum Errors base_identifier(char *str, int *max_digit) {
    int value;
    char c;
    int size;
    int flag=1;
    if (str == NULL || max_digit == NULL) {
        return NULL_PTR_ERROR;
    }
    if (str[0] == '-'){
        flag = -1;
    }
    *max_digit = 1;
    size = strlen(str);
    for (int i = 0; i < size; i++) {
        if (str[i] == '-'){

            continue;
        }
        else{
            c = toupper(str[i]);

            if (isdigit(c)) {
                value = c - '0';
            } else if (isalpha(c)) {
                value = c - 'A' + 10;
            } else {
                return INVALID_DATA;
            }

            if (value >= *max_digit) {
                *max_digit = value + 1;
            }
        }

    }

    return OK;
}


int main(int argc, char *argv[]) {
    FILE *f;
    FILE *f_out;
    char *delimiters = " \t\n";
    char buf[BUFSIZ];
    char *cur_num;
    char *endptr;
    int base;
    long int decimal_num;
    switch (validation(argc, argv)) {
        case (INVALID_INPUT):
            printf("ERROR: Invalid input");
            return INVALID_INPUT;
        case (NULL_PTR_ERROR):
            printf("ERROR: Null pointer error");
            return NULL_PTR_ERROR;
        case (INVALID_PATH):
            printf("ERROR: Invalid path");
            return INVALID_PATH;
        case (INVALID_DATA):
            printf("ERROR: Invalid data");
            return INVALID_DATA;
        case (OK):
            break;
    }
    f = fopen(argv[1], "r");
    f_out = fopen(argv[2], "r+");

    while (fgets(buf, sizeof(buf), f)) {
        cur_num = strtok(buf, delimiters);
        while (cur_num != NULL) {
            switch (base_identifier(cur_num, &base)) {
                case (INVALID_INPUT):
                    fclose(f);
                    fclose(f_out);
                    printf("ERROR: Invalid input");
                    return INVALID_INPUT;
                case (NULL_PTR_ERROR):
                    fclose(f);
                    fclose(f_out);
                    printf("ERROR: Null pointer error");
                    return NULL_PTR_ERROR;
                case (INVALID_PATH):
                    fclose(f);
                    fclose(f_out);
                    printf("ERROR: Invalid path");
                    return INVALID_PATH;
                case (INVALID_DATA):
                    fclose(f);
                    fclose(f_out);
                    printf("ERROR: Invalid data");
                    return INVALID_DATA;
                case (OK):
                    decimal_num = strtol(cur_num, &endptr, base);
                    if (*endptr != '\0') {
                        fclose(f);
                        fclose(f_out);
                        printf("ERROR: Invalid data");
                        return INVALID_DATA;
                    }
                    fprintf(f_out, "%ld %d\n", decimal_num, base);
                    cur_num = strtok(NULL, delimiters);
                    base = 1;
                    break;
            }

        }


    }
    printf("Done");
    fclose(f);
    fclose(f_out);


}