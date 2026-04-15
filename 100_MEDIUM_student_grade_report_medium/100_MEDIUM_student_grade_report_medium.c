#include <stdio.h>
#include <string.h>
#define MAX_STUDENTS 5
typedef struct Student {
    int id;
    char name[50];
    int grade1;
    int grade2;
    int grade3;
    float average;
} Student;
Student calculateStudentAverage(Student s) {
    s.average = (float)(s.grade1 + s.grade2 + s.grade3) / 3.0;
    return s;
}
void displayStudent(Student s) {
    printf("ID: %d\n", s.id);
    printf("Name: %s\n", s.name);
    printf("Grades: %d, %d, %d\n", s.grade1, s.grade2, s.grade3);
    printf("Average: %.2f\n", s.average);
    printf("--------------------\n");
}
int main() {
    Student students[MAX_STUDENTS];
    int currentStudentCount = 0;
    students[currentStudentCount].id = 101;
    strcpy(students[currentStudentCount].name, "Alice Smith");
    students[currentStudentCount].grade1 = 85;
    students[currentStudentCount].grade2 = 90;
    students[currentStudentCount].grade3 = 88;
    currentStudentCount++;
    students[currentStudentCount].id = 102;
    strcpy(students[currentStudentCount].name, "Bob Johnson");
    students[currentStudentCount].grade1 = 70;
    students[currentStudentCount].grade2 = 75;
    students[currentStudentCount].grade3 = 68;
    currentStudentCount++;
    students[currentStudentCount].id = 103;
    strcpy(students[currentStudentCount].name, "Charlie Brown");
    students[currentStudentCount].grade1 = 92;
    students[currentStudentCount].grade2 = 88;
    students[currentStudentCount].grade3 = 95;
    currentStudentCount++;
    students[currentStudentCount].id = 104;
    strcpy(students[currentStudentCount].name, "Diana Prince");
    students[currentStudentCount].grade1 = 78;
    students[currentStudentCount].grade2 = 82;
    students[currentStudentCount].grade3 = 80;
    currentStudentCount++;
    for (int i = 0; i < currentStudentCount; i++) {
        students[i] = calculateStudentAverage(students[i]);
    }
    printf("--- All Student Grades ---\n");
    for (int i = 0; i < currentStudentCount; i++) {
        displayStudent(students[i]);
    }
    float highestAverage = -1.0;
    int topStudentIndex = -1;
    for (int i = 0; i < currentStudentCount; i++) {
        if (students[i].average > highestAverage) {
            highestAverage = students[i].average;
            topStudentIndex = i;
        }
    }
    printf("\n--- Student with Highest Average ---\n");
    if (topStudentIndex != -1) {
        displayStudent(students[topStudentIndex]);
    } else {
        printf("No students to display.\n");
    }
    return 0;
}