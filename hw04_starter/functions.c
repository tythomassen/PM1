/**
 * HW4: Structures and File I/O - Function Implementations
 * 
 * Complete all TODO sections below.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

/* ============================================================
 * Problem 1: Student Records
 * ============================================================ */

int student_init(Student *s, int id, const char *name, double gpa, int credits) {
    /* NULL pointer check */
    if (!s || !name) return -1;

    /* Validate GPA is in range [0.0, 4.0] */
    if (gpa < 0.0 || gpa > 4.0) return -1;

    /* Validate credits are non-negative */
    if (credits < 0) return -1;

    s->id      = id;
    s->gpa     = gpa;
    s->credits = credits;

    /* strncpy won't null-terminate if src >= MAX_NAME chars, so force it */
    strncpy(s->name, name, MAX_NAME - 1);
    s->name[MAX_NAME - 1] = '\0';
    return 0;
}

void student_print(const Student *s) {
    // TODO: Print student in format:
    // "ID: 12345, Name: John Doe, GPA: 3.75, Credits: 60"
    // Handle NULL pointer gracefully
    if (!s) return;  // If S is not 0 do all this. 
    printf("ID: %d, Name: %s, GPA: %.2f, Credits: %d\n",
           s->id, s->name, s->gpa, s->credits);
}

int student_compare_gpa(const Student *a, const Student *b) {
    // TODO: Compare GPAs for sorting
    // Return negative if a->gpa < b->gpa
    // Return 0 if equal
    // Return positive if a->gpa > b->gpa
    // Handle NULL pointers
    if (!a || !b) return 0;
    if (a->gpa < b->gpa) return -1;
    if (a->gpa > b->gpa) return  1;
    return 0;  // Replace
}

Student* student_find_by_id(Student *students, int count, int id) {
    // TODO: Search array for student with matching ID
    // Return pointer to found student, or NULL if not found
    if (!students || count <= 0) return NULL;
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) return &students[i];
    }    
    return NULL;  // Replace
}

double students_average_gpa(const Student *students, int count) {
    // TODO: Calculate average GPA of all students
    // Return 0.0 if count is 0 or students is NULL
    if (!students || count <= 0) return 0.0;
    double total = 0.0;
    for (int i = 0; i < count; i++) total += students[i].gpa;
    return total / count;
}


/* ============================================================
 * Problem 2: CSV Parser
 * ============================================================ */

int parse_student_line(char *line, Student *s) {
    // TODO: Parse CSV line: "12345,John Doe,3.75,60"
    // Use strtok() or sscanf() to extract fields
    // Return 0 on success, -1 on parse error
    //
    // Hint: strtok modifies the string, so line must be modifiable
    // Hint: Use sscanf for numeric conversion: sscanf(token, "%d", &value)
    if (!line || !s) return -1;

    char *id_tok      = strtok(line, ",");
    char *name_tok    = strtok(NULL, ",");
    char *gpa_tok     = strtok(NULL, ",");
    char *credits_tok = strtok(NULL, ",\n\r");

    if (!id_tok || !name_tok || !gpa_tok || !credits_tok) return -1;

    int    id, credits;
    double gpa;
    if (sscanf(id_tok,      "%d",  &id)      != 1) return -1;
    if (sscanf(gpa_tok,     "%lf", &gpa)     != 1) return -1;
    if (sscanf(credits_tok, "%d",  &credits) != 1) return -1;

    return student_init(s, id, name_tok, gpa, credits);   
}

int read_students_csv(const char *filename, Student *students, int max_students) {
    // TODO: Read CSV file into students array
    // - Skip header line (first line)
    // - Parse each subsequent line
    // - Stop at max_students or EOF
    // Return number read, or -1 on file error
    //
    // Hint: Use fgets() to read lines, then parse_student_line()
    if (!filename || !students || max_students <= 0) return -1;

    FILE *f = fopen(filename, "r");
    if (!f) return -1;

    char line[256];
    /* skip header */
    if (!fgets(line, sizeof(line), f)) { fclose(f); return 0; }

    int count = 0;
    while (count < max_students && fgets(line, sizeof(line), f)) {
        if (parse_student_line(line, &students[count]) == 0)
            count++;
    }

    fclose(f);
    return count;
}

int write_students_csv(const char *filename, const Student *students, 
                       int count, int include_header) {
    // TODO: Write students to CSV file
    // - If include_header, write "id,name,gpa,credits\n" first
    // - Write each student as CSV line
    // Return 0 on success, -1 on error
    if (!filename || !students) return -1;

    FILE *f = fopen(filename, "w");
    if (!f) return -1;

    if (include_header)
        fprintf(f, "id,name,gpa,credits\n");

    for (int i = 0; i < count; i++)
        fprintf(f, "%d,%s,%.2f,%d\n",
                students[i].id, students[i].name,
                students[i].gpa, students[i].credits);

    fclose(f);
    return 0;
}

int filter_by_gpa(const Student *students, int count, 
                  Student *filtered, int max_filtered, double min_gpa) {
    // TODO: Copy students with gpa >= min_gpa to filtered array
    // Return number of students that passed filter
    if (!students || !filtered) return 0;

    int n = 0;
    for (int i = 0; i < count && n < max_filtered; i++) {
        if (students[i].gpa >= min_gpa)
            filtered[n++] = students[i];
    }
    return n;
}


/* ============================================================
 * Problem 3: Contact Book
 * ============================================================ */

void contactbook_init(ContactBook *book, const char *filename) {
    // TODO: Initialize contact book
    // - Set count to 0
    // - Copy filename for persistence
    if (!book) return;
    book->count = 0;
    if (filename) {
        strncpy(book->filename, filename, 255);
        book->filename[255] = '\0';
    } else {
        book->filename[0] = '\0';
    }
}

int contactbook_add(ContactBook *book, const char *name, 
                    const char *phone, const char *email) {
    // TODO: Add contact to book
    // - Check if full (count >= MAX_CONTACTS)
    // - Copy name, phone, email to new contact
    // - Increment count
    // Return 0 on success, -1 if full or error
    if (!book || !name || !phone || !email) return -1;
    if (book->count >= MAX_CONTACTS) return -1;

    Contact *c = &book->contacts[book->count];
    strncpy(c->name,  name,  MAX_NAME  - 1); c->name[MAX_NAME   - 1] = '\0';
    strncpy(c->phone, phone, MAX_PHONE - 1); c->phone[MAX_PHONE - 1] = '\0';
    strncpy(c->email, email, MAX_EMAIL - 1); c->email[MAX_EMAIL - 1] = '\0';
    book->count++;
    return 0;
}

int contactbook_remove(ContactBook *book, const char *name) {
    // TODO: Remove contact by name (first match)
    // - Find contact with matching name (use strcmp)
    // - Shift remaining contacts down to fill gap
    // - Decrement count
    // Return 0 on success, -1 if not found
    if (!book || !name) return -1;

    for (int i = 0; i < book->count; i++) {
        if (strcmp(book->contacts[i].name, name) == 0) {
            /* shift remaining contacts down to fill the gap */
            for (int j = i; j < book->count - 1; j++)
                book->contacts[j] = book->contacts[j + 1];
            book->count--;
            return 0;
        }
    }
    return -1;
}

Contact* contactbook_search(ContactBook *book, const char *name) {
    // TODO: Search for contact by name (partial match)
    // Use strstr() for partial matching
    // Return pointer to contact, or NULL if not found
    if (!book || !name) return NULL;

    for (int i = 0; i < book->count; i++) {
        if (strstr(book->contacts[i].name, name))
            return &book->contacts[i];
    }
    return NULL;
}

int contactbook_save(const ContactBook *book) {
    // TODO: Save contacts to file (binary format)
    // - Write count first
    // - Write all contacts
    // Use fwrite() for binary output
    // Return 0 on success, -1 on error
    if (!book) return -1;

    FILE *f = fopen(book->filename, "wb");
    if (!f) return -1;

    fwrite(&book->count,    sizeof(int),     1,           f);
    fwrite(book->contacts,  sizeof(Contact), book->count, f);
    fclose(f);
    return 0;
}

int contactbook_load(ContactBook *book) {
    // TODO: Load contacts from file (binary format)
    // - Read count first
    // - Read all contacts
    // Use fread() for binary input
    // Return number loaded, or -1 on error
    if (!book) return -1;

    FILE *f = fopen(book->filename, "rb");
    if (!f) return -1;

    int count;
    if (fread(&count, sizeof(int), 1, f) != 1) { fclose(f); return -1; }
    if (count < 0 || count > MAX_CONTACTS)      { fclose(f); return -1; }

    int n = (int)fread(book->contacts, sizeof(Contact), count, f);
    book->count = n;
    fclose(f);
    return n;
}

void contactbook_print(const ContactBook *book) {
    // TODO: Print all contacts
    // Format: "Name: Alice, Phone: 555-1234, Email: alice@email.com"
    if (!book) return;
    for (int i = 0; i < book->count; i++)
        printf("Name: %s, Phone: %s, Email: %s\n",
               book->contacts[i].name,
               book->contacts[i].phone,
               book->contacts[i].email);
}


/* ============================================================
 * Problem 4: Log Analyzer
 * ============================================================ */

LogLevel parse_log_level(const char *level_str) {
    // TODO: Parse log level string to enum
    // "INFO" -> LOG_INFO
    // "WARNING" -> LOG_WARNING
    // "ERROR" -> LOG_ERROR
    // Otherwise -> LOG_UNKNOWN
    if (!level_str)                        return LOG_UNKNOWN;
    if (strcmp(level_str, "INFO")    == 0) return LOG_INFO;
    if (strcmp(level_str, "WARNING") == 0) return LOG_WARNING;
    if (strcmp(level_str, "ERROR")   == 0) return LOG_ERROR;
    return LOG_UNKNOWN;
}

int parse_log_line(const char *line, LogEntry *entry) {
    // TODO: Parse log line format:
    // "[2024-01-15 10:30:45] INFO: User login successful"
    //
    // Extract:
    // - timestamp: "2024-01-15 10:30:45"
    // - level: "INFO" -> LOG_INFO
    // - message: "User login successful"
    //
    // Return 0 on success, -1 on parse error
    // Hint: Use sscanf with format like "[%19[^]]] %[^:]: %[^\n]"
    if (!line || !entry) return -1;

    /* Format: "[2024-01-15 10:30:45] INFO: User login successful" */
    char level_str[16];
    if (sscanf(line, "[%19[^]]] %15[^:]: %255[^\n]",
               entry->timestamp, level_str, entry->message) != 3)
        return -1;

    entry->level = parse_log_level(level_str);
    return 0;
}

int analyze_log_file(const char *filename, LogStats *stats) {
    // TODO: Read log file and count entries by level
    // - Initialize stats to zeros
    // - Parse each line and increment appropriate counter
    // Return 0 on success, -1 on file error
    if (!filename || !stats) return -1;

    FILE *f = fopen(filename, "r");
    if (!f) return -1;

    memset(stats, 0, sizeof(LogStats));

    char line[512];
    LogEntry entry;
    while (fgets(line, sizeof(line), f)) {
        if (parse_log_line(line, &entry) != 0) continue;
        switch (entry.level) {
            case LOG_INFO:    stats->info_count++;    break;
            case LOG_WARNING: stats->warning_count++; break;
            case LOG_ERROR:   stats->error_count++;   break;
            default: break;
        }
        stats->total_count++;
    }

    fclose(f);
    return 0;
}

int filter_logs_by_level(const char *input_file, const char *output_file, 
                         LogLevel level) {
    // TODO: Read input log file, write matching entries to output
    // Return number of entries written, or -1 on error
    if (!input_file || !output_file) return -1;

    FILE *in = fopen(input_file, "r");
    if (!in) return -1;

    FILE *out = fopen(output_file, "w");
    if (!out) { fclose(in); return -1; }

    char line[512];
    LogEntry entry;
    int written = 0;
    while (fgets(line, sizeof(line), in)) {
        if (parse_log_line(line, &entry) == 0 && entry.level == level) {
            fputs(line, out);
            written++;
        }
    }

    fclose(in);
    fclose(out);
    return written;
}

void print_log_stats(const LogStats *stats) {
    // TODO: Print formatted statistics
    // "Log Statistics:"
    // "  INFO:    %d"
    // "  WARNING: %d"
    // "  ERROR:   %d"
    // "  TOTAL:   %d"
    if (!stats) return;
    printf("Log Statistics:\n");
    printf("  INFO:    %d\n", stats->info_count);
    printf("  WARNING: %d\n", stats->warning_count);
    printf("  ERROR:   %d\n", stats->error_count);
    printf("  TOTAL:   %d\n", stats->total_count);
}

