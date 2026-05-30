#include <stdio.h>
#define MAX_NAME_LENGTH 50
#define NUM_SCORES 3
#define MAX_STUDENTS 3
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    int scores[NUM_SCORES];
    float average_score;
} Student;
int main() {
    Student students[MAX_STUDENTS] = {
        {101, "Alice Johnson", {85, 90, 88}, 0.0f},
        {102, "Bob Williams", {70, 75, 72}, 0.0f},
        {103, "Charlie Brown", {92, 88, 95}, 0.0f}
    };
    int i, j;
    int current_sum;
    float current_avg;
    for (i = 0; i < MAX_STUDENTS; i++) {
        current_sum = 0;
        for (j = 0; j < NUM_SCORES; j++) {
            current_sum += students[i].scores[j];
        }
        current_avg = (float)current_sum / NUM_SCORES;
        students[i].average_score = current_avg;
    }
    int highest_avg_student_index = 0;
    for (i = 1; i < MAX_STUDENTS; i++) {
        if (students[i].average_score > students[highest_avg_student_index].average_score) {
            highest_avg_student_index = i;
        }
    }
    printf("--- Student Grades ---\n");
    for (i = 0; i < MAX_STUDENTS; i++) {
        printf("ID: %d, Name: %s, Avg Score: %.2f\n",
               students[i].id, students[i].name, students[i].average_score);
    }
    printf("\n--- Student with Highest Average Score ---\n");
    printf("ID: %d, Name: %s, Avg Score: %.2f\n",
           students[highest_avg_student_index].id,
           students[highest_avg_student_index].name,
           students[highest_avg_student_index].average_score);
    return 0;
}