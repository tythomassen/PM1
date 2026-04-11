/**
 * HW4: Structures and File I/O - Main Driver Program
 * DO NOT MODIFY THIS FILE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void test_student_records(void);
void test_csv_parser(void);
void test_contact_book(void);
void test_log_analyzer(void);
void create_sample_files(void);

int main(void) {
    int choice;
    
    printf("===========================================\n");
    printf("      HW4: Structures and File I/O        \n");
    printf("===========================================\n\n");
    
    // Create sample test files
    create_sample_files();
    
    printf("Select a problem to test:\n");
    printf("1. Student Records\n");
    printf("2. CSV Parser\n");
    printf("3. Contact Book\n");
    printf("4. Log Analyzer\n");
    printf("5. Run All\n");
    printf("0. Exit\n");
    printf("\nEnter choice: ");
    
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    printf("\n");
    
    switch (choice) {
        case 1: test_student_records(); break;
        case 2: test_csv_parser(); break;
        case 3: test_contact_book(); break;
        case 4: test_log_analyzer(); break;
        case 5:
            test_student_records();
            printf("\n-------------------------------------------\n\n");
            test_csv_parser();
            printf("\n-------------------------------------------\n\n");
            test_contact_book();
            printf("\n-------------------------------------------\n\n");
            test_log_analyzer();
            break;
        case 0:
            printf("Goodbye!\n");
            break;
        default:
            printf("Invalid choice\n");
    }
    
    return 0;
}

void create_sample_files(void) {
    // Create sample students.csv
    FILE *f = fopen("students.csv", "w");
    if (f) {
        fprintf(f, "id,name,gpa,credits\n");
        fprintf(f, "12345,John Doe,3.75,60\n");
        fprintf(f, "12346,Jane Smith,3.92,45\n");
        fprintf(f, "12347,Bob Johnson,3.50,90\n");
        fprintf(f, "12348,Alice Brown,2.85,30\n");
        fprintf(f, "12349,Charlie Wilson,3.65,75\n");
        fclose(f);
    }
    
    // Create sample log file
    f = fopen("sample.log", "w");
    if (f) {
        fprintf(f, "[2024-01-15 10:30:45] INFO: User login successful\n");
        fprintf(f, "[2024-01-15 10:31:02] WARNING: Invalid password attempt\n");
        fprintf(f, "[2024-01-15 10:32:15] ERROR: Database connection failed\n");
        fprintf(f, "[2024-01-15 10:33:00] INFO: User logged out\n");
        fprintf(f, "[2024-01-15 10:34:20] INFO: New user registered\n");
        fprintf(f, "[2024-01-15 10:35:45] WARNING: Low disk space\n");
        fprintf(f, "[2024-01-15 10:36:10] ERROR: File not found\n");
        fclose(f);
    }
}

void test_student_records(void) {
    printf("===== Problem 1: Student Records =====\n\n");
    
    // Test student_init and student_print
    Student s1;
    printf("Creating student...\n");
    int result = student_init(&s1, 12345, "John Doe", 3.75, 60);
    printf("student_init returned: %d\n", result);
    printf("student_print: ");
    student_print(&s1);
    printf("\n\n");
    
    // Test with array
    Student students[5];
    student_init(&students[0], 1, "Alice", 3.9, 50);
    student_init(&students[1], 2, "Bob", 3.5, 60);
    student_init(&students[2], 3, "Charlie", 3.7, 45);
    student_init(&students[3], 4, "Diana", 3.2, 70);
    student_init(&students[4], 5, "Eve", 3.8, 55);
    
    // Test find_by_id
    printf("Finding student with ID 3...\n");
    Student *found = student_find_by_id(students, 5, 3);
    if (found) {
        printf("Found: ");
        student_print(found);
        printf("\n");
    } else {
        printf("Not found\n");
    }
    
    // Test average GPA
    printf("\nAverage GPA: %.2f (expected ~3.62)\n", 
           students_average_gpa(students, 5));
    
    // Test compare
    printf("\nComparing Alice (3.9) vs Bob (3.5): %d (expected: positive)\n",
           student_compare_gpa(&students[0], &students[1]));
}

void test_csv_parser(void) {
    printf("===== Problem 2: CSV Parser =====\n\n");
    
    // Test reading CSV
    Student students[MAX_STUDENTS];
    printf("Reading students.csv...\n");
    int count = read_students_csv("students.csv", students, MAX_STUDENTS);
    printf("Read %d students\n\n", count);
    
    if (count > 0) {
        printf("Students:\n");
        for (int i = 0; i < count; i++) {
            printf("  ");
            student_print(&students[i]);
            printf("\n");
        }
        
        // Test filter
        printf("\nFiltering by GPA >= 3.5...\n");
        Student filtered[MAX_STUDENTS];
        int filtered_count = filter_by_gpa(students, count, filtered, MAX_STUDENTS, 3.5);
        printf("Found %d students with GPA >= 3.5\n", filtered_count);
        
        // Write filtered to file
        write_students_csv("honors.csv", filtered, filtered_count, 1);
        printf("Wrote honors.csv\n");
    }
}

void test_contact_book(void) {
    printf("===== Problem 3: Contact Book =====\n\n");
    
    ContactBook book;
    contactbook_init(&book, "contacts.dat");
    
    // Add contacts
    printf("Adding contacts...\n");
    contactbook_add(&book, "Alice Smith", "555-1234", "alice@email.com");
    contactbook_add(&book, "Bob Jones", "555-5678", "bob@email.com");
    contactbook_add(&book, "Charlie Brown", "555-9012", "charlie@email.com");
    
    printf("Contact book (%d contacts):\n", book.count);
    contactbook_print(&book);
    
    // Search
    printf("\nSearching for 'Bob'...\n");
    Contact *found = contactbook_search(&book, "Bob");
    if (found) {
        printf("Found: %s, %s, %s\n", found->name, found->phone, found->email);
    } else {
        printf("Not found\n");
    }
    
    // Save and reload
    printf("\nSaving to contacts.dat...\n");
    contactbook_save(&book);
    
    ContactBook book2;
    contactbook_init(&book2, "contacts.dat");
    printf("Loading from contacts.dat...\n");
    int loaded = contactbook_load(&book2);
    printf("Loaded %d contacts:\n", loaded);
    contactbook_print(&book2);
    
    // Remove
    printf("\nRemoving 'Bob Jones'...\n");
    contactbook_remove(&book2, "Bob Jones");
    printf("After removal (%d contacts):\n", book2.count);
    contactbook_print(&book2);
}

void test_log_analyzer(void) {
    printf("===== Problem 4: Log Analyzer =====\n\n");
    
    // Test parse_log_level
    printf("parse_log_level tests:\n");
    printf("  'INFO' -> %d (expected: 0)\n", parse_log_level("INFO"));
    printf("  'WARNING' -> %d (expected: 1)\n", parse_log_level("WARNING"));
    printf("  'ERROR' -> %d (expected: 2)\n", parse_log_level("ERROR"));
    printf("  'UNKNOWN' -> %d (expected: 3)\n\n", parse_log_level("UNKNOWN"));
    
    // Test parse_log_line
    printf("parse_log_line test:\n");
    LogEntry entry;
    const char *test_line = "[2024-01-15 10:30:45] INFO: User login successful";
    if (parse_log_line(test_line, &entry) == 0) {
        printf("  Timestamp: %s\n", entry.timestamp);
        printf("  Level: %d\n", entry.level);
        printf("  Message: %s\n\n", entry.message);
    } else {
        printf("  Parse failed\n\n");
    }
    
    // Test analyze_log_file
    printf("Analyzing sample.log...\n");
    LogStats stats;
    if (analyze_log_file("sample.log", &stats) == 0) {
        print_log_stats(&stats);
    } else {
        printf("Failed to analyze log file\n");
    }
    
    // Test filter
    printf("\nFiltering ERROR entries to errors.log...\n");
    int filtered = filter_logs_by_level("sample.log", "errors.log", LOG_ERROR);
    printf("Wrote %d error entries\n", filtered);
}

