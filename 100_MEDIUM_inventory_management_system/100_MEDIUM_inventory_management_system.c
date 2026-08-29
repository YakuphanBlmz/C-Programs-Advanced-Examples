#include <stdio.h>
#include <string.h>
typedef struct {
    int id;
    char name[50];
    int quantity;
    float price;
} Product;
void addProduct() {
    FILE *file = fopen("inventory.txt", "a");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    Product newProduct;
    printf("Enter Product ID: ");
    scanf("%d", &newProduct.id);
    while (getchar() != '\n');
    printf("Enter Product Name (max 49 chars): ");
    fgets(newProduct.name, sizeof(newProduct.name), stdin);
    newProduct.name[strcspn(newProduct.name, "\n")] = 0;
    printf("Enter Product Quantity: ");
    scanf("%d", &newProduct.quantity);
    while (getchar() != '\n');
    printf("Enter Product Price: ");
    scanf("%f", &newProduct.price);
    while (getchar() != '\n');
    fprintf(file, "%d,%s,%d,%.2f\n", newProduct.id, newProduct.name, newProduct.quantity, newProduct.price);
    fclose(file);
    printf("Product added successfully.\n\n");
}
void displayProducts() {
    FILE *file = fopen("inventory.txt", "r");
    if (file == NULL) {
        printf("Inventory file not found or empty.\n\n");
        return;
    }
    Product currentProduct;
    char line[256];
    printf("--- Current Inventory ---\n");
    printf("%-5s %-20s %-10s %-10s\n", "ID", "Name", "Quantity", "Price");
    printf("--------------------------------------------------\n");
    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%d,%49[^,],%d,%f",
               &currentProduct.id,
               currentProduct.name,
               &currentProduct.quantity,
               &currentProduct.price);
        printf("%-5d %-20s %-10d %-10.2f\n",
               currentProduct.id,
               currentProduct.name,
               currentProduct.quantity,
               currentProduct.price);
    }
    printf("--------------------------------------------------\n\n");
    fclose(file);
}
void calculateTotalValue() {
    FILE *file = fopen("inventory.txt", "r");
    if (file == NULL) {
        printf("Inventory file not found or empty.\n\n");
        return;
    }
    Product currentProduct;
    char line[256];
    float totalValue = 0.0;
    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%d,%49[^,],%d,%f",
               &currentProduct.id,
               currentProduct.name,
               &currentProduct.quantity,
               &currentProduct.price);
        totalValue += (float)currentProduct.quantity * currentProduct.price;
    }
    fclose(file);
    printf("Total Inventory Value: %.2f\n\n", totalValue);
}
int main() {
    int choice;
    do {
        printf("--- Inventory Management System ---\n");
        printf("1. Add New Product\n");
        printf("2. Display All Products\n");
        printf("3. Calculate Total Inventory Value\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');
        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                displayProducts();
                break;
            case 3:
                calculateTotalValue();
                break;
            case 4:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n\n");
        }
    } while (choice != 4);
    return 0;
}