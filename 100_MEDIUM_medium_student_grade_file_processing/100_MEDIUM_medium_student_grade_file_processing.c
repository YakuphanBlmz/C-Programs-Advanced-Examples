#include <stdio.h>
#include <string.h>
#define MAX_STUDENTS 10
typedef struct {
    int studentId;
    char name[50];
    int grade1;
    int grade2;
    int grade3;
    float average;
} StudentReport;
int main() {
    StudentReport students[MAX_STUDENTS];
    int studentCount = 0;
    FILE *inputFile;
    FILE *outputFile;
    inputFile = fopen("grades.txt", "r");
    if (inputFile == NULL) {
        printf("Hata: grades.txt dosyasi acilamadi.\n");
        return 1;
    }
    while (studentCount < MAX_STUDENTS &&
           fscanf(inputFile, "%d %s %d %d %d",
                  &students[studentCount].studentId,
                  students[studentCount].name,
                  &students[studentCount].grade1,
                  &students[studentCount].grade2,
                  &students[studentCount].grade3) == 5) {
        students[studentCount].average = (float)(students[studentCount].grade1 +
                                                 students[studentCount].grade2 +
                                                 students[studentCount].grade3) / 3.0f;
        studentCount++;
    }
    fclose(inputFile);
    outputFile = fopen("report.txt", "w");
    if (outputFile == NULL) {
        printf("Hata: report.txt dosyasi olusturulamadi veya acilamadi.\n");
        return 1;
    }
    for (int i = 0; i < studentCount; i++) {
        fprintf(outputFile, "Student ID: %d, Name: %s, Average: %.2f\n",
                students[i].studentId,
                students[i].name,
                students[i].average);
    }
    fclose(outputFile);
    printf("Ogrenci raporu basariyla olusturuldu: report.txt\n");
    return 0;
}