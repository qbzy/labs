
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <windows.h>

enum Errors {
    OK,
    INVALID_INPUT,
    INVALID_PATH,
    NULL_PTR_ERROR,
    INVALID_DATA,
    RANGE_ERROR,
};

enum Errors get_full_path(char *path1, char *path2){

    char fullPath1[MAX_PATH], fullPath2[MAX_PATH];

    if (!path1 || !path2){
        return NULL_PTR_ERROR;
    }
    GetFullPathName(path1, MAX_PATH, fullPath1, NULL);
    GetFullPathName(path2, MAX_PATH, fullPath2, NULL);

    if (strcmp(fullPath1, fullPath2) == 0){
        return INVALID_INPUT;
    }
    return OK;
}

enum Errors validation(int argc, char *argv[]) {
    FILE *f;
    FILE *f_out;
    enum Errors status;

    if (argv == NULL) {
        return NULL_PTR_ERROR;
    }

    if (argc != 3) {
        return INVALID_INPUT;
    }
    status = get_full_path(argv[1], argv[2]);
    if (status != OK){
        return status;
    }

    f = fopen(argv[1], "r");
    if (f == NULL) {
        return INVALID_PATH;
    }
    f_out = fopen(argv[2], "r+");
    if (f_out == NULL) {
        fclose(f);
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
    if (str == NULL || max_digit == NULL) {
        return NULL_PTR_ERROR;
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

enum Errors file_input(FILE *f, FILE *f_out) {
    char *delimiters = " \t\n";
    char buf[BUFSIZ];
    char *cur_num;
    char *endptr;
    int base;
    long long int decimal_num;
    while (fgets(buf, sizeof(buf), f)) {
        cur_num = strtok(buf, delimiters);
        while (cur_num != NULL) {
            switch (base_identifier(cur_num, &base)) {
                case (INVALID_INPUT):
                    return INVALID_INPUT;
                case (NULL_PTR_ERROR):
                    return NULL_PTR_ERROR;
                case (INVALID_PATH):

                    return INVALID_PATH;
                case RANGE_ERROR:
                    return RANGE_ERROR;
                case (INVALID_DATA):
                    return INVALID_DATA;
                case (OK):
                    decimal_num = strtoll(cur_num, &endptr, base);

                    if (decimal_num == LLONG_MAX || decimal_num == LLONG_MIN){
                        return RANGE_ERROR;
                    }
                    if (*endptr != '\0') {
                        return INVALID_DATA;
                    }
                    fprintf(f_out, "%lld %d\n", decimal_num, base);
                    cur_num = strtok(NULL, delimiters);
                    base = 1;
                    break;
            }
        }
    }
    return OK;
}

int main(int argc, char *argv[]) {
    FILE *f;
    FILE *f_out;

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
        case RANGE_ERROR:
            printf("ERROR: Range error");
            return RANGE_ERROR;
        case (OK):
            break;
    }
    f = fopen(argv[1], "r");
    f_out = fopen(argv[2], "r+");

    switch (file_input(f, f_out)) {
        case (INVALID_INPUT):
            if(f != NULL) fclose(f);
            if (f_out != NULL) fclose(f_out);
            printf("ERROR: Invalid input");
            return INVALID_INPUT;
        case (NULL_PTR_ERROR):
            if(f != NULL) fclose(f);
            if (f_out != NULL) fclose(f_out);
            printf("ERROR: Null pointer error");
            return NULL_PTR_ERROR;
        case (INVALID_PATH):
            if(f != NULL) fclose(f);
            if (f_out != NULL) fclose(f_out);
            printf("ERROR: Invalid path");
            return INVALID_PATH;
        case (INVALID_DATA):
            if(f != NULL) fclose(f);
            if (f_out != NULL) fclose(f_out);
            printf("ERROR: Invalid data");
            return INVALID_DATA;
        case RANGE_ERROR:
            if(f != NULL) fclose(f);
            if (f_out != NULL) fclose(f_out);
            printf("ERROR: Range error");
            return RANGE_ERROR;
        case (OK):
            printf("Done");
            fclose(f);
            fclose(f_out);
            break;
    }
    if(f != NULL) fclose(f);
    if (f_out != NULL) fclose(f_out);

}