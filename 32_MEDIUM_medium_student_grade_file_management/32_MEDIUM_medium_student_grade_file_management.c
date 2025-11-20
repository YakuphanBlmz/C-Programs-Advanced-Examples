#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    int studentId;
    char name[50];
    int grade;
} Student;
int main() {
    Student studentsToWrite[] = {
        {101, "Alice Smith", 92},
        {102, "Bob Johnson", 85},
        {103, "Charlie Brown", 78},
        {104, "Diana Prince", 95},
        {105, "Eve Adams", 88}
    };
    int numStudentsToWrite = sizeof(studentsToWrite) / sizeof(studentsToWrite[0]);
    FILE *file = fopen("students.dat", "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }
    fwrite(studentsToWrite, sizeof(Student), numStudentsToWrite, file);
    fclose(file);
    printf("Student data written to students.dat successfully.\n\n");
    file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return 1;
    }
    Student studentsRead[50];
    int numStudentsRead = 0;
    while (fread(&studentsRead[numStudentsRead], sizeof(Student), 1, file) == 1) {
        numStudentsRead++;
        if (numStudentsRead >= 50) {
            break;
        }
    }
    fclose(file);
    printf("Student data read from students.dat successfully.\n");
    printf("Number of students read: %d\n\n", numStudentsRead);
    if (numStudentsRead == 0) {
        printf("No student data found to process.\n");
        return 0;
    }
    int totalGrade = 0;
    int highestGrade = -1;
    int highestGradeStudentIndex = -1;
    for (int i = 0; i < numStudentsRead; i++) {
        totalGrade += studentsRead[i].grade;
        if (studentsRead[i].grade > highestGrade) {
            highestGrade = studentsRead[i].grade;
            highestGradeStudentIndex = i;
        }
    }
    double averageGrade = (double)totalGrade / numStudentsRead;
    printf("Average Grade: %.2f\n", averageGrade);
    if (highestGradeStudentIndex != -1) {
        printf("Student with Highest Grade:\n");
        printf("ID: %d, Name: %s, Grade: %d\n", 
               studentsRead[highestGradeStudentIndex].studentId,
               studentsRead[highestGradeStudentIndex].name,
               studentsRead[highestGradeStudentIndex].grade);
    } else {
        printf("Could not determine student with highest grade.\n");
    }
    return 0;
}