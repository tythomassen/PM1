#include <stdio.h>

int main(void) {
    int n;
    scanf("%d", &n);
    
    int arr[10];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    // TODO: Compute the average of all elements
    // Print the result with 2 decimal places: printf("%.2f\n", avg);
   
    double avg = sum/n;
    printf("%.2f\n", avg);
    return 0;
}
