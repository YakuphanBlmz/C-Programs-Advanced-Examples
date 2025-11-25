#include <stdio.h>
#include <string.h>
typedef struct {
    char name[50];
    int studentId;
    int grade;
} Student;
int main() {
    Student students[5];
    int numStudents = 5;
    strcpy(students[0].name, "Alice");
    students[0].studentId = 101;
    students[0].grade = 85;
    strcpy(students[1].name, "Bob");
    students[1].studentId = 102;
    students[1].grade = 92;
    strcpy(students[2].name, "Charlie");
    students[2].studentId = 103;
    students[2].grade = 78;
    strcpy(students[3].name, "Diana");
    students[3].studentId = 104;
    students[3].grade = 95;
    strcpy(students[4].name, "Eve");
    students[4].studentId = 105;
    students[4].grade = 88;
    for (int i = 0; i < numStudents - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < numStudents; j++) {
            if (students[j].grade > students[maxIdx].grade) {
                maxIdx = j;
            }
        }
        Student temp = students[i];
        students[i] = students[maxIdx];
        students[maxIdx] = temp;
    }
    printf("Students sorted by grade (descending):\n");
    for (int i = 0; i < numStudents; i++) {
        printf("Name: %s, ID: %d, Grade: %d\n", students[i].name, students[i].studentId, students[i].grade);
    }
    return 0;
}