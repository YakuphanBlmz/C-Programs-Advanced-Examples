#include <stdio.h>
#include <string.h>
#define MAX_STUDENTS 3
#define MAX_NAME_LENGTH 50
#define NUM_GRADES 3
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    int grades[NUM_GRADES];
} Student;
double calculateAverage(Student s) {
    int sum = 0;
    for (int i = 0; i < NUM_GRADES; i++) {
        sum += s.grades[i];
    }
    return (double)sum / NUM_GRADES;
}
void printStudentDetails(Student s) {
    printf("ID: %d, Name: %s, Average Grade: %.2f\n", s.id, s.name, calculateAverage(s));
}
int findTopStudentIndex(Student students[], int count) {
    if (count <= 0) {
        return -1;
    }
    int topIndex = 0;
    double maxAverage = calculateAverage(students[0]);
    for (int i = 1; i < count; i++) {
        double currentAverage = calculateAverage(students[i]);
        if (currentAverage > maxAverage) {
            maxAverage = currentAverage;
            topIndex = i;
        }
    }
    return topIndex;
}
int main() {
    Student classRoster[MAX_STUDENTS];
    classRoster[0].id = 101;
    strcpy(classRoster[0].name, "Ali Veli");
    classRoster[0].grades[0] = 85;
    classRoster[0].grades[1] = 90;
    classRoster[0].grades[2] = 88;
    classRoster[1].id = 102;
    strcpy(classRoster[1].name, "Ayse Fatma");
    classRoster[1].grades[0] = 75;
    classRoster[1].grades[1] = 80;
    classRoster[1].grades[2] = 78;
    classRoster[2].id = 103;
    strcpy(classRoster[2].name, "Canan Kara");
    classRoster[2].grades[0] = 92;
    classRoster[2].grades[1] = 95;
    classRoster[2].grades[2] = 90;
    printf("Student Details:\n");
    for (int i = 0; i < MAX_STUDENTS; i++) {
        printStudentDetails(classRoster[i]);
    }
    int topStudentIndex = findTopStudentIndex(classRoster, MAX_STUDENTS);
    if (topStudentIndex != -1) {
        printf("\nStudent with the highest average grade:\n");
        printStudentDetails(classRoster[topStudentIndex]);
    } else {
        printf("\nNo students to process.\n");
    }
    return 0;
}