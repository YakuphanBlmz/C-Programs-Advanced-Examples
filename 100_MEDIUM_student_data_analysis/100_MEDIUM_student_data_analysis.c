#include <stdio.h>
#include <string.h>
#define MAX_STUDENTS 100
#define MAX_NAME_LEN 50
#define FILENAME "students.txt"
typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int score;
} Student;
int main() {
    Student students[MAX_STUDENTS];
    FILE *file_ptr;
    int student_count = 0;
    int total_score = 0;
    int highest_score = -1;
    int highest_scorer_index = -1;
    double average_score;
    file_ptr = fopen(FILENAME, "r");
    if (file_ptr == NULL) {
        printf("Hata: Dosya acilamadi '%s'\n", FILENAME);
        return 1;
    }
    while (student_count < MAX_STUDENTS && 
           fscanf(file_ptr, "%d %s %d", 
                  &students[student_count].id, 
                  students[student_count].name, 
                  &students[student_count].score) == 3) {
        total_score += students[student_count].score;
        if (students[student_count].score > highest_score) {
            highest_score = students[student_count].score;
            highest_scorer_index = student_count;
        }
        student_count++;
    }
    fclose(file_ptr);
    if (student_count == 0) {
        printf("Dosyada hic ogrenci verisi bulunamadi.\n");
        return 0;
    }
    average_score = (double)total_score / student_count;
    printf("--- Ogrenci Performans Raporu ---\n");
    printf("Toplam Ogrenci Sayisi: %d\n", student_count);
    printf("Ortalama Puan: %.2f\n", average_score);
    if (highest_scorer_index != -1) {
        printf("En Yuksek Puan Alan Ogrenci:\n");
        printf("  ID: %d\n", students[highest_scorer_index].id);
        printf("  Ad: %s\n", students[highest_scorer_index].name);
        printf("  Puan: %d\n", students[highest_scorer_index].score);
    } else {
        printf("En yuksek puanli ogrenci bulunamadi (hic puan yok).\n");
    }
    return 0;
}