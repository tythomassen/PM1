#include <stdio.h>
#include "utils.h"

int main(void) {
    printf("=== Multi-file Project Demo ===\n\n");
    
    int a = 10, b = 5;
    printf("Basic operations with %d and %d:\n", a, b);
    printf("  Add: %d\n", add(a, b));
    printf("  Subtract: %d\n", subtract(a, b));
    printf("  Multiply: %d\n", multiply(a, b));
    
    printf("\nFactorial examples:\n");
    for (int i = 1; i <= 5; i++) {
        printf("  %d! = %d\n", i, factorial(i));
    }
    
    printf("\nFibonacci sequence:\n  ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", fibonacci(i));
    }
    printf("\n");
    
    return 0;
}