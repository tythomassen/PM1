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
    int size = 5; 
    int *arr = (int *)malloc(size * sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Memory successfully allocated at address: %p\n", (void*)arr);

    for (int i = 0; i < size; i++) {
        arr[i] = i * 10; 
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    free(arr);
    printf("Memory freed successfully.\n");
}

void test_calloc_realloc(void) {
    int initial_size = 5; 
    int new_size = 10;    
    
    int *arr = (int *)calloc(initial_size, sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Calloc address: %p\n", (void*)arr);
    for (int i = 0; i < initial_size; i++) {
        printf("Initial arr[%d] = %d\n", i, arr[i]); 
    }


    int *temp = (int *)realloc(arr, new_size * sizeof(int));
    if (temp == NULL) {
        printf("Memory reallocation failed!\n");
        free(arr); 
        return;
    }
    arr = temp; 

    
    for (int i = 0; i < new_size; i++) {
        if (i >= initial_size) arr[i] = (i + 1) * 100; 
        printf("Post-realloc arr[%d] = %d\n", i, arr[i]);
    }

    free(arr); 
    printf("Memory freed successfully.\n");
}