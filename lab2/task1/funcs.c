
#include "funcs.h"



enum Errors str_to_ull(const char *str, unsigned long long int *converted_x) {
    if (str == NULL || converted_x == NULL) {
        return NULL_PTR_ERROR;
    }

    char *endptr;

    *converted_x = strtoull(str, &endptr, 10);

    if (*converted_x == ULLONG_MAX) {
        return RANGE_ERROR;
    }

    if (*endptr != '\0') {
        return INVALID_INPUT;
    }

    return OK;
}


enum Errors flags_validation(char *argv[]) {

    if (argv == NULL) {
        return NULL_PTR_ERROR;
    }
    if (argv[1][0] != '-') {
        return INVALID_INPUT;
    }
    if (argv[1][1] != 'l' && argv[1][1] != 'r' && argv[1][1] != 'u' && argv[1][1] != 'n' && argv[1][1] != 'c') {
        return INVALID_INPUT;
    }


    return OK;
}


enum Errors l_flag(char * str, int * length){
    char * i = NULL;
    if (!str || !length){
        return NULL_PTR_ERROR;
    }
    for (i = str; *i != '\0'; i++) {
        (*length)++;
    }

    return OK;
}

enum Errors r_flag(char *str, char **result){
    char *temp;
    char len_finder[BUFSIZ];
    char *i = NULL;
    int length = 0, k = 0;
    if (!str || !result){
        return NULL_PTR_ERROR;
    }

    temp = (char *) malloc(sizeof(char *) * BUFSIZ);
    if (!temp){
        return MEMORY_ERROR;
    }

    for (i = str; *i != '\0'; i++){

        len_finder[length++] = *i;

    }

    for (int j = length - 1; j >= 0; j--){
        temp[k++] = len_finder[j];
    }

    *result = temp;

    return OK;

}

enum Errors u_flag(char *str, char **result){
    char * temp;
    int index = 0;
    char *i = NULL;
    if (!str || !result){
        return NULL_PTR_ERROR;
    }

    temp = (char *) malloc(sizeof(char *) * BUFSIZ);
    if (!temp){
        return MEMORY_ERROR;
    }

    for (i = str; *i != '\0'; i++){
        if (((index) & 1) != 0){
            temp[index++] = (char) toupper(*i);
        }
        else{
            temp[index++] = *i;
        }
    }
    *result = temp;
    return OK;

}

enum Errors n_flag(char *str, char **result){
    char * temp;
    int index = 0;
    char digits[BUFSIZ];
    char alphas[BUFSIZ];
    char others[BUFSIZ];
    int digits_index = 0, alphas_index = 0, others_index = 0;
    char *i = NULL;
    if (!str || !result){
        return NULL_PTR_ERROR;
    }
    temp = (char *) malloc(sizeof(char *) * BUFSIZ * 3);
    if (!temp){
        return MEMORY_ERROR;
    }
    for (i = str; *i != '\0'; i++){
        if (isdigit(*i)){
            digits[digits_index++] =  *i;
        }else if(isalpha(*i)){
            alphas[alphas_index++] = *i;
        }else{
            others[others_index++] = *i;
        }
    }
    for (int k = 0; k < digits_index; ++k){
        temp[index++] = digits[k];
    }
    for (int j = 0; j < alphas_index; ++j){
        temp[index++] = alphas[j];
    }
    for (int k = 0; k < others_index; ++k){
        temp[index++] = others[k];
    }

    *result = temp;

    return OK;
}

enum Errors c_flag(int argc, char *argv[], char **result){
    int cnt = 0;
    int num_selected = 0;
    int max_selected;
    char **input_strings;
    unsigned long long int seed;

    if (!argv || !result){
        return NULL_PTR_ERROR;
    }


    enum Errors err = str_to_ull(argv[2], &seed);
    if (err != OK) {
        return err;
    }

    int num_strings = argc - 3;
    if (num_strings < 1) {
        return INVALID_INPUT;
    }

    input_strings = &argv[3];

    max_selected = num_strings;
    char **selected_strings = (char **)malloc(sizeof(char *) * max_selected);
    if (!selected_strings) {
        return MEMORY_ERROR;
    }
    char* used_strings = (char *) malloc(sizeof(char *) * max_selected);
    if(!used_strings){
        free(selected_strings);
        return MEMORY_ERROR;
    }
    char **shuffled = (char **)malloc(sizeof(char *) * max_selected);
    if (!shuffled){
        free(selected_strings);
        free(used_strings);
        return MEMORY_ERROR;
    }
    for (int i = 0; i < num_strings; i++) {
        selected_strings[num_selected++] = input_strings[i];
    }

    srand((unsigned int)seed);
    for(int i = 0; i < max_selected; i++){
        used_strings[i] = '-';
    }

    while (cnt != num_selected){
        int i = rand() % (num_selected);
        if (used_strings[i] != (char) '+'){
            used_strings[i] = '+';
            shuffled[cnt++] = selected_strings[i];
        }
    }

    int total_length = 0;
    for (int i = 0; i < num_selected; i++) {
        int len = 0;
        while (shuffled[i][len] != '\0') {
            len++;
        }
        total_length += len;
    }

    char *temp_result = (char *)malloc(sizeof(char) * (total_length + 1));
    if (!temp_result) {
        free(selected_strings);
        free(used_strings);
        free(shuffled);
        return MEMORY_ERROR;
    }


    int pos = 0;
    for (int i = 0; i < num_selected; i++) {
        int k = 0;
        while (shuffled[i][k] != '\0') {
            temp_result[pos++] = shuffled[i][k++];
        }
    }
    temp_result[pos] = '\0';

    free(selected_strings);
    free(used_strings);
    free(shuffled);
    *result = temp_result;

    return OK;
}