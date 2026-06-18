#include <stdio.h>
#include <string.h>
#define MAX_STUDENTS 5
#define FILENAME "students.dat"
typedef struct {
    int id;
    char name[50];
    int score;
} Student;
void saveStudentsToFile(const char *filename, Student students[], int count) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    fwrite(students, sizeof(Student), count, file);
    fclose(file);
    printf("Students saved successfully.\n");
}
int loadStudentsFromFile(const char *filename, Student students[]) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("No existing student data found. Starting fresh.\n");
        return 0;
    }
    int numRead = fread(students, sizeof(Student), MAX_STUDENTS, file);
    fclose(file);
    printf("%d students loaded from file.\n", numRead);
    return numRead;
}
void displayStudents(const Student students[], int count) {
    printf("\n--- Current Students (Count: %d) ---\n", count);
    if (count == 0) {
        printf("No students to display.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        printf("ID: %d, Name: %s, Score: %d\n", students[i].id, students[i].name, students[i].score);
    }
    printf("-----------------------------------\n");
}
int main() {
    Student schoolStudents[MAX_STUDENTS];
    int studentCount = 0;
    studentCount = loadStudentsFromFile(FILENAME, schoolStudents);
    displayStudents(schoolStudents, studentCount);
    if (studentCount < MAX_STUDENTS) {
        Student newStudent;
        newStudent.id = 1001 + studentCount;
        strcpy(newStudent.name, "Ali Can");
        newStudent.score = 85;
        schoolStudents[studentCount] = newStudent;
        studentCount++;
        printf("\nAdded new student: %s (ID: %d)\n", newStudent.name, newStudent.id);
    } else {
        printf("\nCannot add new student, maximum capacity reached.\n");
    }
    displayStudents(schoolStudents, studentCount);
    saveStudentsToFile(FILENAME, schoolStudents, studentCount);
    return 0;
}