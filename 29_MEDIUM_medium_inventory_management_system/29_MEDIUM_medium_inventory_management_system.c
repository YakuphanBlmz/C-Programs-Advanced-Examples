#include <stdio.h>
#define MAX_PRODUCTS 10
#define NAME_LEN 50
typedef struct {
    int id;
    char name[NAME_LEN];
    int quantity;
} Product;
Product inventory[MAX_PRODUCTS];
int productCount = 0;
void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        printf("Inventory is full. Cannot add more products.\n");
        return;
    }
    int newId;
    printf("Enter product ID: ");
    scanf("%d", &newId);
    for (int i = 0; i < productCount; i++) {
        if (inventory[i].id == newId) {
            printf("Product with ID %d already exists. Please use a unique ID.\n", newId);
            return;
        }
    }
    inventory[productCount].id = newId;
    printf("Enter product name (single word): ");
    scanf("%49s", inventory[productCount].name); 
    printf("Enter quantity: ");
    scanf("%d", &inventory[productCount].quantity);
    productCount++;
    printf("Product added successfully!\n");
}
void listProducts() {
    if (productCount == 0) {
        printf("Inventory is empty.\n");
        return;
    }
    printf("\n--- Current Inventory ---\n");
    printf("%-5s %-20s %-10s\n", "ID", "Name", "Quantity");
    printf("----------------------------------\n");
    for (int i = 0; i < productCount; i++) {
        printf("%-5d %-20s %-10d\n", inventory[i].id, inventory[i].name, inventory[i].quantity);
    }
    printf("----------------------------------\n");
}
void findProduct() {
    if (productCount == 0) {
        printf("Inventory is empty. No products to search.\n");
        return;
    }
    int searchId;
    printf("Enter product ID to search: ");
    scanf("%d", &searchId);
    int found = 0;
    for (int i = 0; i < productCount; i++) {
        if (inventory[i].id == searchId) {
            printf("\nProduct Found:\n");
            printf("ID: %d\n", inventory[i].id);
            printf("Name: %s\n", inventory[i].name);
            printf("Quantity: %d\n", inventory[i].quantity);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Product with ID %d not found.\n", searchId);
    }
}
int main() {
    int choice;
    do {
        printf("\n--- Inventory Management System ---\n");
        printf("1. Add Product\n");
        printf("2. List Products\n");
        printf("3. Find Product by ID\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                listProducts();
                break;
            case 3:
                findProduct();
                break;
            case 4:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
    return 0;
}