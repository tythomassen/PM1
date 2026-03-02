#include <stdio.h>
#include "functions.h"
int main(void) {
    int choice;
    printf("Select exercise:\n");
    printf("1. Basic Functions\n");
    printf("2. Temperature Conversion\n");
    printf("Choice: ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        int a, b;
        printf("Enter two numbers: ");
        scanf("%d %d", &a, &b);
        printf("Add: %d\n", add(a, b));
        printf("Subtract: %d\n", subtract(a, b));
        printf("Multiply: %d\n", multiply(a, b));
    } else if (choice == 2) {
        double temp;
        printf("Enter Fahrenheit: ");
        scanf("%lf", &temp);
        printf("%.2f F = %.2f C\n", temp, fahrenheit_to_celsius(temp));
    }
    
    return 0;
}
