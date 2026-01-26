#include <stdio.h>
#define MAX_STUDENTS 100
#define FILENAME_IN "students.txt"
#define FILENAME_OUT "passed_students.txt"
#define PASS_SCORE 60
typedef struct {
    int id;
    char name[50];
    int score;
} Student;
int main() {
    Student students[MAX_STUDENTS];
    int studentCount = 0;
    FILE *inFile = NULL;
    FILE *outFile = NULL;
    inFile = fopen(FILENAME_IN, "r");
    if (inFile == NULL) {
        printf("Error: Could not open input file %s\n", FILENAME_IN);
        return 1;
    }
    while (studentCount < MAX_STUDENTS &&
           fscanf(inFile, "%d,%49[^,],%d\n",
                  &students[studentCount].id,
                  students[studentCount].name,
                  &students[studentCount].score) == 3) {
        studentCount++;
    }
    fclose(inFile);
    if (studentCount == 0) {
        printf("No student data found or read.\n");
        return 0;
    }
    int totalScore = 0;
    for (int i = 0; i < studentCount; i++) {
        totalScore += students[i].score;
    }
    float averageScore = (float)totalScore / studentCount;
    printf("Average score: %.2f\n", averageScore);
    int highestScoreIndex = 0;
    for (int i = 1; i < studentCount; i++) {
        if (students[i].score > students[highestScoreIndex].score) {
            highestScoreIndex = i;
        }
    }
    printf("Student with highest score: ID %d, Name %s, Score %d\n",
           students[highestScoreIndex].id,
           students[highestScoreIndex].name,
           students[highestScoreIndex].score);
    outFile = fopen(FILENAME_OUT, "w");
    if (outFile == NULL) {
        printf("Error: Could not open output file %s\n", FILENAME_OUT);
        return 1;
    }
    fprintf(outFile, "ID,Name,Score\n");
    for (int i = 0; i < studentCount; i++) {
        if (students[i].score >= PASS_SCORE) {
            fprintf(outFile, "%d,%s,%d\n",
                    students[i].id,
                    students[i].name,
                    students[i].score);
        }
    }
    fclose(outFile);
    printf("Passed students written to %s\n", FILENAME_OUT);
    return 0;
}