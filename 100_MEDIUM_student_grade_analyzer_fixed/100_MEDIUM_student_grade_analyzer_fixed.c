#include <stdio.h>
#include <string.h>
#define MAX_STUDENTS 3
#define NAME_LENGTH 50
#define NUM_GRADES 3
typedef struct {
    int student_id;
    char name[NAME_LENGTH];
    int grades[NUM_GRADES];
    float average_grade;
} Student;
int main() {
    Student students[MAX_STUDENTS];
    int i, j;
    float current_sum;
    float max_average = -1.0;
    int top_student_index = -1;
    for (i = 0; i < MAX_STUDENTS; i++) {
        printf("Enter details for Student %d:\n", i + 1);
        printf("Student ID: ");
        scanf("%d", &students[i].student_id);
        while (getchar() != '\n');
        printf("Name: ");
        fgets(students[i].name, NAME_LENGTH, stdin);
        students[i].name[strcspn(students[i].name, "\n")] = 0;
        printf("Enter %d grades:\n", NUM_GRADES);
        current_sum = 0;
        for (j = 0; j < NUM_GRADES; j++) {
            printf("Grade %d: ", j + 1);
            scanf("%d", &students[i].grades[j]);
            current_sum += students[i].grades[j];
        }
        students[i].average_grade = current_sum / NUM_GRADES;
        while (getchar() != '\n');
    }
    for (i = 0; i < MAX_STUDENTS; i++) {
        if (students[i].average_grade > max_average) {
            max_average = students[i].average_grade;
            top_student_index = i;
        }
    }
    printf("\n--- All Student Records ---\n");
    for (i = 0; i < MAX_STUDENTS; i++) {
        printf("ID: %d, Name: %s, Average Grade: %.2f\n",
               students[i].student_id, students[i].name, students[i].average_grade);
    }
    if (top_student_index != -1) {
        printf("\n--- Student with Highest Average Grade ---\n");
        printf("ID: %d\n", students[top_student_index].student_id);
        printf("Name: %s\n", students[top_student_index].name);
        printf("Average Grade: %.2f\n", students[top_student_index].average_grade);
    } else {
        printf("\nNo student data processed.\n");
    }
    return 0;
}