#include <stdio.h>
typedef struct Student {
    int id;
    char name[50];
    int score;
} Student;
int main() {
    Student students_to_write[3] = {
        {101, "Alice Smith", 85},
        {102, "Bob Johnson", 92},
        {103, "Charlie Brown", 78}
    };
    FILE *file_ptr;
    file_ptr = fopen("students.dat", "wb");
    if (file_ptr == NULL) {
        printf("Dosya yazmak icin acilamadi.\n");
        return 1;
    }
    fwrite(students_to_write, sizeof(Student), 3, file_ptr);
    fclose(file_ptr);
    printf("Ogrenci verileri students.dat dosyasina yazildi.\n\n");
    Student students_read[3];
    Student highest_score_student;
    int max_score = -1;
    int i;
    file_ptr = fopen("students.dat", "rb");
    if (file_ptr == NULL) {
        printf("Dosya okumak icin acilamadi.\n");
        return 1;
    }
    printf("Dosyadan okunan ogrenci verileri:\n");
    printf("-----------------------------\n");
    fread(students_read, sizeof(Student), 3, file_ptr);
    for (i = 0; i < 3; i++) {
        printf("ID: %d, Ad: %s, Puan: %d\n", students_read[i].id, students_read[i].name, students_read[i].score);
        if (students_read[i].score > max_score) {
            max_score = students_read[i].score;
            highest_score_student = students_read[i];
        }
    }
    fclose(file_ptr);
    printf("\nEn yuksek puana sahip ogrenci:\n");
    printf("------------------------------\n");
    printf("ID: %d, Ad: %s, Puan: %d\n", highest_score_student.id, highest_score_student.name, highest_score_student.score);
    return 0;
}