#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --- Problem 1: Swap Functions --- */

void swap_int(int *a, int *b) {
    if (!a || !b) return;
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap_double(double *a, double *b) {
    if (!a || !b) return;
    double temp = *a;
    *a = *b;
    *b = temp;
}

void swap_pointers(int **a, int **b) {
    if (!a || !b) return;
    int *temp = *a;
    *a = *b;
    *b = temp;
}

void rotate_three(int *a, int *b, int *c) {
    if (!a || !b || !c) return;
    int temp = *c;
    *c = *b;
    *b = *a;
    *a = temp;
}

/* --- Problem 2: Array Operations via Pointers --- */

void array_reverse_ptr(int *arr, int size) {
    if (!arr || size <= 0) return;
    int *start = arr;
    int *end = arr + (size - 1);
    while (start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

int* find_element(int *arr, int size, int target) {
    if (!arr) return NULL;
    for (int i = 0; i < size; i++) {
        if (*(arr + i) == target) return (arr + i);
    }
    return NULL;
}

void array_copy_ptr(int *dest, const int *src, int size) {
    if (!dest || !src) return;
    for (int i = 0; i < size; i++) {
        *(dest + i) = *(src + i);
    }
}

void array_stats(const int *arr, int size, int *sum, int *min, int *max) {
    if (!arr || size <= 0) return;
    *sum = 0;
    *min = *arr;
    *max = *arr;
    for (int i = 0; i < size; i++) {
        int val = *(arr + i);
        *sum += val;
        if (val < *min) *min = val;
        if (val > *max) *max = val;
    }
}

/* --- Problem 3: Dynamic Array --- */

int* create_array(int size) {
    if (size < 0) return NULL;
    return (int *)malloc(size * sizeof(int));
}

int* resize_array(int *arr, int old_size, int new_size) {
    if (new_size < 0) return arr;
    int *new_arr = realloc(arr, new_size * sizeof(int));
    return new_arr; 
}

void fill_array(int *arr, int size, int value) {
    if (!arr) return;
    for (int i = 0; i < size; i++) {
        *(arr + i) = value;
    }
}

void free_array(int **arr) {
    if (!arr || !*arr) return;
    free(*arr);
    *arr = NULL;
}

int* duplicate_array(const int *src, int size) {
    if (!src || size < 0) return NULL;
    int *copy = malloc(size * sizeof(int));
    if (!copy) return NULL;
    for (int i = 0; i < size; i++) {
        *(copy + i) = *(src + i);
    }
    return copy;
}

/* --- Problem 4: String Builder --- */

char* string_create(void) {
    char *s = malloc(1);
    if (s) *s = '\0';
    return s;
}

int string_length(const char *builder) {
    if (!builder) return 0;
    int len = 0;
    while (*(builder + len) != '\0') len++;
    return len;
}

int string_append(char **builder, const char *str) {
    if (!builder || !*builder || !str) return -1;
    int current_len = string_length(*builder);
    int append_len = string_length(str);
    
    char *new_str = realloc(*builder, current_len + append_len + 1);
    if (!new_str) return -1;
    
    *builder = new_str;
    strcpy(*builder + current_len, str);
    return 0;
}

int string_append_char(char **builder, char c) {
    if (!builder || !*builder) return -1;
    int current_len = string_length(*builder);
    
    char *new_str = realloc(*builder, current_len + 2);
    if (!new_str) return -1;
    
    *builder = new_str;
    *(*builder + current_len) = c;
    *(*builder + current_len + 1) = '\0';
    return 0;
}

void string_free(char **builder) {
    if (!builder || !*builder) return;
    free(*builder);
    *builder = NULL;
}
