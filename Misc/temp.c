#include <stdio.h>

int main(void) {
    int temp;
    scanf("%d", &temp);

    if (temp < -40) {
        printf("invalid\n");
    } else if (temp <= 31) { 
        printf("freezing\n"); 
    } else if (temp <= 59) { 
        printf("cold\n");
    } else if (temp <= 79) { 
        printf("warm\n");
    } else if (temp <= 120) { 
        printf("hot\n");
    } else {                
        printf("invalid\n");
    }

    return 0;
}
