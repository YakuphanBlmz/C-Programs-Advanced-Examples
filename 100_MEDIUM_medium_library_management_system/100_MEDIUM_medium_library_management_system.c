#include <stdio.h>
#include <string.h>
#define MAX_TITLE_LENGTH 50
#define MAX_AUTHOR_LENGTH 30
#define MAX_BOOKS 5
typedef struct {
    int id;
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    float price;
} Book;
void addBook(Book library[], int *bookCount, int id, const char title[], const char author[], float price) {
    if (*bookCount < MAX_BOOKS) {
        library[*bookCount].id = id;
        strncpy(library[*bookCount].title, title, MAX_TITLE_LENGTH - 1);
        library[*bookCount].title[MAX_TITLE_LENGTH - 1] = '\0';
        strncpy(library[*bookCount].author, author, MAX_AUTHOR_LENGTH - 1);
        library[*bookCount].author[MAX_AUTHOR_LENGTH - 1] = '\0';
        library[*bookCount].price = price;
        (*bookCount)++;
        printf("Book added: %s\n", title);
    } else {
        printf("Library is full. Cannot add more books.\n");
    }
}
void listAllBooks(const Book library[], int bookCount) {
    int i;
    if (bookCount == 0) {
        printf("The library is empty.\n");
        return;
    }
    printf("\n--- All Books in Library ---\n");
    for (i = 0; i < bookCount; i++) {
        printf("ID: %d, Title: %s, Author: %s, Price: %.2f\n",
               library[i].id, library[i].title, library[i].author, library[i].price);
    }
    printf("----------------------------\n");
}
void findBookById(const Book library[], int bookCount, int searchId) {
    int i;
    for (i = 0; i < bookCount; i++) {
        if (library[i].id == searchId) {
            printf("\nBook found (ID: %d):\n", searchId);
            printf("Title: %s\n", library[i].title);
            printf("Author: %s\n", library[i].author);
            printf("Price: %.2f\n", library[i].price);
            return;
        }
    }
    printf("\nBook with ID %d not found.\n", searchId);
}
int main() {
    Book library[MAX_BOOKS];
    int bookCount = 0;
    addBook(library, &bookCount, 101, "C Programming Absolute Beginner's Guide", "Greg Perry", 29.99);
    addBook(library, &bookCount, 102, "The C Programming Language", "Brian W. Kernighan", 45.50);
    addBook(library, &bookCount, 103, "Data Structures and Algorithms in C", "Michael T. Goodrich", 59.75);
    addBook(library, &bookCount, 104, "Effective C", "Robert C. Seacord", 35.00);
    addBook(library, &bookCount, 105, "Learn C The Hard Way", "Zed A. Shaw", 25.00);
    addBook(library, &bookCount, 106, "Extra Book", "Someone", 10.00);
    listAllBooks(library, bookCount);
    findBookById(library, bookCount, 102);
    findBookById(library, bookCount, 100);
    return 0;
}