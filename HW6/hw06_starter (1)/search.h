/**
 * HW6: Mini Database System - Search Header
 * DO NOT MODIFY THIS FILE
 */

#ifndef SEARCH_H
#define SEARCH_H

#include "database.h"

typedef struct {
    StudentRecord **results;
    int count;
    int capacity;
} SearchResult;

/* Search result management */
SearchResult* search_create(int capacity);
void search_destroy(SearchResult *result);

/* Search functions */
SearchResult* db_search_by_name(Database *db, const char *name);
SearchResult* db_search_by_major(Database *db, const char *major);
SearchResult* db_search_by_min_gpa(Database *db, float min_gpa);
SearchResult* db_search_by_gpa_range(Database *db, float min_gpa, float max_gpa);

#endif /* SEARCH_H */

