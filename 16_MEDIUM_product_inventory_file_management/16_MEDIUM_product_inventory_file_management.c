#include <stdio.h>
#include <string.h>
#define MAX_PRODUCTS 10
#define FILENAME "inventory.dat"
typedef struct {
    int id;
    char name[50];
    int quantity;
} Product;
void addProduct(Product inventory[], int *count, int id, const char *name, int quantity) {
    if (*count < MAX_PRODUCTS) {
        inventory[*count].id = id;
        strncpy(inventory[*count].name, name, sizeof(inventory[*count].name) - 1);
        inventory[*count].name[sizeof(inventory[*count].name) - 1] = '\0';
        inventory[*count].quantity = quantity;
        (*count)++;
    } else {
        printf("Inventory is full. Cannot add more products.\n");
    }
}
void displayInventory(const Product inventory[], int count) {
    printf("\n--- Current Inventory ---\n");
    if (count == 0) {
        printf("Inventory is empty.\n");
        return;
    }
    printf("%-5s %-20s %-10s\n", "ID", "Name", "Quantity");
    printf("----------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %-10d\n", inventory[i].id, inventory[i].name, inventory[i].quantity);
    }
    printf("----------------------------------\n");
}
void saveInventory(const Product inventory[], int count, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error: Could not open file %s for writing.\n", filename);
        return;
    }
    fwrite(&count, sizeof(int), 1, file);
    fwrite(inventory, sizeof(Product), count, file);
    fclose(file);
    printf("Inventory saved to %s successfully.\n", filename);
}
void loadInventory(Product inventory[], int *count, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error: Could not open file %s for reading. Initializing empty inventory.\n", filename);
        *count = 0;
        return;
    }
    int loadedCount = 0;
    fread(&loadedCount, sizeof(int), 1, file);
    if (loadedCount > MAX_PRODUCTS) {
        printf("Warning: File contains more products (%d) than inventory capacity (%d). Loading only up to capacity.\n", loadedCount, MAX_PRODUCTS);
        loadedCount = MAX_PRODUCTS;
    } else if (loadedCount < 0) {
        printf("Warning: Invalid product count (%d) in file. Initializing empty inventory.\n", loadedCount);
        loadedCount = 0;
    }
    fread(inventory, sizeof(Product), loadedCount, file);
    *count = loadedCount;
    fclose(file);
    printf("Inventory loaded from %s successfully. %d products loaded.\n", filename, *count);
}
int main() {
    Product inventory[MAX_PRODUCTS];
    int currentProductCount = 0;
    loadInventory(inventory, &currentProductCount, FILENAME);
    if (currentProductCount == 0) {
        addProduct(inventory, &currentProductCount, 101, "Laptop", 10);
        addProduct(inventory, &currentProductCount, 205, "Mouse", 50);
        addProduct(inventory, &currentProductCount, 310, "Keyboard", 25);
    } else if (currentProductCount < MAX_PRODUCTS) {
        printf("\nAdding one more product to existing inventory.\n");
        addProduct(inventory, &currentProductCount, 401, "Monitor", 15);
    }
    displayInventory(inventory, currentProductCount);
    saveInventory(inventory, currentProductCount, FILENAME);
    Product newInventory[MAX_PRODUCTS];
    int newCount = 0;
    printf("\n--- Demonstrating Load into New Inventory After Save ---\n");
    loadInventory(newInventory, &newCount, FILENAME);
    displayInventory(newInventory, newCount);
    return 0;
}