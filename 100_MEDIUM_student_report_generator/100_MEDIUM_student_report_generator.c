#include <stdio.h>
typedef struct {
    int id;
    char name[50];
    int score;
} Student;
int main() {
    Student students[10];
    int studentCount = 0;
    FILE *inputFile;
    FILE *outputFile;
    int totalScore = 0;
    double averageScore = 0.0;
    inputFile = fopen("students.txt", "r");
    if (inputFile == NULL) {
        fprintf(stderr, "Error: Could not open students.txt for reading.\n");
        return 1;
    }
    while (studentCount < 10 && fscanf(inputFile, "%d %s %d", 
                                       &students[studentCount].id, 
                                       students[studentCount].name, 
                                       &students[studentCount].score) == 3) {
        totalScore += students[studentCount].score;
        studentCount++;
    }
    fclose(inputFile);
    if (studentCount == 0) {
        fprintf(stderr, "No student data read from students.txt.\n");
        return 1;
    }
    averageScore = (double)totalScore / studentCount;
    outputFile = fopen("report.txt", "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Error: Could not open report.txt for writing.\n");
        return 1;
    }
    fprintf(outputFile, "Student Report:\n");
    fprintf(outputFile, "--------------------------------------------------\n");
    fprintf(outputFile, "ID   Name          Score Status\n");
    fprintf(outputFile, "--------------------------------------------------\n");
    for (int i = 0; i < studentCount; i++) {
        fprintf(outputFile, "%-4d %-13s %-5d %s\n", 
                students[i].id, 
                students[i].name, 
                students[i].score, 
                (students[i].score >= 50) ? "PASS" : "FAIL");
    }
    fprintf(outputFile, "--------------------------------------------------\n");
    fprintf(outputFile, "Overall Average Score: %.2f\n", averageScore);
    fclose(outputFile);
    printf("Student report generated successfully in report.txt\n");
    return 0;
}