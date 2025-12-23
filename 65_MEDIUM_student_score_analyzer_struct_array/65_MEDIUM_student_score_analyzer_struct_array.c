#include <stdio.h>
#include <string.h>
#define MAX_STUDENTS 5
#define NAME_LENGTH 50
typedef struct {
    int id;
    char name[NAME_LENGTH];
    int score;
} Student;
int main() {
    Student classStudents[MAX_STUDENTS];
    int studentCount = 0;
    if (studentCount < MAX_STUDENTS) {
        classStudents[studentCount].id = 101;
        strncpy(classStudents[studentCount].name, "Alice", NAME_LENGTH - 1);
        classStudents[studentCount].name[NAME_LENGTH - 1] = '\0';
        classStudents[studentCount].score = 95;
        studentCount++;
    }
    if (studentCount < MAX_STUDENTS) {
        classStudents[studentCount].id = 102;
        strncpy(classStudents[studentCount].name, "Bob", NAME_LENGTH - 1);
        classStudents[studentCount].name[NAME_LENGTH - 1] = '\0';
        classStudents[studentCount].score = 88;
        studentCount++;
    }
    if (studentCount < MAX_STUDENTS) {
        classStudents[studentCount].id = 103;
        strncpy(classStudents[studentCount].name, "Charlie", NAME_LENGTH - 1);
        classStudents[studentCount].name[NAME_LENGTH - 1] = '\0';
        classStudents[studentCount].score = 99;
        studentCount++;
    }
    if (studentCount < MAX_STUDENTS) {
        classStudents[studentCount].id = 104;
        strncpy(classStudents[studentCount].name, "David", NAME_LENGTH - 1);
        classStudents[studentCount].name[NAME_LENGTH - 1] = '\0';
        classStudents[studentCount].score = 76;
        studentCount++;
    }
    if (studentCount < MAX_STUDENTS) {
        classStudents[studentCount].id = 105;
        strncpy(classStudents[studentCount].name, "Eve", NAME_LENGTH - 1);
        classStudents[studentCount].name[NAME_LENGTH - 1] = '\0';
        classStudents[studentCount].score = 92;
        studentCount++;
    }
    int highestScore = -1;
    int topStudentIndex = -1;
    for (int i = 0; i < studentCount; i++) {
        if (classStudents[i].score > highestScore) {
            highestScore = classStudents[i].score;
            topStudentIndex = i;
        }
    }
    if (topStudentIndex != -1) {
        printf("Top Performing Student:\n");
        printf("ID: %d\n", classStudents[topStudentIndex].id);
        printf("Name: %s\n", classStudents[topStudentIndex].name);
        printf("Score: %d\n", classStudents[topStudentIndex].score);
    } else {
        printf("No students found.\n");
    }
    return 0;
}