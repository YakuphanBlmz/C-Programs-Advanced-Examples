#include <stdio.h>
#include <string.h>
#define MAX_STUDENTS 5
typedef struct {
    int studentId;
    char name[50];
    int grade;
} Student;
Student students[MAX_STUDENTS];
int studentCount = 0;
void addStudent(int id, const char* name, int grade) {
    if (studentCount < MAX_STUDENTS) {
        students[studentCount].studentId = id;
        strncpy(students[studentCount].name, name, sizeof(students[studentCount].name) - 1);
        students[studentCount].name[sizeof(students[studentCount].name) - 1] = '\0';
        students[studentCount].grade = grade;
        studentCount++;
        printf("Student %s (ID: %d) added successfully.\n", name, id);
    } else {
        printf("Class is full. Cannot add %s.\n", name);
    }
}
void displayAllStudents() {
    if (studentCount == 0) {
        printf("No students in the class.\n");
        return;
    }
    printf("\n--- All Students ---\n");
    for (int i = 0; i < studentCount; i++) {
        printf("ID: %d, Name: %s, Grade: %d\n", students[i].studentId, students[i].name, students[i].grade);
    }
    printf("---------------------\n");
}
void findStudent(int id) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].studentId == id) {
            printf("\n--- Student Found ---\n");
            printf("ID: %d, Name: %s, Grade: %d\n", students[i].studentId, students[i].name, students[i].grade);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("\nStudent with ID %d not found.\n", id);
    }
}
void calculateAverageGrade() {
    if (studentCount == 0) {
        printf("\nNo students to calculate average grade.\n");
        return;
    }
    int totalGrade = 0;
    for (int i = 0; i < studentCount; i++) {
        totalGrade += students[i].grade;
    }
    double average = (double)totalGrade / studentCount;
    printf("\nAverage grade for %d students: %.2f\n", studentCount, average);
}
int main() {
    addStudent(101, "Alice Smith", 85);
    addStudent(102, "Bob Johnson", 92);
    addStudent(103, "Charlie Brown", 78);
    addStudent(104, "Diana Prince", 95);
    addStudent(105, "Eve Adams", 88);
    addStudent(106, "Frank White", 70);
    displayAllStudents();
    findStudent(103);
    findStudent(200);
    calculateAverageGrade();
    return 0;
}