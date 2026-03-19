#include <stdio.h>
#include <string.h>
#define MAX_STUDENTS 10
#define FILENAME "students.dat"
typedef struct {
    int id;
    char name[50];
    int grade;
} Student;
Student students[MAX_STUDENTS];
int studentCount = 0;
void addStudent(int id, const char* name, int grade) {
    if (studentCount < MAX_STUDENTS) {
        students[studentCount].id = id;
        strncpy(students[studentCount].name, name, sizeof(students[studentCount].name) - 1);
        students[studentCount].name[sizeof(students[studentCount].name) - 1] = '\0';
        students[studentCount].grade = grade;
        studentCount++;
        printf("Student added successfully.\n");
    } else {
        printf("Maximum student limit reached. Cannot add more students.\n");
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
void saveStudentsToFile() {
    FILE *fp = fopen(FILENAME, "wb");
    if (fp == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    fwrite(students, sizeof(Student), studentCount, fp);
    fclose(fp);
    printf("Student data saved to %s successfully.\n", FILENAME);
}
void loadStudentsFromFile() {
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("Error opening file for reading. File might not exist yet.\n");
        studentCount = 0; 
        return;
    }
    studentCount = fread(students, sizeof(Student), MAX_STUDENTS, fp);
    fclose(fp);
    printf("Loaded %d students from %s.\n", studentCount, FILENAME);
}
int main() {
    int choice;
    int id, grade;
    char name[50];
    loadStudentsFromFile(); 
    do {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Save Students to File\n");
        printf("4. Load Students from File\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter Student ID: ");
                scanf("%d", &id);
                printf("Enter Student Name: ");
                scanf("%s", name); 
                printf("Enter Student Grade: ");
                scanf("%d", &grade);
                addStudent(id, name, grade);
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                saveStudentsToFile();
                break;
            case 4:
                loadStudentsFromFile();
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