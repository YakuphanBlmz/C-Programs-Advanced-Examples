#include <stdio.h>
#include <string.h>
#define MAX_TITLE_LEN 50
#define MAX_AUTHOR_LEN 30
#define MAX_BOOKS 3
typedef struct {
    char title[MAX_TITLE_LEN];
    char author[MAX_AUTHOR_LEN];
    int publication_year;
    int stock;
} Book;
void updateBookStock(Book library[], int numBooks, const char* targetTitle, int newStock) {
    int found = 0;
    for (int i = 0; i < numBooks; i++) {
        if (strcmp(library[i].title, targetTitle) == 0) {
            library[i].stock = newStock;
            found = 1;
            break;
        }
    }
    if (found) {
        printf("Kitap '%s' stoku %d olarak güncellendi.\n", targetTitle, newStock);
    } else {
        printf("Kitap '%s' bulunamadı.\n", targetTitle);
    }
}
void printLibrary(Book library[], int numBooks) {
    printf("\n--- Kütüphane Koleksiyonu ---\n");
    for (int i = 0; i < numBooks; i++) {
        printf("Başlık: %s, Yazar: %s, Yıl: %d, Stok: %d\n",
               library[i].title,
               library[i].author,
               library[i].publication_year,
               library[i].stock);
    }
    printf("------------------------------\n");
}
int main() {
    Book myLibrary[MAX_BOOKS];
    strcpy(myLibrary[0].title, "C Programlama");
    strcpy(myLibrary[0].author, "Ali Veli");
    myLibrary[0].publication_year = 2020;
    myLibrary[0].stock = 5;
    strcpy(myLibrary[1].title, "Veri Yapıları");
    strcpy(myLibrary[1].author, "Can Deniz");
    myLibrary[1].publication_year = 2018;
    myLibrary[1].stock = 3;
    strcpy(myLibrary[2].title, "Algoritma Tasarımı");
    strcpy(myLibrary[2].author, "Ece Irmak");
    myLibrary[2].publication_year = 2022;
    myLibrary[2].stock = 7;
    printLibrary(myLibrary, MAX_BOOKS);
    updateBookStock(myLibrary, MAX_BOOKS, "C Programlama", 8);
    updateBookStock(myLibrary, MAX_BOOKS, "Python Giriş", 2);
    printLibrary(myLibrary, MAX_BOOKS);
    return 0;
}