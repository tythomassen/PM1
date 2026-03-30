#include <stdio.h>

void array_operations(void);
void search_array(void);
void sort_array(void);

int main(void) {
    int choice;
    printf("Select exercise:\n");
    printf("1. Array Operations\n");
    printf("2. Searching\n");
    printf("3. Sorting\n");
    printf("Choice: ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1: array_operations(); break;
        case 2: search_array(); break;
        case 3: sort_array(); break;
        default: printf("Invalid choice\n");
    }
    return 0;
}

void array_operations(void) {
    // TODO: Read array, calculate sum, avg, min, max
    // Label your output clearly
    int n; 
    printf("Enter Array Size: "); 
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
}
int sum = 0, min = arr[0], max = arr[0];
for (int i = 0; i < n; i++) {
    sum += arr[i];
    if (arr[i] < min) min = arr[i];
    if (arr[i] > max) max = arr[i];
}   
double avg = (double)sum / n;
printf("Sum: %d\n", sum);
printf("Average: %.2f\n", avg);
printf("Minimum: %d\n", min);
printf("Maximum: %d\n", max);
}
void search_array(void) {
    int n; 
    printf("Enter Array Size: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    int search_value;
    printf("Enter value to search: ");
    scanf("%d", &search_value);
    int found_index = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] == search_value) {
            found_index = i;
            break;
        }
    }
    if (found_index != -1) {
        printf("Value found at index: %d\n", found_index);
    } else {
        printf("Value not found in the array.\n");
    }    
    // TODO: Read array, read search value
    // Report index if found, "not found" otherwise
}

void sort_array(void) {
    int n;
    printf("Enter Array Size: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    // TODO: Read array, sort with bubble sort
    // Display sorted result
}
