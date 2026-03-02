#include <stdio.h>

void pattern_printing(void);
void number_analyzer(void);
void guessing_game(void);

int main(void) {
    int choice;
    printf("Select exercise:\n");
    printf("1. Pattern Printing\n");
    printf("2. Number Analyzer\n");
    printf("3. Guessing Game\n");
    printf("Choice: ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1: pattern_printing(); break;
        case 2: number_analyzer(); break;
        case 3: guessing_game(); break;
        default: printf("Invalid choice\n");
    }
    return 0;
}

void pattern_printing(void) {
    // TODO: Read size, print right triangle, print inverted triangle
    // Use nested for loops
    int size;
    printf("Enter Size 1-10: ");
    scanf("%d", &size);
    if (size < 1 || size > 10) {
        printf("Invalid size\n");
        return;
    }
    else
    {
        printf("Right Triangle:\n");
        for (int i = 1; i <= size; i++) {
            for (int j = 1; j <= i; j++) {
                printf("*");
            }
            printf("\n");
        }
        printf("Inverted Triangle:\n");
        for (int i = size; i >= 1; i--) {
            for (int j = 1; j <= i; j++) {
                printf("*");
            }
            printf("\n");
        }
    } // End of else
} // End of function
void number_analyzer(void) {
    // TODO: Read positive integer
    // Calculate digits, sum, even/odd, reversed using while loops
    int num;
    printf("Enter a Positive Number: ");
    scanf("%d", &num);
    if (num <= 0) {
        printf("Invalid number\n");
        return;
    } else {
        int digits = 0, sum = 0, reversed = 0, temp = num;
        while (temp > 0) {
            int digit = temp % 10;
            sum += digit;
            reversed = reversed * 10 + digit;
            temp /= 10;
            digits++;
        }
        printf("Digits: %d\n", digits);
        printf("Sum: %d\n", sum);
        printf("Even/Odd: %s\n", (num % 2 == 0) ? "Even" : "Odd");
        printf("Reversed: %d\n", reversed);



    }
}

void guessing_game(void) {
    int secret = 42;
    int guess;
    int count = 0;
    do{
        printf("Guess the number (1-100): ");
        scanf("%d", &guess);
        if (guess < 1 || guess > 100) {
            printf("Out of range! \n");
        } else {
            count++;
            if (guess < secret) {
                printf("Too low!\n");
            } else if (guess > secret) {
                printf("Too high!\n");
            } else {
                printf("Correct! You guessed it in %d valid guesses.\n", count);
            }
        }
    } while (guess != secret);
    // TODO: Use do-while to loop until correct guess
    // Validate input range 1-100
    // Count valid guesses only
}