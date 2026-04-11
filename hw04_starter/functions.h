/**
 * HW4: Structures and File I/O - Function Prototypes
 * DO NOT MODIFY THIS FILE
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define MAX_NAME 50
#define MAX_STUDENTS 100
#define MAX_PHONE 20
#define MAX_EMAIL 50
#define MAX_CONTACTS 200

/* ============================================================
 * Problem 1: Student Records
 * ============================================================ */

typedef struct {
    int id;
    char name[MAX_NAME];
    double gpa;
    int credits;
} Student;

int student_init(Student *s, int id, const char *name, double gpa, int credits);
void student_print(const Student *s);
int student_compare_gpa(const Student *a, const Student *b);
Student* student_find_by_id(Student *students, int count, int id);
double students_average_gpa(const Student *students, int count);

/* ============================================================
 * Problem 2: CSV Parser
 * ============================================================ */

int parse_student_line(char *line, Student *s);
int read_students_csv(const char *filename, Student *students, int max_students);
int write_students_csv(const char *filename, const Student *students, 
                       int count, int include_header);
int filter_by_gpa(const Student *students, int count, 
                  Student *filtered, int max_filtered, double min_gpa);

/* ============================================================
 * Problem 3: Contact Book
 * ============================================================ */

typedef struct {
    char name[MAX_NAME];
    char phone[MAX_PHONE];
    char email[MAX_EMAIL];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int count;
    char filename[256];
} ContactBook;

void contactbook_init(ContactBook *book, const char *filename);
int contactbook_add(ContactBook *book, const char *name, 
                    const char *phone, const char *email);
int contactbook_remove(ContactBook *book, const char *name);
Contact* contactbook_search(ContactBook *book, const char *name);
int contactbook_save(const ContactBook *book);
int contactbook_load(ContactBook *book);
void contactbook_print(const ContactBook *book);

/* ============================================================
 * Problem 4: Log Analyzer
 * ============================================================ */

typedef enum {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_UNKNOWN
} LogLevel;

typedef struct {
    char timestamp[20];
    LogLevel level;
    char message[256];
} LogEntry;

typedef struct {
    int info_count;
    int warning_count;
    int error_count;
    int total_count;
} LogStats;

LogLevel parse_log_level(const char *level_str);
int parse_log_line(const char *line, LogEntry *entry);
int analyze_log_file(const char *filename, LogStats *stats);
int filter_logs_by_level(const char *input_file, const char *output_file, 
                         LogLevel level);
void print_log_stats(const LogStats *stats);

#endif /* FUNCTIONS_H */

