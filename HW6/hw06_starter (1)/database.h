/**
 * HW6: Mini Database System - Database Header
 * DO NOT MODIFY THIS FILE
 */

#ifndef DATABASE_H
#define DATABASE_H

#define MAX_NAME 64
#define MAX_MAJOR 32
#define MAX_RECORDS 1000

typedef struct StudentRecord {
    int id;
    char name[MAX_NAME];
    char major[MAX_MAJOR];
    float gpa;
    int credits;
    struct StudentRecord *next;
} StudentRecord;

typedef struct {
    StudentRecord *head;
    int count;
    char filename[256];
    int modified;
} Database;

typedef enum {
    SORT_BY_ID,
    SORT_BY_NAME,
    SORT_BY_GPA,
    SORT_BY_CREDITS
} SortCriteria;

/* Database management */
Database* db_create(const char *filename);
void db_destroy(Database *db);
int db_save(Database *db);
int db_load(Database *db);
int db_count(const Database *db);

/* CRUD operations */
int db_add(Database *db, int id, const char *name,
           const char *major, float gpa, int credits);
StudentRecord* db_get(Database *db, int id);
int db_update(Database *db, int id, const char *name,
              const char *major, float gpa, int credits);
int db_delete(Database *db, int id);

/* Sorting */
void db_sort(Database *db, SortCriteria criteria);

#endif /* DATABASE_H */

