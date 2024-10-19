

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


enum Errors {
    OK,
    INVALID_INPUT,
    INVALID_PATH,
    NULL_PTR_ERROR,
    MEMORY_ERROR,
    INVALID_DATA,
};


enum Errors flags_validation(int argc, char *argv[]) {

    if (argv == NULL) {
        return NULL_PTR_ERROR;
    }

    if (!(argc == 5 || argc == 4)) {
        return INVALID_INPUT;
    }

    if (argv[1][0] != '-' && argv[1][0] != '/') {
        return INVALID_INPUT;
    }
    if (argv[1][1] != 'r' && argv[1][1] != 'a') {
        return INVALID_INPUT;
    }

    return OK;
}

enum Errors get_full_path(char *path1, char *path2) {

    char fullPath1[MAX_PATH], fullPath2[MAX_PATH];

    if (!path1 || !path2) {
        return NULL_PTR_ERROR;
    }
    if (GetFullPathName(path1, MAX_PATH, fullPath1, NULL) == 0) {
        return INVALID_PATH;
    }
    if (GetFullPathName(path2, MAX_PATH, fullPath2, NULL) == 0) {
        return INVALID_PATH;
    }

    if (strcmp(fullPath1, fullPath2) == 0) {
        return INVALID_INPUT;
    }

    return OK;
}


enum Errors files_validation(int argc, char *argv[]) {
    if (argc == 5) {
        FILE *f1 = fopen(argv[2], "r");
        FILE *f2 = fopen(argv[3], "r");
        FILE *f_out = fopen(argv[4], "r+");

        enum Errors status1 = get_full_path(argv[2], argv[3]),
                status2 = get_full_path(argv[3], argv[4]),
                status3 = get_full_path(argv[2], argv[4]);

        if (status1 != OK) {
            return status1;
        }
        if (status2 != OK) {
            return status2;
        }
        if (status3 != OK) {
            return status3;
        }
        if (f1 == NULL || f2 == NULL || f_out == NULL) {
            if (f1 != NULL) fclose(f1);
            if (f2 != NULL) fclose(f2);
            if (f_out != NULL) fclose(f_out);
            return INVALID_PATH;
        }

        fclose(f2);
        fclose(f1);
        fclose(f_out);

    } else if (argc == 4) {
        FILE *f1;
        FILE *f_out;

        enum Errors status4 = get_full_path(argv[2], argv[3]);
        if (status4 != OK) {
            return status4;
        }
        f1 = fopen(argv[2], "r");
        f_out = fopen(argv[3], "w");
        if (f1 == NULL || f_out == NULL) {
            if (f1 != NULL) fclose(f1);
            if (f_out != NULL) fclose(f_out);
            return INVALID_PATH;
        }

        fclose(f1);
        fclose(f_out);
    }
    return OK;
}

enum Errors input_into_arr(FILE *f, char *buf[], int *len) {
    char ch;

    if (f == NULL || buf == NULL || len == NULL) {
        return NULL_PTR_ERROR;
    }
    ch = fgetc(f);
    while (ch == ' ' || ch == '\n' || ch == '\t') {
        ch = fgetc(f);
    }
    *len = 0;
    while (ch != ' ' && ch != '\n' && ch != '\t' && ch != EOF) {
        (*buf)[(*len)++] = ch;
        if (*len == BUFSIZ) {
            return INVALID_DATA;
        }
        ch = fgetc(f);
    }
    if (*len >= BUFSIZ) {
        return INVALID_DATA;
    }
    (*buf)[*len] = '\0';
    return OK;
}

enum Errors r_func(FILE *f1, FILE *f2, FILE *f_out) {
    char *buf = (char *) malloc(BUFSIZ * sizeof(char));
    int len = 0;

    if (f1 == NULL || f2 == NULL || f_out == NULL) {
        return INVALID_PATH;
    }

    if (buf == NULL) {
        return MEMORY_ERROR;
    }
    while (!feof(f1) || !feof(f2)) {
        if (!feof(f1)) {
            switch (input_into_arr(f1, &buf, &len)) {
                case (INVALID_INPUT):
                    free(buf);
                    return INVALID_INPUT;
                case (NULL_PTR_ERROR):
                    free(buf);
                    return NULL_PTR_ERROR;
                case (INVALID_PATH):
                    free(buf);
                    return INVALID_PATH;
                case (MEMORY_ERROR):
                    free(buf);
                    return MEMORY_ERROR;
                case (INVALID_DATA):
                    free(buf);
                    return INVALID_DATA;
                case (OK):
                    break;
            }
            if (len > 0) {
                fprintf(f_out, "%s ", buf);
            }
        }

        if (!feof(f2)) {
            switch (input_into_arr(f2, &buf, &len)) {
                case (INVALID_INPUT):
                    free(buf);
                    return INVALID_INPUT;
                case (NULL_PTR_ERROR):
                    free(buf);
                    return NULL_PTR_ERROR;
                case (INVALID_PATH):
                    free(buf);
                    return INVALID_PATH;
                case (MEMORY_ERROR):
                    free(buf);
                    return MEMORY_ERROR;
                case (INVALID_DATA):
                    free(buf);
                    return INVALID_DATA;
                case (OK):
                    break;
            }
            if (len > 0) {
                fprintf(f_out, "%s ", buf);
            }
        }
    }
    free(buf);
    return OK;
}

void base_converter(char **arr, int **result, int len, int base) {

    int num = 0;
    for(int i = 0; i < len; ++i)
    {
        if(isalpha((*arr)[i]))
        {
            (*arr)[i] = (char)tolower((*arr)[i]);
        }
        int temp_num = (int)(*arr)[i];
        int base10 = 1;
        while(temp_num > 0)
        {
            num += (temp_num % base) * base10;
            base10 *= 10;
            temp_num /= base;
        }

        (*result)[i] = num;
        num = 0;
    }
}






enum Errors a_func(FILE *f1, FILE *f_out) {
    int i = 0;
    int len = 0;

    char *buf;
    int * res;
    buf = (char *)malloc(BUFSIZ * sizeof(char));
    if (buf == NULL) {
        return MEMORY_ERROR;
    }
    res = (int *)malloc(100 * sizeof(int));
    if (!res) {
        free(buf);
        return MEMORY_ERROR;
    }

    if (f1 == NULL || f_out == NULL) {
        free(res);
        free(buf);
        return NULL_PTR_ERROR;
    }
    while (!feof(f1)) {

        switch (input_into_arr(f1, &buf, &len)) {
            case (NULL_PTR_ERROR):
                free(buf);
                free(res);
                return NULL_PTR_ERROR;
            case (INVALID_DATA):
                free(buf);
                free(res);
                return INVALID_DATA;
            case (OK):
                i++;
                break;
            default:
                break;
        }
        if (len > 0 && i % 10 == 0) {
            base_converter(&buf, &res, len, 4);


            for (int k = 0; k < len; k++) {
                fprintf(f_out, "%d", res[k]);
            }
            fprintf(f_out, " ");
        }

        else if (len > 0 && i % 2 == 0) {
            for (int k = 0; k < len; k++) {
                fprintf(f_out, "%c", tolower(buf[k]));
            }
            fprintf(f_out, " ");

        } else if (len > 0 && i % 5 == 0) {

            base_converter(&buf, &res, len, 8);
            for (int k = 0; k < len; k++) {
                fprintf(f_out, "%d", res[k]);
            }
            fprintf(f_out, " ");

        }


    }
    free(res);
    free(buf);
    return OK;
}

int main(int argc, char *argv[]) {
    FILE *f1;
    FILE *f2;
    FILE *f_out;

    switch (flags_validation(argc, argv)) {
        case (INVALID_INPUT):
            printf("ERROR: Invalid input");
            return INVALID_INPUT;
        case (NULL_PTR_ERROR):
            printf("ERROR: Null pointer error");
            return NULL_PTR_ERROR;
        case (INVALID_PATH):
            printf("ERROR: Invalid path");
            return INVALID_PATH;
        case (MEMORY_ERROR):
            printf("ERROR: Memory error");
        case (INVALID_DATA):
            printf("ERROR: Invalid data");
            return INVALID_DATA;
        case (OK):
            break;
    }
    switch (files_validation(argc, argv)) {
        case (INVALID_INPUT):
            printf("ERROR: Invalid input");
            return INVALID_INPUT;
        case (NULL_PTR_ERROR):
            printf("ERROR: Null pointer error");
            return NULL_PTR_ERROR;
        case (INVALID_PATH):
            printf("ERROR: Invalid path");
            return INVALID_PATH;
        case (OK):
            break;
        default:
            break;
    }
    switch (argv[1][1]) {
        case ('r'):
            if (argc != 5) {
                printf("ERROR: Invalid input");
                return INVALID_INPUT;
            }
            f1 = fopen(argv[2], "r");
            f2 = fopen(argv[3], "r");
            f_out = fopen(argv[4], "r+");

            switch (r_func(f1, f2, f_out)) {
                case (INVALID_INPUT):
                    if (f1 != NULL) fclose(f1);
                    if (f2 != NULL) fclose(f2);
                    if (f_out != NULL) fclose(f_out);
                    printf("ERROR: Invalid input");
                    return INVALID_INPUT;
                case (NULL_PTR_ERROR):
                    if (f1 != NULL) fclose(f1);
                    if (f2 != NULL) fclose(f2);
                    if (f_out != NULL) fclose(f_out);
                    printf("ERROR: Null pointer error");
                    return NULL_PTR_ERROR;
                case (INVALID_PATH):
                    if (f1 != NULL) fclose(f1);
                    if (f2 != NULL) fclose(f2);
                    if (f_out != NULL) fclose(f_out);
                    printf("ERROR: Invalid path");
                    return INVALID_PATH;
                case (MEMORY_ERROR):
                    if (f1 != NULL) fclose(f1);
                    if (f2 != NULL) fclose(f2);
                    if (f_out != NULL) fclose(f_out);
                    printf("ERROR: Memory error");
                case (INVALID_DATA):
                    if (f1 != NULL) fclose(f1);
                    if (f2 != NULL) fclose(f2);
                    if (f_out != NULL) fclose(f_out);
                    printf("ERROR: Invalid data");
                    return INVALID_DATA;
                case (OK):
                    printf("done");
                    break;
            }
            fclose(f1);
            fclose(f2);
            fclose(f_out);

            break;
        case ('a'):
            if (argc != 4) {
                printf("ERROR: Invalid input");
                return INVALID_INPUT;
            }
            f1 = fopen(argv[2], "r");
            f_out = fopen(argv[3], "w");

            switch (a_func(f1, f_out)) {
                case (INVALID_INPUT):
                    if (f1 != NULL) fclose(f1);
                    if (f_out != NULL) fclose(f_out);
                    printf("ERROR: Invalid input1");
                    return INVALID_INPUT;
                case (NULL_PTR_ERROR):
                    if (f1 != NULL) fclose(f1);
                    if (f_out != NULL) fclose(f_out);
                    printf("ERROR: Null pointer error");
                    return NULL_PTR_ERROR;
                case (MEMORY_ERROR):
                    if (f1 != NULL) fclose(f1);
                    if (f_out != NULL) fclose(f_out);
                    printf("ERROR: Memory error");
                case (INVALID_DATA):
                    if (f1 != NULL) fclose(f1);
                    if (f_out != NULL) fclose(f_out);
                    printf("ERROR: Invalid data");
                    return INVALID_DATA;
                case (OK):
                    printf("done");
                    break;
                default:
                    break;
            }

            fclose(f1);
            fclose(f_out);
    }
}