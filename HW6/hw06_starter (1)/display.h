/**
 * HW6: Mini Database System - Display Header
 * DO NOT MODIFY THIS FILE
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "database.h"
#include "search.h"

/* Display functions */
void db_print_record(const StudentRecord *record);
void db_print_all(const Database *db);
void search_print(const SearchResult *result);
void db_print_summary(const Database *db);

#endif /* DISPLAY_H */

