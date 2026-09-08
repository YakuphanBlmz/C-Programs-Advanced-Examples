#include <stdio.h>
#include <string.h>
#define MAX_NAME_LEN 50
#define FILENAME "inventory.bin"
typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int quantity;
    float price;
} Product;
void addProduct();
void listProducts();
int main() {
    int choice;
    do {
        printf("\n--- Inventory Management ---\n");
        printf("1. Add New Product\n");
        printf("2. List All Products\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                listProducts();
                break;
            case 0:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
    return 0;
}
void addProduct() {
    FILE *fp;
    Product newProduct;
    fp = fopen(FILENAME, "ab");
    if (fp == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    printf("\nEnter Product ID: ");
    scanf("%d", &newProduct.id);
    printf("Enter Product Name (max %d chars): ", MAX_NAME_LEN - 1);
    scanf("%s", newProduct.name); 
    printf("Enter Quantity: ");
    scanf("%d", &newProduct.quantity);
    printf("Enter Price: ");
    scanf("%f", &newProduct.price);
    fwrite(&newProduct, sizeof(Product), 1, fp);
    fclose(fp);
    printf("Product added successfully!\n");
}
void listProducts() {
    FILE *fp;
    Product currentProduct;
    int count = 0;
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("Error opening file for reading or file does not exist.\n");
        return;
    }
    printf("\n--- All Products ---\n");
    printf("%-5s %-20s %-10s %-10s\n", "ID", "Name", "Quantity", "Price");
    printf("--------------------------------------------------\n");
    while (fread(&currentProduct, sizeof(Product), 1, fp) == 1) {
        printf("%-5d %-20s %-10d %-10.2f\n", 
               currentProduct.id, 
               currentProduct.name, 
               currentProduct.quantity, 
               currentProduct.price);
        count++;
    }
    if (count == 0) {
        printf("No products found in inventory.\n");
    }
    printf("--------------------------------------------------\n");
    fclose(fp);
}