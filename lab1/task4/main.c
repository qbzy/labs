
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum Errors {
    OK,
    INVALID_INPUT,
    INVALID_PATH,
    NULL_PTR_ERROR,
    MEMORY_ERROR,
};


enum Errors flags_validation(int argc, char *argv[]) {


    if (argv == NULL) {
        return NULL_PTR_ERROR;
    }

    unsigned int size = strlen(argv[1]);

    if (!(argc == 4 || argc == 3)) {
        return INVALID_INPUT;
    }

    if (argv[1][0] != '-' && argv[1][0] != '/') {
        return INVALID_INPUT;
    }

    if (size == 3) {
        if (argv[1][1] == 'n') {
            if (argc != 4) {
                return INVALID_INPUT;
            }
            if (argv[1][2] != 'd' && argv[1][2] != 'i'
                && argv[1][2] != 's' && argv[1][2] != 'a') {
                return INVALID_INPUT;
            }
        }
    } else if (size == 2) {
        if (argv[1][1] != 'd' && argv[1][1] != 'i'
            && argv[1][1] != 's' && argv[1][1] != 'a') {
            return INVALID_INPUT;
        }

    }
    return OK;
}

enum Errors path_validation_with_n(char *argv[]) {
    FILE *f = fopen(argv[2], "r");

    if (f == NULL) {
        return INVALID_PATH;
    } else {
        fclose(f);
    }

    if (strcmp(argv[2], argv[3]) == 0) {
        return INVALID_INPUT;
    }

    FILE *f_out = fopen(argv[3], "r+");

    if (f_out == NULL) {
        return INVALID_PATH;
    } else {
        fclose(f_out);
    }

    return OK;
}

enum Errors path_validation_without_n(char *argv[], char *file_out_name) {
    FILE *f = fopen(argv[2], "r");
    if (f == NULL) {
        return INVALID_PATH;
    }
    FILE *f_out = fopen(file_out_name, "w");
    if (f_out == NULL) {
        fclose(f);
        return INVALID_PATH;
    }
    f_out = fopen(file_out_name, "w");

    if (f_out == NULL) {
        return INVALID_PATH;
    }

    fclose(f);
    fclose(f_out);
    return OK;
}

void d_func(FILE *f, FILE *f_out) {
    int ch;


    while ((ch = fgetc(f)) != EOF) {
        if (!isdigit(ch)) {
            fputc(ch, f_out);
        }
    }


}

void i_func(FILE *f, FILE *f_out) {
    int counter = 0, str_cnt = 0, cur_str = 0;
    int i;
    char st[BUFSIZ];
    while (fgets(st, sizeof(st), f)) {
        str_cnt++;
    }
    rewind(f);
    while (fgets(st, sizeof(st), f)) {
        for (i = 0; st[i] != '\0'; ++i) {
            if (isalpha(st[i])) {
                ++counter;
            }
        }
        if (++cur_str != str_cnt) {
            fprintf(f_out, "%d\n", counter);
            counter = 0;
        } else {
            fprintf(f_out, "%d", counter);
        }

    }

}

void s_func(FILE *f, FILE *f_out) {
    int counter = 0, str_cnt = 0, cur_str = 0;
    int i;
    char st[BUFSIZ];
    while (fgets(st, sizeof(st), f)) {
        str_cnt++;
    }
    rewind(f);
    while (fgets(st, sizeof(st), f)) {
        for (i = 0; st[i] != '\0'; ++i) {
            if (!(isalnum(st[i]) || st[i] == ' ')) {
                ++counter;
            }
        }
        if (++cur_str != str_cnt) {
            fprintf(f_out, "%d\n", counter);
            counter = 0;
        } else {
            fprintf(f_out, "%d", counter);
        }
    }
}

void a_func(FILE *f, FILE *f_out) {
    int ch;

    while ((ch = fgetc(f)) != EOF) {
        if (!isdigit(ch) && ch != '\n') {
            fprintf(f_out, "%X", ch);
        } else {
            fputc(ch, f_out);
        }
    }
}


int main(int argc, char *argv[]) {
    FILE *f;
    FILE *f_out;
    unsigned int len;
    const char prefix[] = "out_";
    char *file_out_name;
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
        case (OK):
            break;
    }

    switch (argc) {
        case (4):
            switch (path_validation_with_n(argv)) {
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
                case (OK):
                    break;
            }

            switch (argv[1][2]) {
                case ('d'):
                    f = fopen(argv[2], "r");
                    f_out = fopen(argv[3], "w");
                    d_func(f, f_out);
                    printf("All arabic numerals were deleted");
                    fclose(f);
                    fclose(f_out);
                    break;
                case ('i'):
                    f = fopen(argv[2], "r");
                    f_out = fopen(argv[3], "w");
                    i_func(f, f_out);
                    printf("All latin literals were counted");
                    fclose(f);
                    fclose(f_out);
                    break;
                case ('s'):
                    f = fopen(argv[2], "r");
                    f_out = fopen(argv[3], "w");
                    s_func(f, f_out);
                    printf("All other symbols were counted");
                    fclose(f);
                    fclose(f_out);
                    break;
                case ('a'):
                    f = fopen(argv[2], "r");
                    f_out = fopen(argv[3], "w");
                    a_func(f, f_out);
                    printf("All other symbols were counted");
                    fclose(f);
                    fclose(f_out);
                    break;
            }
            break;
        case (3):
            len = strlen(argv[2]) + strlen("out_") + 1;
            file_out_name = (char *) malloc(len * sizeof(char));

            if (file_out_name == NULL) {
                printf("ERROR: Memory error");
                return MEMORY_ERROR;
            }

            strcpy(file_out_name, prefix);
            strcat(file_out_name, argv[2]);


            switch (path_validation_without_n(argv, file_out_name)) {
                case (INVALID_INPUT):
                    free(file_out_name);
                    printf("ERROR: Invalid input");
                    return INVALID_INPUT;
                case (NULL_PTR_ERROR):
                    free(file_out_name);
                    printf("ERROR: Null pointer error");
                    return NULL_PTR_ERROR;
                case (INVALID_PATH):
                    printf("ERROR: Invalid path");
                    free(file_out_name);
                    return INVALID_PATH;
                case (MEMORY_ERROR):
                    printf("ERROR: Memory error");
                    free(file_out_name);
                    return MEMORY_ERROR;
                case (OK):
                    break;
            }
            switch (argv[1][1]) {
                case ('d'):
                    f = fopen(argv[2], "r");
                    f_out = fopen(file_out_name, "w");
                    d_func(f, f_out);
                    printf("All arabic numerals were deleted");
                    fclose(f);
                    fclose(f_out);
                    break;
                case ('i'):
                    f = fopen(argv[2], "r");
                    f_out = fopen(file_out_name, "w");
                    i_func(f, f_out);
                    printf("All latin literals were counted");
                    fclose(f);
                    fclose(f_out);
                    break;
                case ('s'):
                    f = fopen(argv[2], "r");
                    f_out = fopen(file_out_name, "w");
                    s_func(f, f_out);
                    printf("All other symbols were counted");
                    fclose(f);
                    fclose(f_out);
                    break;
                case ('a'):
                    f = fopen(argv[2], "r");
                    f_out = fopen(file_out_name, "w");
                    a_func(f, f_out);
                    printf("All other symbols were counted");
                    fclose(f);
                    fclose(f_out);
                    break;
            }
            free(file_out_name);
            break;


    }
}
