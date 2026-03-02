#include <stdio.h>

int main(void) {
    int temp;
    scanf("%d", &temp);

    // TODO: Implement classification logic
    // Use if/else or switch statement

    if (temp < -40)  {
        printf("invalid\n");
    } else if (temp >= -40 && temp <= 31) {
        printf("Freezing\n");
    } else if (temp >= 32 && temp <= 59) {
        printf("cold\n");
    } else if (temp >= 60 && temp <= 79) {
        printf("warm\n");
    } else if (temp >= 80 && temp <= 120) {
        printf("hot\n");
    } else {
        printf("invalid\n");
    }

    return 0;
}