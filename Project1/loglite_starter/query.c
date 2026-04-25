/**
 * query.c - Query processing implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "query.h"
#include "parser.h"
#include "types.h"

#define MAX_COMMAND_LENGTH 1024 // Headers

void print_entry(const LogEntry *entry) {
    printf("[%04d-%02d-%02d %02d:%02d:%02d] %s %s\n", // Formating for printing 
           entry->year, entry->month, entry->day,
           entry->hour, entry->minute, entry->second,
           level_names[entry->level],
           entry->message);
}

void filter_by_level(LogStore *store, LogLevel level) {
    for (int i = 0; i < store->count; i++) { // Count though the store
        if (store->entries[i].level == level) {
            print_entry(&store->entries[i]);  // Printing entires downthe index
        }
    }
}

void filter_by_date(LogStore *store,
                    int start_year, int start_month, int start_day,
                    int end_year, int end_month, int end_day) {
    int start = start_year * 10000 + start_month * 100 + start_day; //Made start date single number for comp
    int end   = end_year   * 10000 + end_month   * 100 + end_day;

    for (int i = 0; i < store->count; i++) { // Loop though entries in store
        LogEntry *e = &store->entries[i];  // Grab pointer to current entry
        int date = e->year * 10000 + e->month * 100 + e->day; // Convert to int
        if (date >= start && date <= end) { // Check against edge/range
            print_entry(e); // if so print it
        }
    }
}

void search_keyword(LogStore *store, const char *keyword) { //Print key word logs
    for (int i = 0; i < store->count; i++) { // loop though entries int he store
        if (strstr(store->entries[i].message, keyword) != NULL) {  // Look for key word
            print_entry(&store->entries[i]); // Found? Print it
        }
    }
}

int count_by_level(LogStore *store, LogLevel level) {  // Entries that match log level
    int count = 0;
    for (int i = 0; i < store->count; i++) { // loop though
        if (store->entries[i].level == level) count++;
    }
    return count; // Final count
}

void print_stats(LogStore *store) { // Entires for each log level
    printf("Total: %d\n", store->count); //Total entries
    printf("DEBUG: %d\n", count_by_level(store, LEVEL_DEBUG));
    printf("INFO: %d\n",  count_by_level(store, LEVEL_INFO));
    printf("WARN: %d\n",  count_by_level(store, LEVEL_WARN));
    printf("ERROR: %d\n", count_by_level(store, LEVEL_ERROR));
    printf("FATAL: %d\n", count_by_level(store, LEVEL_FATAL));
}

int execute_command(LogStore *store, const char *command) {
    char cmd[32]; // Buffer for overflow
    if (sscanf(command, "%31s", cmd) != 1) {
        return 0;
    }

    if (strcmp(cmd, "QUIT") == 0) { //Read QUIT? stop
        return 1;
    }

    if (strcmp(cmd, "STATS") == 0) {
        print_stats(store);
        return 0;
    }

    if (strcmp(cmd, "SEARCH") == 0) { // If SEach extract key word
        char keyword[MAX_COMMAND_LENGTH]; // Buffer
        if (sscanf(command, "SEARCH %1023[^\n]", keyword) != 1) {
            fprintf(stderr, "ERROR: Unknown command\n");
            return 0;
        }
        search_keyword(store, keyword); // Run keyword search
        return 0;
    }

    if (strcmp(cmd, "COUNT") == 0) {
        char sub[16]; // Buffer
        if (sscanf(command, "%*s %15s", sub) != 1) { // Sca for sub command
            fprintf(stderr, "ERROR: Unknown command\n");
            return 0;
        }
        if (strcmp(sub, "all") == 0) { // Cases
            printf("%d\n", store->count);
        } else if (strcmp(sub, "level") == 0) {
            char level_str[16];
            if (sscanf(command, "%*s %*s %15s", level_str) != 1) {
                fprintf(stderr, "ERROR: Unknown command\n");
                return 0;
            }
            LogLevel level = parse_level(level_str);
            if ((int)level == -1) {
                fprintf(stderr, "ERROR: Unknown command\n");
                return 0;
            }
            printf("%d\n", count_by_level(store, level));
        } else {
            fprintf(stderr, "ERROR: Unknown command\n");
        }
        return 0;
    }
// Command code
    if (strcmp(cmd, "FILTER") == 0) {
        char sub[16];
        if (sscanf(command, "%*s %15s", sub) != 1) {
            fprintf(stderr, "ERROR: Unknown command\n");
            return 0;
        }
        if (strcmp(sub, "level") == 0) {
            char level_str[16];
            if (sscanf(command, "%*s %*s %15s", level_str) != 1) {
                fprintf(stderr, "ERROR: Unknown command\n");
                return 0;
            }
            LogLevel level = parse_level(level_str);
            if ((int)level == -1) {
                fprintf(stderr, "ERROR: Unknown command\n");
                return 0;
            }
            filter_by_level(store, level);
        } else if (strcmp(sub, "date") == 0) {
            char start[16], end[16];
            if (sscanf(command, "%*s %*s %15s %15s", start, end) != 2) {
                fprintf(stderr, "ERROR: Unknown command\n");
                return 0;
            }
            int sy, sm, sd, ey, em, ed; // Creating vars for ints
            if (sscanf(start, "%d-%d-%d", &sy, &sm, &sd) != 3 || // formating 3 feilds
                sscanf(end,   "%d-%d-%d", &ey, &em, &ed) != 3) {
                fprintf(stderr, "ERROR: Unknown command\n");
                return 0;
            }
            filter_by_date(store, sy, sm, sd, ey, em, ed);
        } else {
            fprintf(stderr, "ERROR: Unknown command\n");
        }
        return 0;
    }

    fprintf(stderr, "ERROR: Unknown command\n");
    return 0;
}

void run_query_loop(LogStore *store) {
    char line[MAX_COMMAND_LENGTH];

    while (fgets(line, sizeof(line), stdin) != NULL) {
        size_t len = strlen(line);  //Parseing
        if (len > 0 && line[len - 1] == '\n') { line[--len] = '\0'; }
        if (len > 0 && line[len - 1] == '\r') { line[--len] = '\0'; }

        if (execute_command(store, line)) {
            break;
        }
    }
}
