#include <stdio.h>
#include <string.h>
typedef struct {
    int id;
    char name[50];
    float score;
} Student;
int main() {
    const char* filename = "students.dat";
    FILE* file_ptr;
    file_ptr = fopen(filename, "wb");
    if (file_ptr == NULL) {
        printf("Error opening file for writing!\n");
        return 1;
    }
    Student student1;
    student1.id = 101;
    strncpy(student1.name, "Alice Smith", sizeof(student1.name) - 1);
    student1.name[sizeof(student1.name) - 1] = '\0';
    student1.score = 85.5f;
    Student student2;
    student2.id = 102;
    strncpy(student2.name, "Bob Johnson", sizeof(student2.name) - 1);
    student2.name[sizeof(student2.name) - 1] = '\0';
    student2.score = 92.0f;
    Student student3;
    student3.id = 103;
    strncpy(student3.name, "Charlie Brown", sizeof(student3.name) - 1);
    student3.name[sizeof(student3.name) - 1] = '\0';
    student3.score = 78.2f;
    fwrite(&student1, sizeof(Student), 1, file_ptr);
    fwrite(&student2, sizeof(Student), 1, file_ptr);
    fwrite(&student3, sizeof(Student), 1, file_ptr);
    fclose(file_ptr);
    printf("Student records successfully written to %s\n\n", filename);
    file_ptr = fopen(filename, "rb");
    if (file_ptr == NULL) {
        printf("Error opening file for reading!\n");
        return 1;
    }
    printf("Reading student records from %s:\n", filename);
    Student current_student;
    int record_count = 0;
    while (fread(&current_student, sizeof(Student), 1, file_ptr) == 1) {
        record_count++;
        printf("Record %d:\n", record_count);
        printf("  ID: %d\n", current_student.id);
        printf("  Name: %s\n", current_student.name);
        printf("  Score: %.2f\n", current_student.score);
        printf("---\n");
    }
    fclose(file_ptr);
    if (record_count == 0) {
        printf("No records found in %s.\n", filename);
    } else {
        printf("Successfully read %d student records.\n", record_count);
    }
    return 0;
}