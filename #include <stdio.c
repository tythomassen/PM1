#include <stdio.h>
#include <stdlib.h>

void test_malloc_free(void);
void test_calloc_realloc(void);

int main(void) {
    int choice;
    
    while (1) {
        printf("\nSelect exercise:\n");
        printf("1. malloc/free\n");
        printf("2. calloc/realloc\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 0: return 0;
            case 1: test_malloc_free(); break;
            case 2: test_calloc_realloc(); break;
            default: printf("Invalid choice\n");
        }
    }
}

void test_malloc_free(void) {
    // TODO: Implement
    // Must show: allocation, values, freeing
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
}

void test_calloc_realloc(void) {
    // TODO: Implement
    // Must show: calloc zeros, realloc resize
}

