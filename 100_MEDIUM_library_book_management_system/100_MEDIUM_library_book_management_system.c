#include <stdio.h>
#include <string.h>
#define MAX_BOOKS 50
#define MAX_TITLE_LEN 50
#define MAX_AUTHOR_LEN 30
#define FILENAME "library.dat"
typedef struct {
    int id;
    char title[MAX_TITLE_LEN];
    char author[MAX_AUTHOR_LEN];
} Book;
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void add_book() {
    Book books[MAX_BOOKS];
    int book_count = 0;
    FILE *fp = fopen(FILENAME, "rb");
    if (fp != NULL) {
        while (fread(&books[book_count], sizeof(Book), 1, fp) == 1 && book_count < MAX_BOOKS) {
            book_count++;
        }
        fclose(fp);
    }
    if (book_count >= MAX_BOOKS) {
        printf("Kutuphane dolu, yeni kitap eklenemez.\n");
        return;
    }
    Book new_book;
    printf("Yeni kitap ekle:\n");
    printf("Kitap ID: ");
    if (scanf("%d", &new_book.id) != 1) {
        printf("Gecersiz ID girisi.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
    printf("Baslik (maks %d karakter): ", MAX_TITLE_LEN - 1);
    fgets(new_book.title, MAX_TITLE_LEN, stdin);
    new_book.title[strcspn(new_book.title, "\n")] = 0;
    printf("Yazar (maks %d karakter): ", MAX_AUTHOR_LEN - 1);
    fgets(new_book.author, MAX_AUTHOR_LEN, stdin);
    new_book.author[strcspn(new_book.author, "\n")] = 0;
    books[book_count] = new_book;
    book_count++;
    fp = fopen(FILENAME, "wb");
    if (fp == NULL) {
        printf("Dosya yazma hatasi!\n");
        return;
    }
    fwrite(books, sizeof(Book), book_count, fp);
    fclose(fp);
    printf("Kitap basariyla eklendi.\n");
}
void list_books() {
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("Henuz kitap kaydi yok.\n");
        return;
    }
    Book current_book;
    int found_books = 0;
    printf("--- KUTUPHANEDAKI KITAPLAR ---\n");
    while (fread(&current_book, sizeof(Book), 1, fp) == 1) {
        printf("ID: %d, Baslik: %s, Yazar: %s\n", current_book.id, current_book.title, current_book.author);
        found_books++;
    }
    fclose(fp);
    if (found_books == 0) {
        printf("Kutuphanede hic kitap yok.\n");
    }
    printf("------------------------------\n");
}
int main() {
    int choice;
    do {
        printf("\nKutuphane Yonetim Sistemi\n");
        printf("1. Kitap Ekle\n");
        printf("2. Kitaplari Listele\n");
        printf("3. Cikis\n");
        printf("Seciminizi yapin: ");
        if (scanf("%d", &choice) != 1) {
            printf("Gecersiz giris. Lutfen bir sayi girin.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        switch (choice) {
            case 1:
                add_book();
                break;
            case 2:
                list_books();
                break;
            case 3:
                printf("Cikis yapiliyor...\n");
                break;
            default:
                printf("Gecersiz secim, lutfen tekrar deneyin.\n");
                break;
        }
    } while (choice != 3);
    return 0;
}