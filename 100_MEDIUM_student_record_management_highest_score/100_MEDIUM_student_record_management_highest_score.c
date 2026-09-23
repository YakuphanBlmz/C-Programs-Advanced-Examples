#include <stdio.h>
#define MAX_STUDENTS 3
typedef struct {
    int id;
    char name[50];
    int score;
} Student;
int main() {
    Student students[MAX_STUDENTS];
    int i;
    int highestScore = -1;
    int highestScorerIndex = -1;
    printf("Please enter data for %d students:\n", MAX_STUDENTS);
    for (i = 0; i < MAX_STUDENTS; i++) {
        printf("Student %d ID: ", i + 1);
        scanf("%d", &students[i].id);
        printf("Student %d Name: ", i + 1);
        scanf("%s", students[i].name);
        printf("Student %d Score: ", i + 1);
        scanf("%d", &students[i].score);
    }
    for (i = 0; i < MAX_STUDENTS; i++) {
        if (students[i].score > highestScore) {
            highestScore = students[i].score;
            highestScorerIndex = i;
        }
    }
    if (highestScorerIndex != -1) {
        printf("\n--- Student with Highest Score ---\n");
        printf("ID: %d\n", students[highestScorerIndex].id);
        printf("Name: %s\n", students[highestScorerIndex].name);
        printf("Score: %d\n", students[highestScorerIndex].score);
    } else {
        printf("\nNo student data available.\n");
    }
    printf("\n--- All Student Data ---\n");
    for (i = 0; i < MAX_STUDENTS; i++) {
        printf("Student %d:\n", i + 1);
        printf("  ID: %d\n", students[i].id);
        printf("  Name: %s\n", students[i].name);
        printf("  Score: %d\n", students[i].score);
    }
    return 0;
}