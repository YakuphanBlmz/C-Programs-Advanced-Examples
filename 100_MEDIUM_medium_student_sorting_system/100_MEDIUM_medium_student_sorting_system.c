#include <stdio.h>
#include <string.h>
typedef struct {
    char name[50];
    int id;
    int score;
} Student;
#define MAX_STUDENTS 10
int main() {
    Student students[MAX_STUDENTS];
    int numStudents;
    int i, j;
    Student tempStudent;
    printf("Enter the number of students (up to %d): ", MAX_STUDENTS);
    scanf("%d", &numStudents);
    if (numStudents <= 0 || numStudents > MAX_STUDENTS) {
        printf("Invalid number of students. Exiting.\n");
        return 1;
    }
    for (i = 0; i < numStudents; i++) {
        printf("Enter details for student %d:\n", i + 1);
        printf("Name (single word): ");
        scanf("%s", students[i].name);
        printf("ID: ");
        scanf("%d", &students[i].id);
        printf("Score: ");
        scanf("%d", &students[i].score);
    }
    for (i = 0; i < numStudents - 1; i++) {
        for (j = 0; j < numStudents - 1 - i; j++) {
            if (students[j].score < students[j+1].score) {
                tempStudent = students[j];
                students[j] = students[j+1];
                students[j+1] = tempStudent;
            } else if (students[j].score == students[j+1].score) {
                if (students[j].id > students[j+1].id) {
                    tempStudent = students[j];
                    students[j] = students[j+1];
                    students[j+1] = tempStudent;
                }
            }
        }
    }
    printf("\n--- Sorted Student List ---\n");
    printf("Name\tID\tScore\n");
    printf("---------------------------\n");
    for (i = 0; i < numStudents; i++) {
        printf("%s\t%d\t%d\n", students[i].name, students[i].id, students[i].score);
    }
    if (numStudents > 0) {
        printf("\n--- Student with the Highest Score ---\n");
        printf("Name: %s\n", students[0].name);
        printf("ID: %d\n", students[0].id);
        printf("Score: %d\n", students[0].score);
    } else {
        printf("\nNo students to display.\n");
    }
    return 0;
}