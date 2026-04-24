/**
 * types.h - Data type definitions for LogLite
 * 
 * This file defines the core data structures used throughout the project.
 * You may modify these structures or add new ones as needed.
 */

#ifndef TYPES_H
#define TYPES_H

/**
 * Log severity levels (in order of increasing severity)
 */
typedef enum {
    LEVEL_DEBUG,
    LEVEL_INFO,
    LEVEL_WARN,
    LEVEL_ERROR,
    LEVEL_FATAL,
    LEVEL_COUNT  // Number of levels (useful for arrays)
} LogLevel;

/**
 * A single log entry
 * 
 * TODO: Decide how to store the message:
 *   - Fixed-size array (simpler but wastes memory)
 *   - Dynamic allocation (more efficient but must free)
 */
typedef struct {
    // Date components
    int year;
    int month;
    int day;
    
    // Time components
    int hour;
    int minute;
    int second;
    
    // Severity level
    LogLevel level;
    
    // Message text
    // TODO: Choose one approach:
    // char message[1024];     // Option A: Fixed size
    char *message;             // Option B: Dynamically allocated (don't forget to free!)
} LogEntry;

/**
 * Collection of log entries
 * 
 * TODO: Choose your data structure:
 *   - Dynamic array (shown below)
 *   - Linked list (you'll need to define a Node struct)
 */
typedef struct {
    LogEntry *entries;    // Dynamic array of entries
    int count;            // Number of entries currently stored
    int capacity;         // Total capacity of the array
} LogStore;

/**
 * String representations of log levels (for parsing and printing)
 * 
 * Usage: level_names[LEVEL_ERROR] returns "ERROR"
 */
extern const char *level_names[];

#endif // TYPES_H

