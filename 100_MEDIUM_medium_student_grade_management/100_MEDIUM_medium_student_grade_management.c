#include <stdio.h>
typedef struct {
    int id;
    char name[50];
    float exam1;
    float exam2;
    float final_grade;
} Student;
int main() {
    Student students[3];
    int i;
    printf("Lutfen 3 ogrencinin bilgilerini giriniz:\n");
    for (i = 0; i < 3; i++) {
        printf("Ogrenci %d ID: ", i + 1);
        scanf("%d", &students[i].id);
        printf("Ogrenci %d Adi: ", i + 1);
        scanf("%s", students[i].name);
        printf("Ogrenci %d Sinav 1 Notu: ", i + 1);
        scanf("%f", &students[i].exam1);
        printf("Ogrenci %d Sinav 2 Notu: ", i + 1);
        scanf("%f", &students[i].exam2);
        students[i].final_grade = (students[i].exam1 + students[i].exam2) / 2.0;
        printf("\n");
    }
    printf("\n--- Tum Ogrenci Bilgileri ---\n");
    printf("ID\tAd\tSinav1\tSinav2\tFinal Notu\n");
    for (i = 0; i < 3; i++) {
        printf("%d\t%s\t%.2f\t%.2f\t%.2f\n",
               students[i].id,
               students[i].name,
               students[i].exam1,
               students[i].exam2,
               students[i].final_grade);
    }
    float max_grade = -1.0;
    int top_student_index = -1;
    for (i = 0; i < 3; i++) {
        if (students[i].final_grade > max_grade) {
            max_grade = students[i].final_grade;
            top_student_index = i;
        }
    }
    printf("\n--- En Yuksek Final Notu Alan Ogrenci ---\n");
    if (top_student_index != -1) {
        printf("ID: %d\n", students[top_student_index].id);
        printf("Ad: %s\n", students[top_student_index].name);
        printf("Sinav 1 Notu: %.2f\n", students[top_student_index].exam1);
        printf("Sinav 2 Notu: %.2f\n", students[top_student_index].exam2);
        printf("Final Notu: %.2f\n", students[top_student_index].final_grade);
    } else {
        printf("Ogrenci bulunamadi veya notlar gecersiz.\n");
    }
    return 0;
}