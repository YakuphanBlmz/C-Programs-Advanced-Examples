#include <stdio.h>
#include <string.h>
#define MAX_STUDENTS 3
#define MAX_NAME_LEN 50
typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    float grade;
} Student;
int main() {
    Student students[MAX_STUDENTS];
    int numStudents = 0;
    char filename[] = "students.dat";
    FILE *filePtr;
    int i;
    float totalGrade = 0.0;
    printf("Please enter data for up to %d students.\n", MAX_STUDENTS);
    printf("Enter ID, Name (single word), Grade. Enter 0 for ID to stop.\n");
    for (i = 0; i < MAX_STUDENTS; i++) {
        printf("Student %d ID: ", i + 1);
        scanf("%d", &students[i].id);
        if (students[i].id == 0) {
            break;
        }
        printf("Student %d Name: ", i + 1);
        scanf("%s", students[i].name);
        printf("Student %d Grade: ", i + 1);
        scanf("%f", &students[i].grade);
        numStudents++;
    }
    filePtr = fopen(filename, "wb");
    if (filePtr == NULL) {
        printf("Error opening file for writing!\n");
        return 1;
    }
    fwrite(students, sizeof(Student), numStudents, filePtr);
    fclose(filePtr);
    printf("\nSuccessfully saved %d student records to %s.\n", numStudents, filename);
    for(i = 0; i < MAX_STUDENTS; i++) {
        students[i].id = 0;
        students[i].name[0] = '\0';
        students[i].grade = 0.0;
    }
    numStudents = 0;
    totalGrade = 0.0;
    filePtr = fopen(filename, "rb");
    if (filePtr == NULL) {
        printf("Error opening file for reading or file does not exist.\n");
        return 1;
    }
    printf("\nLoading student records from %s:\n", filename);
    printf("--------------------------------------------------\n");
    printf("ID\tName\tGrade\n");
    printf("--------------------------------------------------\n");
    while (fread(&students[numStudents], sizeof(Student), 1, filePtr) == 1 && numStudents < MAX_STUDENTS) {
        printf("%d\t%s\t%.2f\n", students[numStudents].id, students[numStudents].name, students[numStudents].grade);
        totalGrade += students[numStudents].grade;
        numStudents++;
    }
    fclose(filePtr);
    if (numStudents > 0) {
        printf("--------------------------------------------------\n");
        printf("Total students loaded: %d\n", numStudents);
        printf("Average Grade: %.2f\n", totalGrade / numStudents);
    } else {
        printf("No student records found in the file.\n");
    }
    return 0;
}