/**
 * parser.c - Log file parsing implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "types.h"

const char *level_names[] = {
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "FATAL"
};

#define INITIAL_CAPACITY 16
#define MAX_LINE_LENGTH 1024

int init_log_store(LogStore *store) {
    store->entries = malloc(INITIAL_CAPACITY * sizeof(LogEntry));  //memory allocation to stare entries at their size
    if (store->entries == NULL) return -1;  // NULL check
    store->count = 0;  // Initcount 
    store->capacity = INITIAL_CAPACITY;  //Init capacity
    return 0;
}

void free_log_store(LogStore *store) {
    for (int i = 0; i < store->count; i++) { //Counter from 0 - Store Count to free storage
        free(store->entries[i].message);
    }
    free(store->entries); // free entires
    store->entries = NULL;  // Dangling pointer Fix
    store->count = 0; // No garabge in mem spot
    store->capacity = 0; // No garabge in mem spot
}

int add_entry(LogStore *store, const LogEntry *entry) {
    if (store->count == store->capacity) { // Run this fuction if Capacity if Full
        int new_capacity = store->capacity * 2; // Double capacity
        LogEntry *new_entries = realloc(store->entries, new_capacity * sizeof(LogEntry));
        if (new_entries == NULL) return -1; // NULL check, -1 if fail
        store->entries = new_entries; //Move back in to the Bigger House
        store->capacity = new_capacity; //Move back in to the Bigger House
    }
    store->entries[store->count] = *entry; 
    store->count++;
    return 0;  //SUccess
}

LogLevel parse_level(const char *str) {
    for (int i = 0; i < LEVEL_COUNT; i++) { //Count though error levels
        if (strcmp(str, level_names[i]) == 0) return (LogLevel)i; //Find error that fits 
    }
    return (LogLevel)-1; 
}

int parse_log_line(const char *line, LogEntry *entry) {
    int year, month, day, hour, minute, second;
    char level_str[16];
    char message_buf[MAX_LINE_LENGTH];

    /* Format: [YYYY-MM-DD HH:MM:SS] LEVEL Message */
    int matched = sscanf(line, "[%d-%d-%d %d:%d:%d] %15s %1023[^\n]",
                         &year, &month, &day,
                         &hour, &minute, &second,
                         level_str, message_buf);

    if (matched != 8) return -1;
    if (line[0] != '[') return -1;

    LogLevel level = parse_level(level_str);
    if ((int)level == -1) return -1;

    entry->year = year;
    entry->month = month;
    entry->day = day;
    entry->hour = hour;
    entry->minute = minute;
    entry->second = second;
    entry->level = level;
    entry->message = malloc(strlen(message_buf) + 1);
    if (entry->message == NULL) return -1;
    strcpy(entry->message, message_buf);

    return 0;
}

int load_log_file(const char *filename, LogStore *store) {
    if (init_log_store(store) != 0) return -1;

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) return -1;

    char line[MAX_LINE_LENGTH];
    int line_num = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        line_num++;

        /* Strip trailing newline / carriage return */
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') { line[--len] = '\0'; }
        if (len > 0 && line[len - 1] == '\r') { line[--len] = '\0'; }

        LogEntry entry;
        if (parse_log_line(line, &entry) != 0) {
            fprintf(stderr, "WARNING: Skipping malformed line %d\n", line_num);
            continue;
        }

        if (add_entry(store, &entry) != 0) {
            free(entry.message);
            fclose(fp);
            return -1;
        }
    }

    fclose(fp);
    return 0;
}
