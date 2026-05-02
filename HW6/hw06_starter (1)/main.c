/**
 * HW6: Mini Database System - Main Program
 * 
 * This provides an interactive menu for testing your database.
 * You may modify this file for testing purposes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "search.h"
#include "display.h"

void print_menu(void);
void handle_add(Database *db);
void handle_search(Database *db);
void handle_update(Database *db);
void handle_delete(Database *db);
void handle_sort(Database *db);
void add_sample_data(Database *db);

int main(void) {
    printf("===========================================\n");
    printf("      HW6: Mini Database System           \n");
    printf("===========================================\n\n");
    
    Database *db = db_create("students.db");
    if (db == NULL) {
        printf("Failed to create database\n");
        return 1;
    }
    
    // Try to load existing data
    int loaded = db_load(db);
    if (loaded > 0) {
        printf("Loaded %d records from students.db\n\n", loaded);
    } else {
        printf("No existing data found. Starting fresh.\n\n");
    }
    
    int choice;
    do {
        print_menu();
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');  // Clear input buffer
            choice = -1;
        }
        printf("\n");
        
        switch (choice) {
            case 1:
                handle_add(db);
                break;
            case 2:
                db_print_all(db);
                break;
            case 3:
                handle_search(db);
                break;
            case 4:
                handle_update(db);
                break;
            case 5:
                handle_delete(db);
                break;
            case 6:
                handle_sort(db);
                break;
            case 7:
                db_print_summary(db);
                break;
            case 8:
                if (db_save(db) == 0) {
                    printf("Database saved successfully.\n");
                } else {
                    printf("Failed to save database.\n");
                }
                break;
            case 9:
                add_sample_data(db);
                break;
            case 0:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice\n");
        }
        printf("\n");
    } while (choice != 0);
    
    db_destroy(db);
    return 0;
}

void print_menu(void) {
    printf("--- Menu ---\n");
    printf("1. Add student\n");
    printf("2. List all students\n");
    printf("3. Search\n");
    printf("4. Update student\n");
    printf("5. Delete student\n");
    printf("6. Sort\n");
    printf("7. Print summary\n");
    printf("8. Save to file\n");
    printf("9. Add sample data\n");
    printf("0. Exit\n");
}

void handle_add(Database *db) {
    int id, credits;
    char name[MAX_NAME], major[MAX_MAJOR];
    float gpa;
    
    printf("Enter student ID: ");
    scanf("%d", &id);
    getchar();  // Consume newline
    
    printf("Enter name: ");
    fgets(name, MAX_NAME, stdin);
    name[strcspn(name, "\n")] = '\0';
    
    printf("Enter major: ");
    fgets(major, MAX_MAJOR, stdin);
    major[strcspn(major, "\n")] = '\0';
    
    printf("Enter GPA (0.0-4.0): ");
    scanf("%f", &gpa);
    
    printf("Enter credits: ");
    scanf("%d", &credits);
    
    if (db_add(db, id, name, major, gpa, credits) == 0) {
        printf("Student added successfully.\n");
    } else {
        printf("Failed to add student (ID may already exist).\n");
    }
}

void handle_search(Database *db) {
    int search_type;
    printf("Search by:\n");
    printf("1. Name (partial match)\n");
    printf("2. Major (exact match)\n");
    printf("3. Minimum GPA\n");
    printf("4. GPA range\n");
    printf("Enter choice: ");
    scanf("%d", &search_type);
    getchar();
    
    SearchResult *result = NULL;
    
    switch (search_type) {
        case 1: {
            char name[MAX_NAME];
            printf("Enter name to search: ");
            fgets(name, MAX_NAME, stdin);
            name[strcspn(name, "\n")] = '\0';
            result = db_search_by_name(db, name);
            break;
        }
        case 2: {
            char major[MAX_MAJOR];
            printf("Enter major: ");
            fgets(major, MAX_MAJOR, stdin);
            major[strcspn(major, "\n")] = '\0';
            result = db_search_by_major(db, major);
            break;
        }
        case 3: {
            float min_gpa;
            printf("Enter minimum GPA: ");
            scanf("%f", &min_gpa);
            result = db_search_by_min_gpa(db, min_gpa);
            break;
        }
        case 4: {
            float min_gpa, max_gpa;
            printf("Enter minimum GPA: ");
            scanf("%f", &min_gpa);
            printf("Enter maximum GPA: ");
            scanf("%f", &max_gpa);
            result = db_search_by_gpa_range(db, min_gpa, max_gpa);
            break;
        }
        default:
            printf("Invalid search type\n");
            return;
    }
    
    if (result != NULL) {
        search_print(result);
        search_destroy(result);
    }
}

void handle_update(Database *db) {
    int id;
    printf("Enter student ID to update: ");
    scanf("%d", &id);
    getchar();
    
    StudentRecord *record = db_get(db, id);
    if (record == NULL) {
        printf("Student not found.\n");
        return;
    }
    
    printf("Current record:\n");
    db_print_record(record);
    
    char name[MAX_NAME], major[MAX_MAJOR];
    float gpa;
    int credits;
    
    printf("\nEnter new name (or press Enter to keep): ");
    fgets(name, MAX_NAME, stdin);
    name[strcspn(name, "\n")] = '\0';
    
    printf("Enter new major (or press Enter to keep): ");
    fgets(major, MAX_MAJOR, stdin);
    major[strcspn(major, "\n")] = '\0';
    
    printf("Enter new GPA (-1 to keep): ");
    scanf("%f", &gpa);
    
    printf("Enter new credits (-1 to keep): ");
    scanf("%d", &credits);
    
    // Use existing values if not provided
    if (strlen(name) == 0) strcpy(name, record->name);
    if (strlen(major) == 0) strcpy(major, record->major);
    if (gpa < 0) gpa = record->gpa;
    if (credits < 0) credits = record->credits;
    
    if (db_update(db, id, name, major, gpa, credits) == 0) {
        printf("Student updated successfully.\n");
    } else {
        printf("Failed to update student.\n");
    }
}

void handle_delete(Database *db) {
    int id;
    printf("Enter student ID to delete: ");
    scanf("%d", &id);
    
    if (db_delete(db, id) == 0) {
        printf("Student deleted successfully.\n");
    } else {
        printf("Student not found.\n");
    }
}

void handle_sort(Database *db) {
    int sort_type;
    printf("Sort by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("3. GPA\n");
    printf("4. Credits\n");
    printf("Enter choice: ");
    scanf("%d", &sort_type);
    
    SortCriteria criteria;
    switch (sort_type) {
        case 1: criteria = SORT_BY_ID; break;
        case 2: criteria = SORT_BY_NAME; break;
        case 3: criteria = SORT_BY_GPA; break;
        case 4: criteria = SORT_BY_CREDITS; break;
        default:
            printf("Invalid sort type\n");
            return;
    }
    
    db_sort(db, criteria);
    printf("Database sorted.\n");
    db_print_all(db);
}

void add_sample_data(Database *db) {
    db_add(db, 1001, "Alice Smith", "Computer Science", 3.85, 90);
    db_add(db, 1002, "Bob Johnson", "Electrical Engineering", 3.45, 75);
    db_add(db, 1003, "Carol White", "Computer Science", 3.92, 60);
    db_add(db, 1004, "David Brown", "Mathematics", 3.20, 100);
    db_add(db, 1005, "Eve Davis", "Computer Science", 2.95, 45);
    db_add(db, 1006, "Frank Miller", "Physics", 3.55, 80);
    db_add(db, 1007, "Grace Lee", "Computer Science", 3.78, 95);
    db_add(db, 1008, "Henry Wilson", "Electrical Engineering", 2.80, 60);
    db_add(db, 1009, "Ivy Chen", "Mathematics", 3.95, 110);
    db_add(db, 1010, "Jack Taylor", "Physics", 3.10, 55);
    
    printf("Added 10 sample students.\n");
}

