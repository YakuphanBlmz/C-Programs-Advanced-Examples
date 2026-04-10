#include <stdio.h>
#define MAX_PRODUCTS 10
#define FILENAME "inventory.dat"
typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
} Product;
int addProduct(Product inventory[], int currentCount) {
    if (currentCount >= MAX_PRODUCTS) {
        printf("Inventory is full. Cannot add more products.\n");
        return currentCount;
    }
    printf("Enter Product ID: ");
    scanf("%d", &inventory[currentCount].id);
    printf("Enter Product Name (single word): ");
    scanf("%s", inventory[currentCount].name);
    printf("Enter Product Price: ");
    scanf("%f", &inventory[currentCount].price);
    printf("Enter Product Quantity: ");
    scanf("%d", &inventory[currentCount].quantity);
    printf("Product added successfully.\n");
    return currentCount + 1;
}
void listProducts(Product inventory[], int count) {
    if (count == 0) {
        printf("Inventory is empty.\n");
        return;
    }
    printf("\n--- Current Inventory ---\n");
    printf("ID\tName\tPrice\tQuantity\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t%.2f\t%d\n", inventory[i].id, inventory[i].name, inventory[i].price, inventory[i].quantity);
    }
    printf("-------------------------\n");
}
void saveInventory(Product inventory[], int count) {
    FILE *fp = fopen(FILENAME, "wb");
    if (fp == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, fp);
    fwrite(inventory, sizeof(Product), count, fp);
    fclose(fp);
    printf("Inventory saved to %s successfully.\n", FILENAME);
}
int loadInventory(Product inventory[]) {
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("No existing inventory file found or error opening. Starting with empty inventory.\n");
        return 0;
    }
    int loadedCount = 0;
    fread(&loadedCount, sizeof(int), 1, fp);
    if (loadedCount > MAX_PRODUCTS) {
        printf("Warning: File contains %d products, but inventory capacity is %d. Loading up to capacity.\n", loadedCount, MAX_PRODUCTS);
        fread(inventory, sizeof(Product), MAX_PRODUCTS, fp);
        fclose(fp);
        return MAX_PRODUCTS;
    } else {
        fread(inventory, sizeof(Product), loadedCount, fp);
        fclose(fp);
        printf("Inventory loaded from %s successfully. Total %d products.\n", FILENAME, loadedCount);
        return loadedCount;
    }
}
int main() {
    Product inventory[MAX_PRODUCTS];
    int productCount = 0;
    int choice;
    productCount = loadInventory(inventory);
    do {
        printf("\n--- Inventory Management System ---\n");
        printf("1. Add Product\n");
        printf("2. List Products\n");
        printf("3. Save Inventory\n");
        printf("4. Load Inventory\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                productCount = addProduct(inventory, productCount);
                break;
            case 2:
                listProducts(inventory, productCount);
                break;
            case 3:
                saveInventory(inventory, productCount);
                break;
            case 4:
                productCount = loadInventory(inventory);
                break;
            case 5:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
    return 0;
}