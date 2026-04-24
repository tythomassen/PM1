/**
 * main.c - LogLite entry point
 * 
 * LogLite: A log file query tool
 * Course: Programming Methodology I (Spring 2026)
 * 
 * Usage: ./loglite <logfile>
 */

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "parser.h"
#include "query.h"

int main(int argc, char *argv[]) {
    // TODO: Check command line arguments
    // - If argc != 2, print usage and exit with code 1
    // Usage: ./loglite <logfile>
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <logfile>\n", argv[0]);
        return 1;
    }
    
    // TODO: Create and initialize LogStore
    LogStore store;
    
    // TODO: Load the log file
    // - If loading fails, error message is already printed
    // - Exit with code 1
    
    if (load_log_file(argv[1], &store) != 0) {
        fprintf(stderr, "ERROR: Cannot open file %s\n", argv[1]);
        return 1;
    }
    
    // TODO: Run the query loop
    run_query_loop(&store);
    
    // TODO: Free all memory before exiting
    free_log_store(&store);
    
    return 0;
}

