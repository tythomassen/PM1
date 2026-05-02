/**
 * HW6: Mini Database System - Display Implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "search.h"
#include "display.h"

/* ============================================================
 * Display Functions
 * ============================================================ */

void db_print_record(const StudentRecord *record) {
    if (record == NULL) return;
    /* single-line format matches the example in the TODO comment */
    printf("ID: %d, Name: %s, Major: %s, GPA: %.2f, Credits: %d\n",
           record->id, record->name, record->major,
           (double)record->gpa, record->credits);
}

void db_print_all(const Database *db) {
    if (db == NULL) return;
    printf("=== Student Database (%d records) ===\n", db->count);
    if (db->count == 0) {
        printf("(empty)\n");
        return;
    }
    StudentRecord *cur = db->head;
    while (cur != NULL) {
        db_print_record(cur); /* reuse single-record formatter */
        cur = cur->next;
    }
}

void search_print(const SearchResult *result) {
    if (result == NULL) return;
    printf("=== Search Results (%d found) ===\n", result->count);
    if (result->count == 0) {
        printf("No matching records.\n");
        return;
    }
    for (int i = 0; i < result->count; i++) {
        db_print_record(result->results[i]); /* results[i] is a pointer into the live list */
    }
}

void db_print_summary(const Database *db) {
    if (db == NULL) return;
    printf("=== Database Summary ===\n");
    printf("Total students: %d\n", db->count);
    if (db->count == 0) return;

    /* --- pass 1: average GPA and grade-band distribution --- */
    double total_gpa    = 0.0;
    int grade_a         = 0; /* 3.5+      */
    int grade_b         = 0; /* 3.0-3.49  */
    int grade_c         = 0; /* 2.0-2.99  */
    int grade_below_c   = 0; /* < 2.0     */

    StudentRecord *cur = db->head;
    while (cur != NULL) {
        total_gpa += (double)cur->gpa;
        if      (cur->gpa >= 3.5f) grade_a++;
        else if (cur->gpa >= 3.0f) grade_b++;
        else if (cur->gpa >= 2.0f) grade_c++;
        else                       grade_below_c++;
        cur = cur->next;
    }

    printf("Average GPA: %.2f\n", total_gpa / (double)db->count);
    printf("GPA Distribution:\n");
    printf("  A (3.5+): %d students\n",       grade_a);
    printf("  B (3.0-3.49): %d students\n",   grade_b);
    printf("  C (2.0-2.99): %d students\n",   grade_c);
    printf("  Below C (<2.0): %d students\n", grade_below_c);

    /* --- pass 2: count students per major using parallel arrays --- */
    /* MAX_RECORDS bounds both arrays so they're always large enough */
    char majors[MAX_RECORDS][MAX_MAJOR];
    int  major_counts[MAX_RECORDS];
    int  major_num = 0; /* number of distinct majors seen so far */

    cur = db->head;
    while (cur != NULL) {
        int found = 0;
        for (int i = 0; i < major_num; i++) {
            if (strcmp(majors[i], cur->major) == 0) { /* already tracked this major */
                major_counts[i]++;
                found = 1;
                break;
            }
        }
        if (!found && major_num < MAX_RECORDS) {
            /* first time seeing this major — add a new slot */
            strncpy(majors[major_num], cur->major, MAX_MAJOR - 1);
            majors[major_num][MAX_MAJOR - 1] = '\0';
            major_counts[major_num] = 1;
            major_num++;
        }
        cur = cur->next;
    }

    printf("Students per major:\n");
    for (int i = 0; i < major_num; i++) {
        printf("  %s: %d\n", majors[i], major_counts[i]);
    }
}
