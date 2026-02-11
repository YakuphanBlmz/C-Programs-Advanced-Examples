#include <stdio.h>
typedef struct {
    int studentId;
    char name[50];
    int score;
} Student;
int main() {
    Student students[] = {
        {101, "Ali Yilmaz", 85},
        {102, "Ayse Demir", 92},
        {103, "Can Kaya", 78},
        {104, "Elif Bulut", 65},
        {105, "Deniz Akdeniz", 95},
        {106, "Fatih Ozturk", 88},
        {107, "Guler Sahin", 72}
    };
    int numStudents = sizeof(students) / sizeof(students[0]);
    int totalScore = 0;
    double averageScore;
    for (int i = 0; i < numStudents; i++) {
        totalScore += students[i].score;
    }
    averageScore = (double)totalScore / numStudents;
    printf("Total students: %d\n", numStudents);
    printf("Average score: %.2f\n\n", averageScore);
    printf("Students scoring above average:\n");
    for (int i = 0; i < numStudents; i++) {
        if (students[i].score > averageScore) {
            printf("- %s (Score: %d)\n", students[i].name, students[i].score);
        }
    }
    return 0;
}