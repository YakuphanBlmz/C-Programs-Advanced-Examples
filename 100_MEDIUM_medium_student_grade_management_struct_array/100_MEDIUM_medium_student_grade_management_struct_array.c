#include <stdio.h>
#include <string.h>
#define MAX_STUDENTS 5
typedef struct {
    int id;
    char name[50];
    int grade;
} Student;
int main() {
    Student students[MAX_STUDENTS];
    int i;
    int totalGrades = 0;
    int highestGrade = -1;
    int highestGradeStudentIndex = -1;
    students[0].id = 101;
    strcpy(students[0].name, "Ayse Yilmaz");
    students[0].grade = 85;
    students[1].id = 102;
    strcpy(students[1].name, "Can Demir");
    students[1].grade = 92;
    students[2].id = 103;
    strcpy(students[2].name, "Elif Kaya");
    students[2].grade = 78;
    students[3].id = 104;
    strcpy(students[3].name, "Fatih Ozturk");
    students[3].grade = 95;
    students[4].id = 105;
    strcpy(students[4].name, "Gizem Cetin");
    students[4].grade = 88;
    for (i = 0; i < MAX_STUDENTS; i++) {
        totalGrades += students[i].grade;
        if (students[i].grade > highestGrade) {
            highestGrade = students[i].grade;
            highestGradeStudentIndex = i;
        }
    }
    printf("Ortalama Not: %.2f\n", (double)totalGrades / MAX_STUDENTS);
    printf("Average Grade: %.2f\n", (double)totalGrades / MAX_STUDENTS);
    if (highestGradeStudentIndex != -1) {
        printf("\nEn Yuksek Not Alan Ogrenci:\n");
        printf("ID: %d, Isim: %s, Not: %d\n",
               students[highestGradeStudentIndex].id,
               students[highestGradeStudentIndex].name,
               students[highestGradeStudentIndex].grade);
        printf("\nStudent with the Highest Grade:\n");
        printf("ID: %d, Name: %s, Grade: %d\n",
               students[highestGradeStudentIndex].id,
               students[highestGradeStudentIndex].name,
               students[highestGradeStudentIndex].grade);
    }
    return 0;
}