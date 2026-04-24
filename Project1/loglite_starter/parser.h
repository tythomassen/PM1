/**
 * parser.h - Log file parsing functions
 * 
 * This module handles reading and parsing log files.
 */

#ifndef PARSER_H
#define PARSER_H

#include "types.h"

/**
 * Load a log file into memory
 * 
 * @param filename  Path to the log file
 * @param store     Pointer to LogStore to populate
 * @return          0 on success, -1 on error (file not found, etc.)
 * 
 * On error, prints message to stderr and returns -1.
 * Malformed lines are skipped (warning printed to stderr).
 */
int load_log_file(const char *filename, LogStore *store);

/**
 * Parse a single log line into a LogEntry
 * 
 * @param line      The line to parse (null-terminated)
 * @param entry     Pointer to LogEntry to populate
 * @return          0 on success, -1 if line is malformed
 * 
 * Expected format: [YYYY-MM-DD HH:MM:SS] LEVEL Message
 */
int parse_log_line(const char *line, LogEntry *entry);

/**
 * Parse a log level string into a LogLevel enum
 * 
 * @param str   Level string (e.g., "ERROR", "INFO")
 * @return      LogLevel value, or -1 if invalid
 */
LogLevel parse_level(const char *str);

/**
 * Initialize a LogStore (allocate initial capacity)
 * 
 * @param store     Pointer to LogStore to initialize
 * @return          0 on success, -1 on allocation failure
 */
int init_log_store(LogStore *store);

/**
 * Free all memory used by a LogStore
 * 
 * @param store     Pointer to LogStore to free
 * 
 * This must free:
 *   - Each entry's message (if dynamically allocated)
 *   - The entries array itself
 */
void free_log_store(LogStore *store);

/**
 * Add an entry to a LogStore (grows array if needed)
 * 
 * @param store     Pointer to LogStore
 * @param entry     Pointer to LogEntry to add (will be copied)
 * @return          0 on success, -1 on allocation failure
 */
int add_entry(LogStore *store, const LogEntry *entry);

#endif // PARSER_H

