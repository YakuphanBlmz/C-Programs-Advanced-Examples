#include <stdio.h>
#include <string.h> 
typedef struct {
    int id;
    char name[50];
    int score;
} Student;
#define MAX_STUDENTS 3
int main() {
    Student students[MAX_STUDENTS];
    FILE *file;
    int i;
    students[0].id = 101;
    strcpy(students[0].name, "Alice Smith");
    students[0].score = 95;
    students[1].id = 102;
    strcpy(students[1].name, "Bob Johnson");
    students[1].score = 88;
    students[2].id = 103;
    strcpy(students[2].name, "Charlie Brown");
    students[2].score = 72;
    printf("Initial students created:\n");
    for (i = 0; i < MAX_STUDENTS; i++) {
        printf("ID: %d, Name: %s, Score: %d\n", students[i].id, students[i].name, students[i].score);
    }
    printf("\n");
    file = fopen("students.dat", "wb");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return 1;
    }
    fwrite(students, sizeof(Student), MAX_STUDENTS, file);
    fclose(file);
    printf("Students saved to students.dat\n\n");
    for (i = 0; i < MAX_STUDENTS; i++) {
        students[i].id = 0;
        strcpy(students[i].name, "");
        students[i].score = 0;
    }
    printf("In-memory student data cleared.\n");
    printf("Cleared students (should be empty/zero):\n");
    for (i = 0; i < MAX_STUDENTS; i++) {
        printf("ID: %d, Name: %s, Score: %d\n", students[i].id, students[i].name, students[i].score);
    }
    printf("\n");
    file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return 1;
    }
    fread(students, sizeof(Student), MAX_STUDENTS, file);
    fclose(file);
    printf("Students loaded from students.dat\n");
    printf("Loaded students from file:\n");
    for (i = 0; i < MAX_STUDENTS; i++) {
        printf("ID: %d, Name: %s, Score: %d\n", students[i].id, students[i].name, students[i].score);
    }
    return 0;
}