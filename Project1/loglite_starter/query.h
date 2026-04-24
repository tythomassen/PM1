/**
 * query.h - Query processing functions
 * 
 * This module handles parsing and executing queries on the log store.
 */

#ifndef QUERY_H
#define QUERY_H

#include "types.h"

/**
 * Run the interactive query loop
 * 
 * @param store     Pointer to loaded LogStore
 * 
 * Reads commands from stdin until QUIT or EOF.
 * Results are printed to stdout.
 * Errors are printed to stderr.
 */
void run_query_loop(LogStore *store);

/**
 * Execute a single query command
 * 
 * @param store     Pointer to LogStore
 * @param command   The command string to execute
 * @return          0 to continue, 1 to quit
 */
int execute_command(LogStore *store, const char *command);

/**
 * Filter entries by log level
 * 
 * @param store     Pointer to LogStore
 * @param level     LogLevel to filter by
 * 
 * Prints matching entries to stdout.
 */
void filter_by_level(LogStore *store, LogLevel level);

/**
 * Filter entries by date range (inclusive)
 * 
 * @param store       Pointer to LogStore
 * @param start_year  Start date year
 * @param start_month Start date month
 * @param start_day   Start date day
 * @param end_year    End date year
 * @param end_month   End date month
 * @param end_day     End date day
 * 
 * Prints matching entries to stdout.
 */
void filter_by_date(LogStore *store, 
                    int start_year, int start_month, int start_day,
                    int end_year, int end_month, int end_day);

/**
 * Search for entries containing a keyword
 * 
 * @param store     Pointer to LogStore
 * @param keyword   Substring to search for (case-sensitive)
 * 
 * Prints matching entries to stdout.
 */
void search_keyword(LogStore *store, const char *keyword);

/**
 * Count entries by level
 * 
 * @param store     Pointer to LogStore
 * @param level     LogLevel to count
 * @return          Number of matching entries
 */
int count_by_level(LogStore *store, LogLevel level);

/**
 * Print statistics summary
 * 
 * @param store     Pointer to LogStore
 * 
 * Prints to stdout:
 *   Total: N
 *   DEBUG: X
 *   INFO: X
 *   WARN: X
 *   ERROR: X
 *   FATAL: X
 */
void print_stats(LogStore *store);

/**
 * Print a single log entry
 * 
 * @param entry     Pointer to LogEntry to print
 * 
 * Format: [YYYY-MM-DD HH:MM:SS] LEVEL Message
 */
void print_entry(const LogEntry *entry);

#endif // QUERY_H

