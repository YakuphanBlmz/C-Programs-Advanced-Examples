#include <stdio.h>
#include <string.h>
typedef struct {
    int id;
    char title[50];
    char author[50];
    int year;
} Book;
#define MAX_BOOKS 3
int main() {
    Book library_books[MAX_BOOKS];
    FILE *fp;
    int i;
    printf("--- Kitap Detaylarını Girin ---\n");
    for (i = 0; i < MAX_BOOKS; i++) {
        printf("\nKitap %d:\n", i + 1);
        printf("ID Girin: ");
        scanf("%d", &library_books[i].id);
        while (getchar() != '\n');
        printf("Başlık Girin: ");
        fgets(library_books[i].title, sizeof(library_books[i].title), stdin);
        library_books[i].title[strcspn(library_books[i].title, "\n")] = 0;
        printf("Yazar Girin: ");
        fgets(library_books[i].author, sizeof(library_books[i].author), stdin);
        library_books[i].author[strcspn(library_books[i].author, "\n")] = 0;
        printf("Yayın Yılı Girin: ");
        scanf("%d", &library_books[i].year);
        while (getchar() != '\n');
    }
    fp = fopen("books.dat", "wb");
    if (fp == NULL) {
        printf("Dosya yazmak için açılamadı!\n");
        return 1;
    }
    fwrite(library_books, sizeof(Book), MAX_BOOKS, fp);
    fclose(fp);
    printf("\n--- Kitap detayları books.dat dosyasına başarıyla yazıldı ---\n");
    printf("\n--- Kitapları Dosyadan Okuma ---\n");
    fp = fopen("books.dat", "rb");
    if (fp == NULL) {
        printf("Dosya okumak için açılamadı!\n");
        return 1;
    }
    Book read_book;
    int record_count = 0;
    while (fread(&read_book, sizeof(Book), 1, fp) == 1) {
        printf("\nKitap %d (Dosyadan Okundu):\n", record_count + 1);
        printf("ID: %d\n", read_book.id);
        printf("Başlık: %s\n", read_book.title);
        printf("Yazar: %s\n", read_book.author);
        printf("Yıl: %d\n", read_book.year);
        record_count++;
    }
    fclose(fp);
    printf("\n--- Tüm kitaplar books.dat dosyasından okundu ve görüntülendi ---\n");
    return 0;
}