#include <stdio.h>

int main(void) {
    int number = 42;
    float pi = 3.14159;
    char letter = 'A';
    char word[] = "Hello";
    int hexNumber = 255;

    printf("Hello, World!\n");

    printf("Integer (%%d): %d\n", number);
    printf("Float (%%f): %f\n", pi);
    printf("Float with width/precision (%%8.2f): %8.2f\n", pi);
    printf("Character (%%c): %c\n", letter);
    printf("String (%%s): %s\n", word);
    printf("Hexadecimal (%%x): %x\n", hexNumber);

    return 0;
}
