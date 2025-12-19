#include <stdio.h>
#include <string.h>
typedef struct {
    int bookId;
    char title[100];
    char author[50];
    float price;
    int stock;
} Book;
void updateBookStock(Book books[], int size, int id, int newStock) {
    for (int i = 0; i < size; i++) {
        if (books[i].bookId == id) {
            books[i].stock = newStock;
            return;
        }
    }
}
float calculateTotalInventoryValue(Book books[], int size) {
    float totalValue = 0.0;
    for (int i = 0; i < size; i++) {
        totalValue += books[i].price * books[i].stock;
    }
    return totalValue;
}
int main() {
    Book library[3];
    library[0].bookId = 101;
    strcpy(library[0].title, "The C Programming Language");
    strcpy(library[0].author, "Kernighan & Ritchie");
    library[0].price = 35.50;
    library[0].stock = 10;
    library[1].bookId = 102;
    strcpy(library[1].title, "Clean Code");
    strcpy(library[1].author, "Robert C. Martin");
    library[1].price = 49.99;
    library[1].stock = 5;
    library[2].bookId = 103;
    strcpy(library[2].title, "Design Patterns");
    strcpy(library[2].author, "Erich Gamma");
    library[2].price = 55.00;
    library[2].stock = 7;
    int librarySize = 3;
    printf("Initial Total Inventory Value: %.2f\n", calculateTotalInventoryValue(library, librarySize));
    printf("Updating stock for book ID 102 to 8...\n");
    updateBookStock(library, librarySize, 102, 8);
    printf("Updating stock for book ID 101 to 7...\n");
    updateBookStock(library, librarySize, 101, 7);
    printf("New Total Inventory Value: %.2f\n", calculateTotalInventoryValue(library, librarySize));
    return 0;
}