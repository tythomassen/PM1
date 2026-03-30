#include <stdio.h>

struct Student {
    int id;
    int grade;
};

int main(void) {
    struct Student s;
    scanf("%d %d", &s.id, &s.grade);
    printf("Student %d has grade %d\n", s.id, s.grade);
    return 0;
}
