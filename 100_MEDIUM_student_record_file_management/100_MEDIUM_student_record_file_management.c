#include <stdio.h>
#include <string.h>
typedef struct {
    int id;
    char name[50];
    int grade;
} Student;
int main() {
    Student studentsToWrite[] = {
        {101, "Ayse Yilmaz", 90},
        {102, "Mehmet Demir", 85},
        {103, "Zeynep Kaya", 92},
        {104, "Ali Can", 78}
    };
    int numStudents = sizeof(studentsToWrite) / sizeof(Student);
    FILE *file;
    file = fopen("students.dat", "wb");
    if (file == NULL) {
        printf("Dosya yazma hatasi!\n");
        return 1;
    }
    fwrite(studentsToWrite, sizeof(Student), numStudents, file);
    fclose(file);
    printf("Ogrenci kayitlari dosyaya yazildi.\n\n");
    printf("Dosyadaki Tum Ogrenci Kayitlari:\n");
    printf("-----------------------------\n");
    file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("Dosya okuma hatasi!\n");
        return 1;
    }
    Student currentStudent;
    while (fread(&currentStudent, sizeof(Student), 1, file) == 1) {
        printf("ID: %d, Ad: %s, Not: %d\n", currentStudent.id, currentStudent.name, currentStudent.grade);
    }
    fclose(file);
    printf("-----------------------------\n\n");
    int searchId;
    printf("Aranacak ogrenci ID'sini girin: ");
    scanf("%d", &searchId);
    file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("Dosya okuma hatasi!\n");
        return 1;
    }
    int found = 0;
    while (fread(&currentStudent, sizeof(Student), 1, file) == 1) {
        if (currentStudent.id == searchId) {
            printf("Ogrenci bulundu!\n");
            printf("ID: %d, Ad: %s, Not: %d\n", currentStudent.id, currentStudent.name, currentStudent.grade);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("ID %d olan ogrenci bulunamadi.\n", searchId);
    }
    fclose(file);
    return 0;
}