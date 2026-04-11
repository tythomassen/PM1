#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_file(void);
void write_file(void);
void binary_file(void);

int main(void) {
    int choice;
    printf("Select exercise:\n");
    printf("1. Read File\n");
    printf("2. Write File\n");
    printf("3. Binary File\n");
    printf("Choice: ");
    scanf("%d", &choice);
    getchar();  // Consume newline

    switch (choice) {
        case 1: read_file(); break;
        case 2: write_file(); break;
        case 3: binary_file(); break;
        default: printf("Invalid choice\n");
    }
    return 0;
}

void read_file(void) {
    char filename[100];
    printf("Enter filename: ");
    scanf("%99s", filename);

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Cannot open file '%s'\n", filename);
        return;
    }
//HGJKJLKgjbhknj,

    printf("\n--- File Contents ---\n");
    char line[256];
    int linenum = 1;
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%d: %s", linenum, line);
        linenum++;
    }
    printf("\n--- End of File ---\n");

//vuygihuojiko;lp'

    fclose(fp);
}

void write_file(void) {
    char filename[100];
    char content[1024];

    printf("Enter filename: ");
    scanf("%99s", filename);
    getchar();  // Consume newline

    printf("Enter content: ");
    fgets(content, sizeof(content), stdin);

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Cannot open file '%s'\n", filename);
        return;
    }

    fprintf(fp, "%s", content);
    fclose(fp);

    printf("File '%s' written successfully\n", filename);
}

void binary_file(void) {
    typedef struct {
        int id;
        char name[32];
        float score;
    } Record;

    Record records[3] = {
        {1, "Alice",   95.5f},
        {2, "Bob",     87.3f},
        {3, "Charlie", 92.0f}
    };

    FILE *fp = fopen("data.bin", "wb");
    if (fp == NULL) {
        printf("Error: Cannot open data.bin for writing\n");
        return;
    }
    fwrite(records, sizeof(Record), 3, fp);
    fclose(fp);
    printf("Wrote 3 records to data.bin\n");

    Record loaded[3];
    fp = fopen("data.bin", "rb");
    if (fp == NULL) {
        printf("Error: Cannot open data.bin for reading\n");
        return;
    }
    fread(loaded, sizeof(Record), 3, fp);
    fclose(fp);

    printf("\n--- Loaded Records ---\n");
    for (int i = 0; i < 3; i++) {
        printf("ID: %d, Name: %s, Score: %.1f\n",
               loaded[i].id, loaded[i].name, loaded[i].score);
    }

    remove("data.bin");
}
