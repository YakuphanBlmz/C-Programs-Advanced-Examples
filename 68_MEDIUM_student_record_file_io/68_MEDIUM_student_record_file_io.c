#include <stdio.h>
#include <stdlib.h>
#define MAX_STUDENTS 3
#define NAME_LENGTH 50
#define MAJOR_LENGTH 30
typedef struct {
    int id;
    char name[NAME_LENGTH];
    char major[MAJOR_LENGTH];
    float gpa;
} Student;
int main() {
    Student students[MAX_STUDENTS];
    FILE *filePointer;
    int i;
    printf("Ogrenci bilgilerini girin (%d ogrenci):\n", MAX_STUDENTS);
    for (i = 0; i < MAX_STUDENTS; i++) {
        printf("\nOgrenci %d:\n", i + 1);
        printf("ID: ");
        scanf("%d", &students[i].id);
        printf("Ad (bosluksuz): ");
        scanf("%s", students[i].name);
        printf("Bolum (bosluksuz): ");
        scanf("%s", students[i].major);
        printf("GPA: ");
        scanf("%f", &students[i].gpa);
    }
    filePointer = fopen("students.dat", "wb");
    if (filePointer == NULL) {
        printf("Hata: 'students.dat' dosyasi acilamadi.\n");
        return EXIT_FAILURE;
    }
    fwrite(students, sizeof(Student), MAX_STUDENTS, filePointer);
    fclose(filePointer);
    printf("\nOgrenci kayitlari 'students.dat' dosyasina yazildi.\n");
    Student readStudents[MAX_STUDENTS];
    filePointer = fopen("students.dat", "rb");
    if (filePointer == NULL) {
        printf("Hata: 'students.dat' dosyasi okuma modunda acilamadi.\n");
        return EXIT_FAILURE;
    }
    fread(readStudents, sizeof(Student), MAX_STUDENTS, filePointer);
    fclose(filePointer);
    printf("\n'students.dat' dosyasindan okunan ogrenci bilgileri:\n");
    for (i = 0; i < MAX_STUDENTS; i++) {
        printf("\nOgrenci %d:\n", i + 1);
        printf("ID: %d\n", readStudents[i].id);
        printf("Ad: %s\n", readStudents[i].name);
        printf("Bolum: %s\n", readStudents[i].major);
        printf("GPA: %.2f\n", readStudents[i].gpa);
    }
    return 0;
}