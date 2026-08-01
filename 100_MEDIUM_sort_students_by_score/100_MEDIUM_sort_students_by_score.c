#include <stdio.h>
#define MAX_NAME_LENGTH 50
#define NUM_STUDENTS 5
typedef struct {
    int studentId;
    char name[MAX_NAME_LENGTH];
    int score;
} Student;
void printStudents(const char* title, Student students[], int size) {
    int i;
    printf("%s\n", title);
    for (i = 0; i < size; i++) {
        printf("ID: %d, Name: %s, Score: %d\n", students[i].studentId, students[i].name, students[i].score);
    }
    printf("\n");
}
int main() {
    Student students[NUM_STUDENTS] = {
        {101, "Alice", 85},
        {102, "Bob", 92},
        {103, "Charlie", 85},
        {104, "David", 78},
        {105, "Eve", 92}
    };
    int i, j;
    Student temp;
    printStudents("Orijinal Öğrenci Listesi:", students, NUM_STUDENTS);
    for (i = 0; i < NUM_STUDENTS - 1; i++) {
        for (j = 0; j < NUM_STUDENTS - 1 - i; j++) {
            if (students[j].score < students[j+1].score) {
                temp = students[j];
                students[j] = students[j+1];
                students[j+1] = temp;
            } else if (students[j].score == students[j+1].score) {
                if (students[j].studentId > students[j+1].studentId) {
                    temp = students[j];
                    students[j] = students[j+1];
                    students[j+1] = temp;
                }
            }
        }
    }
    printStudents("Sıralanmış Öğrenci Listesi:", students, NUM_STUDENTS);
    return 0;
}