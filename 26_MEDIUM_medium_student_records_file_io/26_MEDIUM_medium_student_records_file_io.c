#include <stdio.h>
#include <string.h>
#define MAX_NAME_LENGTH 50
#define MAX_STUDENTS 10
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    int grade;
} Student;
int main() {
    Student students[MAX_STUDENTS];
    int numStudents;
    FILE *file;
    int i;
    char buffer[MAX_NAME_LENGTH + 2];
    printf("Enter the number of students (max %d): ", MAX_STUDENTS);
    scanf("%d", &numStudents);
    while (getchar() != '\n');
    if (numStudents > MAX_STUDENTS || numStudents <= 0) {
        printf("Invalid number of students. Using 1.\n");
        numStudents = 1;
    }
    for (i = 0; i < numStudents; i++) {
        printf("Enter ID for student %d: ", i + 1);
        scanf("%d", &students[i].id);
        while (getchar() != '\n');
        printf("Enter name for student %d: ", i + 1);
        fgets(buffer, MAX_NAME_LENGTH + 2, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(students[i].name, buffer, MAX_NAME_LENGTH - 1);
        students[i].name[MAX_NAME_LENGTH - 1] = '\0';
        printf("Enter grade for student %d: ", i + 1);
        scanf("%d", &students[i].grade);
        while (getchar() != '\n');
    }
    file = fopen("students.dat", "wb");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return 1;
    }
    for (i = 0; i < numStudents; i++) {
        fwrite(&students[i], sizeof(Student), 1, file);
    }
    fclose(file);
    printf("Student data written to students.dat\n\n");
    printf("Reading student data from students.dat:\n");
    file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return 1;
    }
    i = 0;
    while (fread(&students[i], sizeof(Student), 1, file) == 1 && i < MAX_STUDENTS) {
        printf("ID: %d, Name: %s, Grade: %d\n", students[i].id, students[i].name, students[i].grade);
        i++;
    }
    fclose(file);
    return 0;
}