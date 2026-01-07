#include <stdio.h>
#define MAX_STUDENTS 100
#define MAX_NAME_LEN 50
typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int grade;
} Student;
int main() {
    Student students[MAX_STUDENTS];
    int studentCount = 0;
    int totalGrades = 0;
    double averageGrade = 0.0;
    FILE *inputFile;
    FILE *outputFile;
    inputFile = fopen("students.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening students.txt for reading.\n");
        return 1;
    }
    while (studentCount < MAX_STUDENTS && 
           fscanf(inputFile, "%d %s %d", 
                  &students[studentCount].id, 
                  students[studentCount].name, 
                  &students[studentCount].grade) == 3) {
        totalGrades += students[studentCount].grade;
        studentCount++;
    }
    fclose(inputFile);
    if (studentCount > 0) {
        averageGrade = (double)totalGrades / studentCount;
    } else {
        averageGrade = 0.0;
    }
    outputFile = fopen("results.txt", "w");
    if (outputFile == NULL) {
        printf("Error opening results.txt for writing.\n");
        return 1;
    }
    fprintf(outputFile, "Average Grade: %.2f\n", averageGrade);
    fprintf(outputFile, "\nStudents Above Average:\n");
    if (studentCount == 0) {
        fprintf(outputFile, "No students to evaluate.\n");
    } else {
        int foundAboveAverage = 0;
        for (int i = 0; i < studentCount; i++) {
            if (students[i].grade > averageGrade) {
                fprintf(outputFile, "ID: %d, Name: %s, Grade: %d\n", 
                        students[i].id, students[i].name, students[i].grade);
                foundAboveAverage = 1;
            }
        }
        if (!foundAboveAverage) {
            fprintf(outputFile, "No students found above average.\n");
        }
    }
    fclose(outputFile);
    return 0;
}