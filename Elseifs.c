#include <stdio.h>

int main() {
    // You can change this value to test different cases
    int x = 1; 

    switch (x) {
        case 1: 
            printf("one\n");
            break; // Stops it from running into case 2
        case 2: 
            printf("two\n");
            break; // Stops it from running into case 3
        case 3:
            printf("three\n");
            break;
        default:
            printf("other\n");
            break;
    }

    return 0;
}