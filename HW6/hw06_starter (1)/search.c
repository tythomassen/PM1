/**
 * HW6: Mini Database System - Search Implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "search.h"

/* ============================================================
 * Search Result Management
 * ============================================================ */

SearchResult* search_create(int capacity) {
    if (capacity <= 0) capacity = 1; /* guard against zero-size malloc */

    SearchResult *result = malloc(sizeof(SearchResult)); /* allocate container */
    if (result == NULL) return NULL;

    result->results = malloc(sizeof(StudentRecord *) * (size_t)capacity); /* allocate pointer array */
    if (result->results == NULL) {
        free(result);
        return NULL;
    }

    result->count    = 0;
    result->capacity = capacity;
    return result;
}

void search_destroy(SearchResult *result) {
    if (result == NULL) return;
    free(result->results); /* free the pointer array — NOT the records it points to */
    free(result);
}

/* Appends a record pointer to the results array */
static int search_add(SearchResult *result, StudentRecord *record) {
    if (result == NULL || result->count >= result->capacity) return -1; /* array full */
    result->results[result->count] = record; /* store pointer, not a copy */
    result->count++;
    return 0;
}


/* ============================================================
 * Search Functions
 * ============================================================ */

SearchResult* db_search_by_name(Database *db, const char *name) {
    if (db == NULL || name == NULL) return NULL;

    /* capacity = db->count is the worst-case number of matches */
    SearchResult *result = search_create(db->count > 0 ? db->count : 1);
    if (result == NULL) return NULL;

    StudentRecord *cur = db->head;
    while (cur != NULL) {
        if (strstr(cur->name, name) != NULL) { /* strstr does partial/substring match */
            search_add(result, cur);
        }
        cur = cur->next;
    }
    return result;
}

SearchResult* db_search_by_major(Database *db, const char *major) {
    if (db == NULL || major == NULL) return NULL;

    SearchResult *result = search_create(db->count > 0 ? db->count : 1);
    if (result == NULL) return NULL;

    StudentRecord *cur = db->head;
    while (cur != NULL) {
        if (strcmp(cur->major, major) == 0) { /* strcmp == 0 means exact match */
            search_add(result, cur);
        }
        cur = cur->next;
    }
    return result;
}

SearchResult* db_search_by_min_gpa(Database *db, float min_gpa) {
    if (db == NULL) return NULL;

    SearchResult *result = search_create(db->count > 0 ? db->count : 1);
    if (result == NULL) return NULL;

    StudentRecord *cur = db->head;
    while (cur != NULL) {
        if (cur->gpa >= min_gpa) { /* include records at exactly the minimum */
            search_add(result, cur);
        }
        cur = cur->next;
    }
    return result;
}

SearchResult* db_search_by_gpa_range(Database *db, float min_gpa, float max_gpa) {
    if (db == NULL) return NULL;

    SearchResult *result = search_create(db->count > 0 ? db->count : 1);
    if (result == NULL) return NULL;

    StudentRecord *cur = db->head;
    while (cur != NULL) {
        if (cur->gpa >= min_gpa && cur->gpa <= max_gpa) { /* inclusive on both ends */
            search_add(result, cur);
        }
        cur = cur->next;
    }
    return result;
}
