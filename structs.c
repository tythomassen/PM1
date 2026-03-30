#include <stdio.h>
#include <string.h>

// --- Data Structures ---

typedef struct {
    char name[50];
    int age;
    float gpa;
} Student;

typedef struct {
    int day, month, year;
} Date;

typedef struct {
    char name[50];
    Date birthdate;
    Date enrollment;
} Person;

typedef enum { CIRCLE, RECTANGLE, TRIANGLE } ShapeType;

typedef union {
    float radius;                          
    struct { float width, height; } rect;  
    struct { float base, h; } tri;         
} ShapeData;

typedef struct {
    ShapeType type;
    ShapeData data;
} Shape;

// --- Function Prototypes ---
void test_basic_struct(void);
void test_nested_struct(void);
void test_unions_enums(void);

// --- Main Program ---
int main(void) {
    int choice;
    printf("Select exercise:\n");
    printf("1. Basic Structures\n");
    printf("2. Nested Structures\n");
    printf("3. Unions and Enums\n");
    printf("Choice: ");
    
    if (scanf("%d", &choice) != 1) return 1;
    
    // Clear buffer after scanf to avoid issues with subsequent gets/scanfs
    while(getchar() != '\n');

    switch (choice) {
        case 1: test_basic_struct(); break;
        case 2: test_nested_struct(); break;
        case 3: test_unions_enums(); break;
        default: printf("Invalid choice\n");
    }
    return 0;
}

// --- Implementation ---

void test_basic_struct(void) {
    Student s;
    
    printf("\n--- Basic Structure Exercise ---\n");
    printf("Enter student name: ");
    scanf("%49s", s.name);
    printf("Enter age: ");
    scanf("%d", &s.age);
    printf("Enter GPA: ");
    scanf("%f", &s.gpa);
    
    printf("\n[Output] Student: %s | Age: %d | GPA: %.2f\n", s.name, s.age, s.gpa);
}

void test_nested_struct(void) {
    printf("\n--- Nested Structure Exercise ---\n");
    Person p = {
        .name = "John Doe",
        .birthdate = {15, 6, 2000},
        .enrollment = {1, 9, 2022}
    };
    
    printf("Name: %s\n", p.name);
    printf("Date of Birth: %02d/%02d/%04d\n", p.birthdate.day, p.birthdate.month, p.birthdate.year);
    printf("Enrollment Date: %02d/%02d/%04d\n", p.enrollment.day, p.enrollment.month, p.enrollment.year);
}

void test_unions_enums(void) {
    printf("\n--- Unions and Enums Exercise ---\n");
    
    // Creating an array of different shapes
    Shape shapes[2];

    // Setup a Circle
    shapes[0].type = CIRCLE;
    shapes[0].data.radius = 5.0;

    // Setup a Rectangle
    shapes[1].type = RECTANGLE;
    shapes[1].data.rect.width = 4.0;
    shapes[1].data.rect.height = 10.0;

    for (int i = 0; i < 2; i++) {
        printf("Shape %d: ", i + 1);
        if (shapes[i].type == CIRCLE) {
            float area = 3.14159f * shapes[i].data.radius * shapes[i].data.radius;
            printf("Circle | Radius: %.1f | Area: %.2f\n", shapes[i].data.radius, area);
        } else if (shapes[i].type == RECTANGLE) {
            float area = shapes[i].data.rect.width * shapes[i].data.rect.height;
            printf("Rectangle | W: %.1f, H: %.1f | Area: %.2f\n", 
                    shapes[i].data.rect.width, shapes[i].data.rect.height, area);
        }
    }
}