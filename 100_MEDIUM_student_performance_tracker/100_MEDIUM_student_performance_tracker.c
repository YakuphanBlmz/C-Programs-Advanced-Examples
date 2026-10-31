#include <stdio.h>
#include <string.h>
#define MAX_STUDENTS 3
#define NAME_LENGTH 50
typedef struct {
    int studentId;
    char name[NAME_LENGTH];
    int mathGrade;
    int scienceGrade;
    int historyGrade;
} Student;
int main() {
    Student students[MAX_STUDENTS];
    students[0].studentId = 101;
    strcpy(students[0].name, "Ayse Yilmaz");
    students[0].mathGrade = 85;
    students[0].scienceGrade = 90;
    students[0].historyGrade = 78;
    students[1].studentId = 102;
    strcpy(students[1].name, "Mehmet Demir");
    students[1].mathGrade = 70;
    students[1].scienceGrade = 65;
    students[1].historyGrade = 72;
    students[2].studentId = 103;
    strcpy(students[2].name, "Zeynep Kaya");
    students[2].mathGrade = 92;
    students[2].scienceGrade = 88;
    students[2].historyGrade = 95;
    float highestAverage = -1.0;
    int topStudentIndex = -1;
    for (int i = 0; i < MAX_STUDENTS; i++) {
        float currentAverage = (float)(students[i].mathGrade + students[i].scienceGrade + students[i].historyGrade) / 3.0;
        if (currentAverage > highestAverage) {
            highestAverage = currentAverage;
            topStudentIndex = i;
        }
    }
    if (topStudentIndex != -1) {
        printf("En yuksek ortalamaya sahip ogrenci:\n");
        printf("ID: %d\n", students[topStudentIndex].studentId);
        printf("Ad: %s\n", students[topStudentIndex].name);
        printf("Ortalama Not: %.2f\n", highestAverage);
    } else {
        printf("Ogrenci bulunamadi.\n");
    }
    return 0;
}