#include <stdio.h>
#include <string.h>
#define MAX_STUDENTS 10
#define NAME_LENGTH 50
#define FILENAME "students.bin"
typedef struct {
    int id;
    char name[NAME_LENGTH];
    int grade;
} Student;
int addStudent(Student students[], int currentCount, int maxCapacity);
void displayStudents(const Student students[], int currentCount);
void saveStudents(const Student students[], int currentCount, char filename[]);
int loadStudents(Student students[], int maxCapacity, char filename[]);
void clearInputBuffer();
int main() {
    Student studentRecords[MAX_STUDENTS];
    int studentCount = 0;
    int choice;
    studentCount = loadStudents(studentRecords, MAX_STUDENTS, FILENAME);
    if (studentCount > 0) {
        printf("Loaded %d student records from %s.\n", studentCount, FILENAME);
    }
    do {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Save Students to File\n");
        printf("4. Load Students from File\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();
        switch (choice) {
            case 1:
                studentCount = addStudent(studentRecords, studentCount, MAX_STUDENTS);
                break;
            case 2:
                displayStudents(studentRecords, studentCount);
                break;
            case 3:
                saveStudents(studentRecords, studentCount, FILENAME);
                break;
            case 4:
                studentCount = loadStudents(studentRecords, MAX_STUDENTS, FILENAME);
                printf("Loaded %d student records.\n", studentCount);
                break;
            case 5:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
    return 0;
}
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
int addStudent(Student students[], int currentCount, int maxCapacity) {
    if (currentCount >= maxCapacity) {
        printf("Maximum student capacity reached. Cannot add more students.\n");
        return currentCount;
    }
    Student newStudent;
    printf("Enter student ID: ");
    scanf("%d", &newStudent.id);
    clearInputBuffer();
    printf("Enter student Name: ");
    fgets(newStudent.name, NAME_LENGTH, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0;
    printf("Enter student Grade: ");
    scanf("%d", &newStudent.grade);
    clearInputBuffer();
    students[currentCount] = newStudent;
    printf("Student added successfully.\n");
    return currentCount + 1;
}
void displayStudents(const Student students[], int currentCount) {
    if (currentCount == 0) {
        printf("No students to display.\n");
        return;
    }
    printf("\n--- Student List ---\n");
    for (int i = 0; i < currentCount; i++) {
        printf("ID: %d, Name: %s, Grade: %d\n", students[i].id, students[i].name, students[i].grade);
    }
}
void saveStudents(const Student students[], int currentCount, char filename[]) {
    FILE *fp;
    fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Error opening file for writing: %s\n", filename);
        return;
    }
    fwrite(students, sizeof(Student), currentCount, fp);
    fclose(fp);
    printf("Successfully saved %d student records to %s.\n", currentCount, filename);
}
int loadStudents(Student students[], int maxCapacity, char filename[]) {
    FILE *fp;
    fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("No existing student data found in %s.\n", filename);
        return 0;
    }
    int loadedCount = fread(students, sizeof(Student), maxCapacity, fp);
    fclose(fp);
    return loadedCount;
}