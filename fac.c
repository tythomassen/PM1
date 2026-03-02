/*
 * Pop Quiz - Loops Review (Section 02)
 * Topic: Loops
 * 
 * TASK: Factorial Calculator
 * 
 * Read a non-negative integer N from stdin.
 * Compute N! (N factorial) using a loop.
 * Print the result.
 * 
 * Remember: 0! = 1, 1! = 1, 5! = 120
 * 
 * Requirements:
 * 1. Use a loop (for, while, or do-while)
 * 2. Read N from stdin
 * 3. Print the factorial as an integer
 * 
 * Input: A single non-negative integer N (0 <= N <= 12)
 * Output: N!
 * 
 * Examples:
 *   Input: 5      Output: 120
 *   Input: 0      Output: 1
 *   Input: 10     Output: 3628800
 */

#include <stdio.h>

int main(void) {
    int n;
    scanf("%d", &n);
    if (n < 0 || n > 12) {
        printf("Invalid input.\n");
        return 1; // Exit with error code
    } else {
        int factorial = 1;
        for (int i = 1; i <= n; i++) {
            factorial *= i;
        }
        printf("%d\n", factorial);
    }

    
    // TODO: Use a loop to compute n factorial
    // Print the result with printf("%d\n", result);
    
    return 0;
}
