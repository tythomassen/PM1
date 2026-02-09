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
        // TODO: Read two numbers, call add/subtract/multiply
        scanf("%d %d", &a, &b);
    } else if (choice == 2) {
        // TODO: Read Fahrenheit, convert to Celsius
        scanf("%lf", &f);
    }
    
    return 0;
}