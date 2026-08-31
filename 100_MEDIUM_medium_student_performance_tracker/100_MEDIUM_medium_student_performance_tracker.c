#include <stdio.h>
#include <string.h>
typedef struct {
    char name[50];
    int studentId;
    int projectScore;
    int midtermScore;
    int finalScore;
} Student;
int main() {
    const int MAX_STUDENTS = 3;
    Student students[MAX_STUDENTS];
    int i;
    int highestScore = -1;
    int highestScoringStudentIndex = -1;
    for (i = 0; i < MAX_STUDENTS; i++) {
        printf("Enter details for student %d:\n", i + 1);
        printf("Name: ");
        fgets(students[i].name, sizeof(students[i].name), stdin);
        students[i].name[strcspn(students[i].name, "\n")] = 0;
        printf("Student ID: ");
        scanf("%d", &students[i].studentId);
        while (getchar() != '\n');
        printf("Project Score: ");
        scanf("%d", &students[i].projectScore);
        while (getchar() != '\n');
        printf("Midterm Score: ");
        scanf("%d", &students[i].midtermScore);
        while (getchar() != '\n');
        printf("Final Score: ");
        scanf("%d", &students[i].finalScore);
        while (getchar() != '\n');
    }
    printf("\n--- Student Performance Summary ---\n");
    for (i = 0; i < MAX_STUDENTS; i++) {
        int currentTotalScore = students[i].projectScore + students[i].midtermScore + students[i].finalScore;
        printf("Student: %s (ID: %d), Total Score: %d\n", students[i].name, students[i].studentId, currentTotalScore);
        if (currentTotalScore > highestScore) {
            highestScore = currentTotalScore;
            highestScoringStudentIndex = i;
        }
    }
    if (highestScoringStudentIndex != -1) {
        printf("\n--- Highest Scoring Student ---\n");
        printf("Name: %s\n", students[highestScoringStudentIndex].name);
        printf("ID: %d\n", students[highestScoringStudentIndex].studentId);
        printf("Total Score: %d\n", highestScore);
    } else {
        printf("\nNo student data processed.\n");
    }
    return 0;
}