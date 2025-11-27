#include <stdio.h>
#define MAX_STUDENTS 3
#define NUM_SUBJECTS 3
#define MAX_NAME_LEN 50
typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int grades[NUM_SUBJECTS];
    float average;
} Student;
int main() {
    Student students[MAX_STUDENTS];
    int i, j;
    float currentTotalGrades;
    for (i = 0; i < MAX_STUDENTS; i++) {
        printf("Enter details for Student %d:\n", i + 1);
        printf("ID: ");
        scanf("%d", &students[i].id);
        printf("Name (single word, no spaces): ");
        scanf("%s", students[i].name);
        currentTotalGrades = 0;
        printf("Enter %d grades for %s: ", NUM_SUBJECTS, students[i].name);
        for (j = 0; j < NUM_SUBJECTS; j++) {
            scanf("%d", &students[i].grades[j]);
            currentTotalGrades += students[i].grades[j];
        }
        students[i].average = currentTotalGrades / NUM_SUBJECTS;
        printf("\n");
    }
    float highestAverage = -1.0;
    int highestAverageStudentIndex = -1;
    for (i = 0; i < MAX_STUDENTS; i++) {
        if (students[i].average > highestAverage) {
            highestAverage = students[i].average;
            highestAverageStudentIndex = i;
        }
    }
    printf("--- Student Records ---\n");
    for (i = 0; i < MAX_STUDENTS; i++) {
        printf("Student ID: %d\n", students[i].id);
        printf("Name: %s\n", students[i].name);
        printf("Grades: ");
        for (j = 0; j < NUM_SUBJECTS; j++) {
            printf("%d ", students[i].grades[j]);
        }
        printf("\n");
        printf("Average Grade: %.2f\n", students[i].average);
        printf("-----------------------\n");
    }
    if (highestAverageStudentIndex != -1) {
        printf("\nStudent with Highest Average:\n");
        printf("ID: %d\n", students[highestAverageStudentIndex].id);
        printf("Name: %s\n", students[highestAverageStudentIndex].name);
        printf("Average Grade: %.2f\n", students[highestAverageStudentIndex].average);
    } else {
        printf("No student data available.\n");
    }
    return 0;
}