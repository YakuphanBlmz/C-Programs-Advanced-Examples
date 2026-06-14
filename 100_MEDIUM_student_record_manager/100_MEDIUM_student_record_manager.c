#include <stdio.h>
#define MAX_STUDENTS 10
typedef struct {
    int id;
    char name[50];
    int grade;
} Student;
Student students[MAX_STUDENTS];
int studentCount = 0;
void addStudent() {
    if (studentCount < MAX_STUDENTS) {
        printf("Enter Student ID: ");
        scanf("%d", &students[studentCount].id);
        printf("Enter Student Name: ");
        scanf("%s", students[studentCount].name);
        printf("Enter Student Grade: ");
        scanf("%d", &students[studentCount].grade);
        printf("Student added successfully.\n");
        studentCount++;
    } else {
        printf("Maximum number of students reached.\n");
    }
}
void displayStudents() {
    if (studentCount == 0) {
        printf("No students to display.\n");
        return;
    }
    printf("\n--- Student List ---\n");
    for (int i = 0; i < studentCount; i++) {
        printf("ID: %d, Name: %s, Grade: %d\n", students[i].id, students[i].name, students[i].grade);
    }
    printf("--------------------\n");
}
void findStudent() {
    int searchId;
    printf("Enter Student ID to search: ");
    scanf("%d", &searchId);
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == searchId) {
            printf("Student Found: ID: %d, Name: %s, Grade: %d\n", students[i].id, students[i].name, students[i].grade);
            found = 1;
            break;
        }
    }
    if (found == 0) {
        printf("Student with ID %d not found.\n", searchId);
    }
}
void calculateAverageGrade() {
    if (studentCount == 0) {
        printf("No students to calculate average grade.\n");
        return;
    }
    int totalGrade = 0;
    for (int i = 0; i < studentCount; i++) {
        totalGrade += students[i].grade;
    }
    printf("Average Grade: %.2f\n", (float)totalGrade / studentCount);
}
int main() {
    int choice;
    do {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Find Student by ID\n");
        printf("4. Calculate Average Grade\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                findStudent();
                break;
            case 4:
                calculateAverageGrade();
                break;
            case 5:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
    return 0;
}