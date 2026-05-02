/**
 * HW6: Mini Database System - Database Implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

/* ============================================================
 * Database Management
 * ============================================================ */

Database* db_create(const char *filename) {
    Database *db = malloc(sizeof(Database)); /* allocate the database struct */
    if (db == NULL) return NULL;

    db->head = NULL;            /* empty linked list to start */
    db->count = 0;              /* no records yet */
    db->modified = 0;           /* not dirty */
    strncpy(db->filename, filename, sizeof(db->filename) - 1); /* copy filename for persistence */
    db->filename[sizeof(db->filename) - 1] = '\0'; /* guarantee null terminator */
    return db;
}

void db_destroy(Database *db) {
    if (db == NULL) return;
    StudentRecord *cur = db->head;
    while (cur != NULL) {
        StudentRecord *next = cur->next; /* save next before freeing current */
        free(cur);
        cur = next;
    }
    free(db); /* free the container after all nodes are gone */
}

int db_save(Database *db) {
    if (db == NULL) return -1;
    FILE *f = fopen(db->filename, "wb"); /* open for binary write */
    if (f == NULL) return -1;

    /* write total record count so loader knows how many records follow */
    if (fwrite(&db->count, sizeof(int), 1, f) != 1) {
        fclose(f);
        return -1;
    }

    StudentRecord *cur = db->head;
    while (cur != NULL) {
        /* write each field individually — no next pointer on disk */
        if (fwrite(&cur->id,      sizeof(int),   1,         f) != 1             ||
            fwrite(cur->name,     sizeof(char),  MAX_NAME,  f) != (size_t)MAX_NAME  ||
            fwrite(cur->major,    sizeof(char),  MAX_MAJOR, f) != (size_t)MAX_MAJOR ||
            fwrite(&cur->gpa,     sizeof(float), 1,         f) != 1             ||
            fwrite(&cur->credits, sizeof(int),   1,         f) != 1) {
            fclose(f);
            return -1;
        }
        cur = cur->next;
    }

    fclose(f);
    db->modified = 0; /* file is now in sync with memory */
    return 0;
}

int db_load(Database *db) {
    if (db == NULL) return -1;
    FILE *f = fopen(db->filename, "rb"); /* open for binary read */
    if (f == NULL) return -1;

    int count;
    if (fread(&count, sizeof(int), 1, f) != 1) { /* read how many records were saved */
        fclose(f);
        return -1;
    }

    int loaded = 0;
    for (int i = 0; i < count; i++) {
        int id, credits;
        char name[MAX_NAME], major[MAX_MAJOR];
        float gpa;

        /* read each field in the same order they were written */
        if (fread(&id,      sizeof(int),   1,         f) != 1             ||
            fread(name,     sizeof(char),  MAX_NAME,  f) != (size_t)MAX_NAME  ||
            fread(major,    sizeof(char),  MAX_MAJOR, f) != (size_t)MAX_MAJOR ||
            fread(&gpa,     sizeof(float), 1,         f) != 1             ||
            fread(&credits, sizeof(int),   1,         f) != 1) {
            break; /* partial read — stop and return what we got */
        }

        if (db_add(db, id, name, major, gpa, credits) == 0) {
            loaded++;
        }
    }

    fclose(f);
    db->modified = 0; /* loading from disk is not a modification */
    return loaded;
}

int db_count(const Database *db) {
    if (db == NULL) return 0;
    return db->count; /* maintained by add/delete so no traversal needed */
}


/* ============================================================
 * CRUD Operations
 * ============================================================ */

int db_add(Database *db, int id, const char *name,
           const char *major, float gpa, int credits) {
    if (db == NULL || name == NULL || major == NULL) return -1;

    /* reject duplicate IDs before allocating anything */
    StudentRecord *cur = db->head;
    while (cur != NULL) {
        if (cur->id == id) return -1; /* duplicate found */
        cur = cur->next;
    }

    StudentRecord *rec = malloc(sizeof(StudentRecord)); /* allocate new node */
    if (rec == NULL) return -1;

    rec->id = id;
    strncpy(rec->name,  name,  MAX_NAME  - 1); /* copy with length guard */
    rec->name[MAX_NAME - 1]   = '\0';
    strncpy(rec->major, major, MAX_MAJOR - 1);
    rec->major[MAX_MAJOR - 1] = '\0';
    rec->gpa     = gpa;
    rec->credits = credits;
    rec->next    = NULL;

    /* append to end so insertion order is preserved */
    if (db->head == NULL) {
        db->head = rec;
    } else {
        cur = db->head;
        while (cur->next != NULL) cur = cur->next;
        cur->next = rec;
    }

    db->count++;
    db->modified = 1; /* list has changed */
    return 0;
}

StudentRecord* db_get(Database *db, int id) {
    if (db == NULL) return NULL;
    StudentRecord *cur = db->head;
    while (cur != NULL) {
        if (cur->id == id) return cur; /* found — return pointer into list */
        cur = cur->next;
    }
    return NULL; /* not found */
}

int db_update(Database *db, int id, const char *name,
              const char *major, float gpa, int credits) {
    StudentRecord *rec = db_get(db, id); /* reuse get to locate the node */
    if (rec == NULL) return -1;

    if (name != NULL) {
        strncpy(rec->name, name, MAX_NAME - 1); /* overwrite name field */
        rec->name[MAX_NAME - 1] = '\0';
    }
    if (major != NULL) {
        strncpy(rec->major, major, MAX_MAJOR - 1); /* overwrite major field */
        rec->major[MAX_MAJOR - 1] = '\0';
    }
    rec->gpa     = gpa;     /* always overwrite numeric fields */
    rec->credits = credits;
    db->modified = 1;
    return 0;
}

int db_delete(Database *db, int id) {
    if (db == NULL || db->head == NULL) return -1;

    /* special case: target is the head node */
    if (db->head->id == id) {
        StudentRecord *to_free = db->head;
        db->head = db->head->next; /* advance head past the deleted node */
        free(to_free);
        db->count--;
        db->modified = 1;
        return 0;
    }

    /* general case: walk until predecessor of target */
    StudentRecord *prev = db->head;
    while (prev->next != NULL && prev->next->id != id) {
        prev = prev->next;
    }
    if (prev->next == NULL) return -1; /* id not found in list */

    StudentRecord *to_free = prev->next;
    prev->next = to_free->next; /* splice out the target node */
    free(to_free);
    db->count--;
    db->modified = 1;
    return 0;
}


/* ============================================================
 * Sorting
 * ============================================================ */

/* Returns negative if a < b, 0 if equal, positive if a > b */
static int compare_records(StudentRecord *a, StudentRecord *b, SortCriteria criteria) {
    switch (criteria) {
        case SORT_BY_ID:
            /* ternary avoids potential int overflow from subtraction */
            return (a->id > b->id) - (a->id < b->id);
        case SORT_BY_NAME:
            return strcmp(a->name, b->name); /* lexicographic order */
        case SORT_BY_GPA:
            /* float subtraction is unsafe for comparison — use explicit checks */
            if (a->gpa < b->gpa) return -1;
            if (a->gpa > b->gpa) return  1;
            return 0;
        case SORT_BY_CREDITS:
            return (a->credits > b->credits) - (a->credits < b->credits);
        default:
            return 0;
    }
}

void db_sort(Database *db, SortCriteria criteria) {
    if (db == NULL || db->head == NULL || db->head->next == NULL) return;

    StudentRecord *sorted = NULL; /* head of the growing sorted list */
    StudentRecord *cur    = db->head;

    while (cur != NULL) {
        StudentRecord *next = cur->next; /* save before we rewire cur->next */

        if (sorted == NULL || compare_records(cur, sorted, criteria) <= 0) {
            /* cur belongs before the current sorted head */
            cur->next = sorted;
            sorted = cur;
        } else {
            /* walk sorted list to find the insertion point */
            StudentRecord *s = sorted;
            while (s->next != NULL && compare_records(cur, s->next, criteria) > 0) {
                s = s->next;
            }
            cur->next = s->next; /* link cur in between s and s->next */
            s->next   = cur;
        }

        cur = next; /* advance through the original unsorted list */
    }

    db->head = sorted; /* replace list head with sorted list */
}
