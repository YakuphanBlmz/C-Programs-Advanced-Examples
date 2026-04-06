#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    int id;
    char name[50];
    int grades[3];
} Student;
double calculate_average(Student s) {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += s.grades[i];
    }
    return (double)sum / 3.0;
}
int main() {
    const int MAX_STUDENTS = 3; 
    Student students[MAX_STUDENTS]; 
    students[0].id = 101;
    strcpy(students[0].name, "Ali Veli");
    students[0].grades[0] = 85;
    students[0].grades[1] = 90;
    students[0].grades[2] = 78;
    students[1].id = 102;
    strcpy(students[1].name, "Ayse Fatma");
    students[1].grades[0] = 92;
    students[1].grades[1] = 88;
    students[1].grades[2] = 95;
    students[2].id = 103;
    strcpy(students[2].name, "Mehmet Can");
    students[2].grades[0] = 70;
    students[2].grades[1] = 75;
    students[2].grades[2] = 80;
    double max_average = -1.0;
    int top_student_index = -1;
    printf("--- Student Grades and Averages ---\n");
    for (int i = 0; i < MAX_STUDENTS; i++) {
        double current_average = calculate_average(students[i]);
        printf("ID: %d, Name: %s, Grades: %d, %d, %d, Average: %.2f\n",
               students[i].id, students[i].name, 
               students[i].grades[0], students[i].grades[1], students[i].grades[2],
               current_average);
        if (current_average > max_average) {
            max_average = current_average;
            top_student_index = i;
        }
    }
    if (top_student_index != -1) {
        printf("\n--- Student with Highest Average ---\n");
        printf("ID: %d, Name: %s, Average: %.2f\n",
               students[top_student_index].id,
               students[top_student_index].name,
               max_average);
    } else {
        printf("\nNo student data processed.\n");
    }
    return 0;
}