#include <stdio.h>

int main(void) {
    int n;
    scanf("%d", &n);
    
    int arr[10];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    // TODO: Compute the product of all elements
    // Print the result
    int product = 1;
    for (int i = 0; i < n; i++) {
        product *= arr[i];
    }
    printf("%d\n", product);
    return 0;
}