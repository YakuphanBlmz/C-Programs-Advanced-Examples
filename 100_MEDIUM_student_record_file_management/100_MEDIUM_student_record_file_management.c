#include <stdio.h>
#include <string.h>
#define MAX_NAME_LENGTH 50
#define NUM_STUDENTS 3
typedef struct {
    int student_id;
    char name[MAX_NAME_LENGTH];
    int score;
} Student;
int main() {
    Student students_write[NUM_STUDENTS];
    Student students_read[NUM_STUDENTS];
    FILE *file_ptr;
    int i;
    int total_score = 0;
    double average_score;
    students_write[0].student_id = 101;
    strcpy(students_write[0].name, "Alice");
    students_write[0].score = 85;
    students_write[1].student_id = 102;
    strcpy(students_write[1].name, "Bob");
    students_write[1].score = 92;
    students_write[2].student_id = 103;
    strcpy(students_write[2].name, "Charlie");
    students_write[2].score = 78;
    file_ptr = fopen("students.dat", "wb");
    if (file_ptr == NULL) {
        printf("Dosya yazmak için açılamadı!\n");
        return 1;
    }
    fwrite(students_write, sizeof(Student), NUM_STUDENTS, file_ptr);
    fclose(file_ptr);
    printf("Öğrenci kayıtları students.dat dosyasına yazıldı.\n\n");
    file_ptr = fopen("students.dat", "rb");
    if (file_ptr == NULL) {
        printf("Dosya okumak için açılamadı!\n");
        return 1;
    }
    fread(students_read, sizeof(Student), NUM_STUDENTS, file_ptr);
    fclose(file_ptr);
    printf("Öğrenci kayıtları students.dat dosyasından okundu:\n");
    for (i = 0; i < NUM_STUDENTS; i++) {
        printf("ID: %d, Ad: %s, Puan: %d\n",
               students_read[i].student_id,
               students_read[i].name,
               students_read[i].score);
        total_score += students_read[i].score;
    }
    average_score = (double)total_score / NUM_STUDENTS;
    printf("\nTüm öğrencilerin ortalama puanı: %.2f\n", average_score);
    return 0;
}