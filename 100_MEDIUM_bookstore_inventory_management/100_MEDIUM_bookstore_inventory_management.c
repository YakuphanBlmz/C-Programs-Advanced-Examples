#include <stdio.h>
#include <string.h>
#define MAX_BOOKS 10
typedef struct {
    char title[50];
    char author[50];
    int publicationYear;
    float price;
} Book;
Book inventory[MAX_BOOKS];
int bookCount = 0;
void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Inventory is full. Cannot add more books.\n");
        return;
    }
    Book newBook;
    printf("Enter book title: ");
    while (getchar() != '\n');
    fgets(newBook.title, sizeof(newBook.title), stdin);
    newBook.title[strcspn(newBook.title, "\n")] = 0;
    printf("Enter book author: ");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    newBook.author[strcspn(newBook.author, "\n")] = 0;
    printf("Enter publication year: ");
    scanf("%d", &newBook.publicationYear);
    printf("Enter price: ");
    scanf("%f", &newBook.price);
    inventory[bookCount] = newBook;
    bookCount++;
    printf("Book added successfully.\n");
}
void listBooks() {
    if (bookCount == 0) {
        printf("Inventory is empty.\n");
        return;
    }
    printf("\n--- Current Inventory ---\n");
    for (int i = 0; i < bookCount; i++) {
        printf("Book %d:\n", i + 1);
        printf("  Title: %s\n", inventory[i].title);
        printf("  Author: %s\n", inventory[i].author);
        printf("  Year: %d\n", inventory[i].publicationYear);
        printf("  Price: %.2f\n", inventory[i].price);
    }
    printf("-------------------------\n");
}
void findBook() {
    if (bookCount == 0) {
        printf("Inventory is empty. Cannot search.\n");
        return;
    }
    char searchTitle[50];
    printf("Enter title to search: ");
    while (getchar() != '\n');
    fgets(searchTitle, sizeof(searchTitle), stdin);
    searchTitle[strcspn(searchTitle, "\n")] = 0;
    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(inventory[i].title, searchTitle) == 0) {
            printf("\nBook Found:\n");
            printf("  Title: %s\n", inventory[i].title);
            printf("  Author: %s\n", inventory[i].author);
            printf("  Year: %d\n", inventory[i].publicationYear);
            printf("  Price: %.2f\n", inventory[i].price);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Book with title '%s' not found.\n", searchTitle);
    }
}
void calculateTotalValue() {
    if (bookCount == 0) {
        printf("Inventory is empty. Total value is 0.00.\n");
        return;
    }
    float totalValue = 0.0;
    for (int i = 0; i < bookCount; i++) {
        totalValue += inventory[i].price;
    }
    printf("Total value of all books in inventory: %.2f\n", totalValue);
}
int main() {
    int choice;
    do {
        printf("\n--- Bookstore Menu ---\n");
        printf("1. Add Book\n");
        printf("2. List All Books\n");
        printf("3. Find Book by Title\n");
        printf("4. Calculate Total Inventory Value\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                listBooks();
                break;
            case 3:
                findBook();
                break;
            case 4:
                calculateTotalValue();
                break;
            case 5:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 5);
    return 0;
}