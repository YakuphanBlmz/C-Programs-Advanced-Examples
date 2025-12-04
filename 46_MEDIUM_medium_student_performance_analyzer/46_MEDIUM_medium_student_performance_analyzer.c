#include <stdio.h>
#include <string.h>
#define MAX_STUDENTS 5
#define MAX_NAME_LENGTH 50
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    int score;
} Student;
int main() {
    Student students[MAX_STUDENTS];
    int i;
    int totalScore = 0;
    double averageScore;
    for (i = 0; i < MAX_STUDENTS; i++) {
        printf("Enter ID for student %d: ", i + 1);
        scanf("%d", &students[i].id);
        printf("Enter Name for student %d: ", i + 1);
        scanf("%s", students[i].name);
        printf("Enter Score for student %d: ", i + 1);
        scanf("%d", &students[i].score);
        totalScore += students[i].score;
    }
    averageScore = (double)totalScore / MAX_STUDENTS;
    printf("\nAverage score: %.2f\n", averageScore);
    printf("\nStudents with scores above average:\n");
    for (i = 0; i < MAX_STUDENTS; i++) {
        if (students[i].score > averageScore) {
            printf("ID: %d, Name: %s, Score: %d\n", students[i].id, students[i].name, students[i].score);
        }
    }
    return 0;
}