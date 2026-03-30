#include <stdio.h>

int main(void) {
    int n = 5; // Set n to the number of rows you want
    
    for (int i = 1; i <= n; i++) { // Outer loop for rows
        for (int j = 1; j <= i; j++) { // Inner loop for stars
            printf("*");
        }
        printf("\n"); // Move to the next line after each row
    }
    
    return 0;
}