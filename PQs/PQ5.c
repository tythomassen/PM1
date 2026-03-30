#include <stdio.h>

// TODO: Implement triple_value function
void triple_value(int *p) {
    // Your code here
    *p = *p * 3;
}

int main(void) {
    int x;
    scanf("%d", &x);
    
    triple_value(&x);
    printf("%d\n", x);
    
    return 0;
}