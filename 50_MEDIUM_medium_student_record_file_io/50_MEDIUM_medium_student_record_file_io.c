#include <stdio.h>
#include <string.h>
#define MAX_NAME_LEN 50
#define MAX_STUDENTS 3
typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    float grade;
} Student;
int main() {
    FILE *fp;
    Student students_to_write[MAX_STUDENTS];
    Student students_read[MAX_STUDENTS];
    int i;
    int search_id;
    int found_student_index = -1;
    students_to_write[0].id = 101;
    strcpy(students_to_write[0].name, "Ali Veli");
    students_to_write[0].grade = 85.5f;
    students_to_write[1].id = 102;
    strcpy(students_to_write[1].name, "Ayse Yilmaz");
    students_to_write[1].grade = 92.0f;
    students_to_write[2].id = 103;
    strcpy(students_to_write[2].name, "Can Demir");
    students_to_write[2].grade = 78.2f;
    fp = fopen("students.dat", "wb");
    if (fp == NULL) {
        printf("Hata: students.dat dosyasi acilamadi.\n");
        return 1;
    }
    fwrite(students_to_write, sizeof(Student), MAX_STUDENTS, fp);
    fclose(fp);
    printf("Ogrenciler dosyaya yazildi.\n\n");
    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("Hata: students.dat dosyasi acilamadi.\n");
        return 1;
    }
    fread(students_read, sizeof(Student), MAX_STUDENTS, fp);
    fclose(fp);
    printf("Dosyadan okunan ogrenci bilgileri:\n");
    for (i = 0; i < MAX_STUDENTS; i++) {
        printf("ID: %d, Ad: %s, Not: %.2f\n", students_read[i].id, students_read[i].name, students_read[i].grade);
    }
    printf("\n");
    printf("Aramak istediginiz ogrenci ID'sini girin: ");
    scanf("%d", &search_id);
    for (i = 0; i < MAX_STUDENTS; i++) {
        if (students_read[i].id == search_id) {
            found_student_index = i;
            break;
        }
    }
    if (found_student_index != -1) {
        printf("\nOgrenci bulundu:\n");
        printf("ID: %d, Ad: %s, Not: %.2f\n", 
               students_read[found_student_index].id, 
               students_read[found_student_index].name, 
               students_read[found_student_index].grade);
    } else {
        printf("\nID %d olan ogrenci bulunamadi.\n", search_id);
    }
    return 0;
}