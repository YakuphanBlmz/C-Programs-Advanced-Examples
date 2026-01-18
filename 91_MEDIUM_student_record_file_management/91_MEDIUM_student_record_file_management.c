#include <stdio.h>
#include <string.h>
#define MAX_NAME_LENGTH 50
#define MAX_STUDENTS 3
typedef struct {
    int studentId;
    char name[MAX_NAME_LENGTH];
    int score;
} Student;
int main() {
    Student studentsToWrite[MAX_STUDENTS];
    studentsToWrite[0].studentId = 101;
    strcpy(studentsToWrite[0].name, "Alice Smith");
    studentsToWrite[0].score = 92;
    studentsToWrite[1].studentId = 102;
    strcpy(studentsToWrite[1].name, "Bob Johnson");
    studentsToWrite[1].score = 88;
    studentsToWrite[2].studentId = 103;
    strcpy(studentsToWrite[2].name, "Charlie Brown");
    studentsToWrite[2].score = 95;
    FILE *filePtr = fopen("students.dat", "wb");
    if (filePtr == NULL) {
        printf("Error opening file for writing!\n");
        return 1;
    }
    fwrite(studentsToWrite, sizeof(Student), MAX_STUDENTS, filePtr);
    fclose(filePtr);
    printf("Student data written to students.dat\n");
    Student studentsRead[MAX_STUDENTS];
    filePtr = fopen("students.dat", "rb");
    if (filePtr == NULL) {
        printf("Error opening file for reading!\n");
        return 1;
    }
    fread(studentsRead, sizeof(Student), MAX_STUDENTS, filePtr);
    fclose(filePtr);
    printf("Student data read from students.dat\n");
    int highestScore = -1;
    int highestScoringStudentIndex = -1;
    for (int i = 0; i < MAX_STUDENTS; i++) {
        if (studentsRead[i].score > highestScore) {
            highestScore = studentsRead[i].score;
            highestScoringStudentIndex = i;
        }
    }
    if (highestScoringStudentIndex != -1) {
        printf("Student with the highest score: %s (ID: %d, Score: %d)\n",
               studentsRead[highestScoringStudentIndex].name,
               studentsRead[highestScoringStudentIndex].studentId,
               studentsRead[highestScoringStudentIndex].score);
    } else {
        printf("No student data available.\n");
    }
    return 0;
}