#include <stdio.h>
#include <string.h>
typedef struct {
    int id;
    char name[50];
    int score;
} Student;
int main() {
    Student students_to_write[] = {
        {101, "Alice Smith", 85},
        {102, "Bob Johnson", 92},
        {103, "Charlie Brown", 78},
        {104, "Diana Prince", 95},
        {105, "Eve Adams", 88}
    };
    int num_initial_students = sizeof(students_to_write) / sizeof(Student);
    FILE *file_ptr_write = fopen("students.dat", "wb");
    if (file_ptr_write == NULL) {
        printf("Error opening file for writing!\n");
        return 1;
    }
    for (int i = 0; i < num_initial_students; i++) {
        fwrite(&students_to_write[i], sizeof(Student), 1, file_ptr_write);
    }
    fclose(file_ptr_write);
    printf("Student data successfully written to students.dat\n");
    FILE *file_ptr_read = fopen("students.dat", "rb");
    if (file_ptr_read == NULL) {
        printf("Error opening file for reading!\n");
        return 1;
    }
    Student current_student;
    int total_score = 0;
    int student_count = 0;
    Student highest_scorer = {0, "", -1};
    printf("\nReading student data from students.dat:\n");
    while (fread(&current_student, sizeof(Student), 1, file_ptr_read) == 1) {
        printf("ID: %d, Name: %s, Score: %d\n", current_student.id, current_student.name, current_student.score);
        total_score += current_student.score;
        student_count++;
        if (current_student.score > highest_scorer.score) {
            highest_scorer = current_student;
        }
    }
    fclose(file_ptr_read);
    if (student_count > 0) {
        double average_score = (double)total_score / student_count;
        printf("\nTotal students read: %d\n", student_count);
        printf("Average score: %.2f\n", average_score);
        printf("Student with the highest score:\n");
        printf("  ID: %d, Name: %s, Score: %d\n", highest_scorer.id, highest_scorer.name, highest_scorer.score);
    } else {
        printf("\nNo student data found in the file.\n");
    }
    return 0;
}