#include <stdio.h>

void pointer_basics(void);
void array_pointer(void);
void memory_addresses(void);

int main(void) {
    int choice;
    printf("Select exercise:\n");
    printf("1. Pointer Basics\n");
    printf("2. Array-Pointer\n");
    printf("3. Memory Addresses\n");
    printf("Choice: ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1: pointer_basics(); break;
        case 2: array_pointer(); break;
        case 3: memory_addresses(); break;
        default: printf("Invalid choice\n");
    }
    return 0;
}

void pointer_basics(void) {
    // TODO: Implement - must show pointer syntax in output
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int *ptr = &size; 
    printf("Pointer val: %d\n", size);
    printf("Pointer value: %d\n", *ptr);
    printf("Pointer address: %p\n", (void*)&ptr);

    *ptr =  (*ptr) * 2;
    printf("Pointer value after doubling: %d\n", *ptr);
    printf("Pointer val: %d\n", size);
}

void array_pointer(void) {
    // TODO: Implement - must show both arr[i] and *(ptr+i) syntax
int size;
    printf("Enter array size: ");
    scanf("%d", &size);

    int arr[size];
    printf("Enter %d elements: ", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
    for (int i = 0; i < size; i++) {
        printf("arr[%d] = %d, *(arr + %d) = %d\n", i, arr[i], i, *(arr + i));
    }
    for (int i = 0; i < size; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }


}

void memory_addresses(void) {
    // TODO: Implement - must show hex addresses and sizeof
    int arr[3] = {10, 20, 30};
    
    printf("\n Memory Layout\n");
    printf("Size of one integer: %zu bytes\n", sizeof(int));
    
    printf("Array addresses (Contiguous Layout):\n");
    for (int i = 0; i < 3; i++) {
        // Printing the address of each element
        printf("Address of arr[%d] (&arr[%d]): %p\n", i, i, (void*)&arr[i]);
    }
    
    printf("\nNote: Notice how each hex address increases by %zu (the sizeof(int))!\n", sizeof(int));
}
