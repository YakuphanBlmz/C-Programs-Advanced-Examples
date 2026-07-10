#include <stdio.h>
#include <string.h>
#define MAX_BOOKS 5
#define MAX_TITLE_LEN 50
#define MAX_AUTHOR_LEN 30
typedef struct {
    int id;
    char title[MAX_TITLE_LEN];
    char author[MAX_AUTHOR_LEN];
    int is_available; 
} Book;
void displayAvailableBooks(Book books[], int count) {
    printf("--- Available Books ---\n");
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (books[i].is_available == 0) {
            printf("ID: %d, Title: %s, Author: %s\n", books[i].id, books[i].title, books[i].author);
            found = 1;
        }
    }
    if (!found) {
        printf("No books are currently available.\n");
    }
    printf("------------------------\n");
}
void borrowBook(Book books[], int count, int bookId) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (books[i].id == bookId) {
            found = 1;
            if (books[i].is_available == 0) {
                books[i].is_available = 1;
                printf("Book '%s' (ID: %d) has been successfully borrowed.\n", books[i].title, bookId);
            } else {
                printf("Book '%s' (ID: %d) is already borrowed.\n", books[i].title, bookId);
            }
            break;
        }
    }
    if (!found) {
        printf("Book with ID %d not found.\n", bookId);
    }
}
int main() {
    Book library[MAX_BOOKS];
    library[0].id = 101;
    strcpy(library[0].title, "The Great Adventures");
    strcpy(library[0].author, "Jane Doe");
    library[0].is_available = 0;
    library[1].id = 102;
    strcpy(library[1].title, "Mystery of the Old House");
    strcpy(library[1].author, "John Smith");
    library[1].is_available = 0;
    library[2].id = 103;
    strcpy(library[2].title, "Coding in C");
    strcpy(library[2].author, "Alice Wonderland");
    library[2].is_available = 1;
    library[3].id = 104;
    strcpy(library[3].title, "Data Structures Intro");
    strcpy(library[3].author, "Bob The Builder");
    library[3].is_available = 0;
    library[4].id = 105;
    strcpy(library[4].title, "Algorithms Illustrated");
    strcpy(library[4].author, "Charlie Chaplin");
    library[4].is_available = 0;
    displayAvailableBooks(library, MAX_BOOKS);
    int borrowId1 = 102;
    printf("\nAttempting to borrow book with ID: %d\n", borrowId1);
    borrowBook(library, MAX_BOOKS, borrowId1);
    displayAvailableBooks(library, MAX_BOOKS);
    int borrowId2 = 103;
    printf("\nAttempting to borrow book with ID: %d\n", borrowId2);
    borrowBook(library, MAX_BOOKS, borrowId2);
    displayAvailableBooks(library, MAX_BOOKS);
    int borrowId3 = 999;
    printf("\nAttempting to borrow book with ID: %d\n", borrowId3);
    borrowBook(library, MAX_BOOKS, borrowId3);
    displayAvailableBooks(library, MAX_BOOKS);
    int borrowId4 = 101;
    printf("\nAttempting to borrow book with ID: %d\n", borrowId4);
    borrowBook(library, MAX_BOOKS, borrowId4);
    displayAvailableBooks(library, MAX_BOOKS);
    return 0;
}