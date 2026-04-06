#include <stdio.h>
#include <limits.h>

int main(void) {
    // TODO: Read integers until scanf returns EOF
    // Track the maximum
    // Print the maximum
    int n, max; 
    scanf("%d", &max);
    while (scanf("%d", &n) == 1) { 
        if (n > max) {
            max = n; 
        }
    }

    printf("%d\n", max);
    
    return 0;
}
