#include <stdio.h>
#include <string.h>
typedef struct {
    int id;
    char name[50];
    float grade;
} Student;
void writeStudentsToFile(const char* filename, Student students[], int count) {
    FILE* fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    fwrite(students, sizeof(Student), count, fp);
    fclose(fp);
}
int readStudentsFromFile(const char* filename, Student students[], int maxCount) {
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error opening file for reading!\n");
        return 0;
    }
    int studentsRead = fread(students, sizeof(Student), maxCount, fp);
    fclose(fp);
    return studentsRead;
}
void displayStudents(Student students[], int count) {
    printf("--- Student Records ---\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d, Name: %s, Grade: %.2f\n", students[i].id, students[i].name, students[i].grade);
    }
    printf("------------------------\n");
}
int main() {
    Student initialStudents[3];
    int initialCount = 3;
    initialStudents[0].id = 101;
    strcpy(initialStudents[0].name, "Alice Smith");
    initialStudents[0].grade = 92.5;
    initialStudents[1].id = 102;
    strcpy(initialStudents[1].name, "Bob Johnson");
    initialStudents[1].grade = 88.0;
    initialStudents[2].id = 103;
    strcpy(initialStudents[2].name, "Charlie Brown");
    initialStudents[2].grade = 76.2;
    printf("Initial Students:\n");
    displayStudents(initialStudents, initialCount);
    writeStudentsToFile("students.dat", initialStudents, initialCount);
    printf("\nStudents written to students.dat\n");
    Student loadedStudents[3];
    int loadedCount;
    loadedCount = readStudentsFromFile("students.dat", loadedStudents, 3);
    printf("\nStudents read from students.dat (%d records):\n", loadedCount);
    if (loadedCount > 0) {
        displayStudents(loadedStudents, loadedCount);
    } else {
        printf("No students were loaded from the file.\n");
    }
    return 0;
}