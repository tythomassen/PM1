#include <stdio.h>   // printf, scanf, fopen, fclose, fscanf, fprintf
#include <stdlib.h>  // malloc, realloc, free, exit

// forward declarations so main can call these before they are defined below
void part_a(void);
void part_b(void);
void part_c(void);

// ── Main: Menu Loop ───────────────────────────────────────────────────────────

int main(void) {
    int choice;  // stores the menu option chosen by the user

    do {
        // print the menu each iteration
        printf("\n=== Comprehensive C Review ===\n");
        printf("1. Memory Management\n");
        printf("2. Data Structures\n");
        printf("3. Integration Exercise\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);                  // read the user's menu selection

        switch (choice) {
            case 1:                            // user chose Memory Management
                part_a();
                break;
            case 2:                            // user chose Data Structures
                part_b();
                break;
            case 3:                            // user chose Integration Exercise
                part_c();
                break;
            case 0:                            // user chose to exit
                printf("Exiting.\n");
                break;
            default:                           // user entered an unrecognized option
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);                     // keep looping until the user selects 0

    return 0;  // return success to the OS
}

// ── Part A: Memory Management ────────────────────────────────────────────────

void part_a(void) {
    int rows = 3;   // number of rows in the 2D matrix
    int cols = 4;   // number of columns in the 2D matrix

    // allocate the array of row pointers (one pointer per row)
    int **matrix = malloc(rows * sizeof(int *));
    if (matrix == NULL) {                          // check that malloc succeeded
        printf("Failed to allocate row pointers\n");
        return;                                    // abort if allocation failed
    }

    // allocate each individual row
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));    // allocate one row of ints
        if (matrix[i] == NULL) {                   // check that row malloc succeeded
            printf("Failed to allocate row %d\n", i);
            for (int k = 0; k < i; k++) {          // free all rows allocated so far
                free(matrix[k]);
            }
            free(matrix);                          // free the row pointer array
            return;                                // abort if any row failed
        }
    }

    // initialize the matrix with sequential values (row * cols + col + 1)
    for (int i = 0; i < rows; i++) {               // iterate over each row
        for (int j = 0; j < cols; j++) {           // iterate over each column
            matrix[i][j] = i * cols + j + 1;       // assign value 1..rows*cols
        }
    }

    printf("\n--- Part A: Memory Management ---\n");  // section header
    printf("Dynamic %dx%d matrix:\n", rows, cols);    // label the matrix size

    // print the matrix contents row by row
    for (int i = 0; i < rows; i++) {               // for each row
        for (int j = 0; j < cols; j++) {           // for each column
            printf("%4d", matrix[i][j]);           // print value right-aligned in 4 chars
        }
        printf("\n");                              // newline after each row
    }

    // free memory in reverse order: rows first, then the pointer array
    for (int i = 0; i < rows; i++) {               // free each row's data
        free(matrix[i]);
    }
    free(matrix);                                  // free the row pointer array last

    printf("Memory freed successfully\n");         // confirm cleanup completed
}

// ── Part B: Data Structures (LIFO) ───────────────────────────────────────────

void part_b(void) {
    int n;  // number of elements the user wants to enter

    printf("\n--- Part B: Data Structures ---\n");     // section header
    printf("Enter number of elements: ");
    scanf("%d", &n);                                   // read element count from user

    if (n <= 0) {                                      // reject non-positive counts
        printf("Number of elements must be positive\n");
        return;
    }

    int *arr = malloc(n * sizeof(int));                // allocate array of n ints
    if (arr == NULL) {                                 // check that malloc succeeded
        printf("Failed to allocate array\n");
        return;
    }

    printf("Enter %d values:\n", n);                   // prompt user for input
    for (int i = 0; i < n; i++) {                      // read each value in order
        scanf("%d", &arr[i]);                          // store value at index i
    }

    printf("LIFO order: ");                            // label the reversed output
    for (int i = n - 1; i >= 0; i--) {                // print from last index down to 0
        printf("%d ", arr[i]);                         // print element at index i
    }
    printf("\n");                                      // newline after all elements

    // compute statistics over the array
    long sum = 0;                                      // accumulator for the sum
    int min = arr[0];                                  // start min at first element
    int max = arr[0];                                  // start max at first element

    for (int i = 0; i < n; i++) {                      // scan every element
        sum += arr[i];                                 // add element to running sum
        if (arr[i] < min) min = arr[i];                // update min if smaller
        if (arr[i] > max) max = arr[i];                // update max if larger
    }

    printf("Sum: %ld\n", sum);                         // display total sum
    printf("Min: %d\n", min);                          // display minimum value
    printf("Max: %d\n", max);                          // display maximum value
    printf("Average: %.2f\n", (double)sum / n);        // display average as a float

    free(arr);                                         // release the dynamically allocated array
}

// ── Part C: Integration Exercise ─────────────────────────────────────────────

void part_c(void) {
    char filename[256];  // buffer to hold the input filename entered by the user

    printf("\n--- Part C: Integration Exercise ---\n");  // section header
    printf("Enter input filename: ");
    scanf("%255s", filename);                             // read filename (max 255 chars)

    FILE *infile = fopen(filename, "r");                  // open the input file for reading
    if (infile == NULL) {                                 // check that the file opened
        printf("Could not open file: %s\n", filename);
        return;
    }

    int capacity = 4;                                     // initial capacity (small to force realloc)
    int count = 0;                                        // number of integers read so far
    int *arr = malloc(capacity * sizeof(int));            // allocate initial array
    if (arr == NULL) {                                    // check that malloc succeeded
        printf("Failed to allocate array\n");
        fclose(infile);                                   // close file before returning
        return;
    }

    int value;  // temporary variable to hold each integer read from the file
    while (fscanf(infile, "%d", &value) == 1) {           // read one int at a time until EOF
        if (count >= capacity) {                          // array is full, need more space
            capacity *= 2;                                // double the capacity
            int *temp = realloc(arr, capacity * sizeof(int));  // try to resize the array
            if (temp == NULL) {                           // check that realloc succeeded
                printf("Failed to grow array\n");
                free(arr);                                // free original array on failure
                fclose(infile);                           // close file before returning
                return;
            }
            arr = temp;                                   // update arr to point to new memory
        }
        arr[count] = value;                               // store the value in the array
        count++;                                          // increment the element count
    }

    fclose(infile);                                       // done reading; close the input file

    if (count == 0) {                                     // handle empty file gracefully
        printf("No integers found in file\n");
        free(arr);
        return;
    }

    // compute statistics from the data read out of the file
    long sum = 0;                                         // accumulator for sum of all values
    for (int i = 0; i < count; i++) {                     // add every element to the sum
        sum += arr[i];
    }
    double average = (double)sum / count;                 // compute average as a double

    printf("Read %d integers from file\n", count);        // report how many values were read
    printf("Sum: %ld\n", sum);                            // display the total sum
    printf("Average: %.2f\n", average);                   // display the average

    FILE *outfile = fopen("review_output.txt", "w");      // open output file for writing
    if (outfile == NULL) {                                // check that output file opened
        printf("Could not open output file\n");
        free(arr);                                        // free array before returning
        return;
    }

    fprintf(outfile, "Count: %d\n", count);               // write count to output file
    fprintf(outfile, "Sum: %ld\n", sum);                  // write sum to output file
    fprintf(outfile, "Average: %.2f\n", average);         // write average to output file

    fclose(outfile);                                      // close the output file
    printf("Results written to review_output.txt\n");     // confirm output was written

    free(arr);                                            // release the dynamically allocated array
}
