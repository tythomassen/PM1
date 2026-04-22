#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ai_code_evaluation(void);
void prompt_refinement(void);

int main(void) {
    int choice;

    printf("AI-Assisted Development Lab\n");
    printf("1. AI Code Evaluation\n");
    printf("2. Prompt Refinement\n");
    printf("Choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            ai_code_evaluation();
            break;
        case 2:
            prompt_refinement();
            break;
        default:
            printf("Invalid choice.\n");
    }

    return 0;
}

void ai_code_evaluation(void) {
    printf("=== AI Code Evaluation ===\n");

    int n = 5;
    int *arr = malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = (i + 1) * 10;
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    printf("Sum: %d\n", sum);

    free(arr);
    printf("Memory freed. Evaluation complete.\n");
}

void prompt_refinement(void) {
    printf("=== Prompt Refinement ===\n");

    char str[] = "Hello, AI!";
    printf("Original: %s\n", str);

    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char tmp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = tmp;
    }

    printf("Reversed: %s\n", str);
    printf("Prompt refinement complete.\n");
}