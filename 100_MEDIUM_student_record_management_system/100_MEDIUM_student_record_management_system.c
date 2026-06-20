#include <stdio.h>
#include <string.h>
#define MAX_NAME_LEN 50
typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int grade;
} Student;
void add_student_record() {
    FILE *file;
    Student student;
    printf("\nEnter student ID: ");
    scanf("%d", &student.id);
    while (getchar() != '\n');
    printf("Enter student name (max %d chars): ", MAX_NAME_LEN - 1);
    scanf("%49[^
]", student.name);
    while (getchar() != '\n');
    printf("Enter student grade: ");
    scanf("%d", &student.grade);
    while (getchar() != '\n');
    file = fopen("students.dat", "ab");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    fwrite(&student, sizeof(Student), 1, file);
    fclose(file);
    printf("Student record added successfully.\n");
}
void list_student_records() {
    FILE *file;
    Student student;
    file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("Error opening file for reading or no records yet.\n");
        return;
    }
    printf("\n--- Student Records ---\n");
    printf("ID\tName\t\tGrade\n");
    printf("-------------------------\n");
    while (fread(&student, sizeof(Student), 1, file) == 1) {
        printf("%d\t%-15s\t%d\n", student.id, student.name, student.grade);
    }
    fclose(file);
    printf("-------------------------\n");
}
int main() {
    int choice;
    do {
        printf("\n--- Student Management System ---\n");
        printf("1. Add New Student\n");
        printf("2. List All Students\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');
        switch (choice) {
            case 1:
                add_student_record();
                break;
            case 2:
                list_student_records();
                break;
            case 3:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
    return 0;
}