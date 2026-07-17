#include <stdio.h>
typedef struct {
    int id;
    char name[30];
    float price;
    int stock;
} Product;
int main() {
    FILE *file;
    Product inventory[3] = {
        {101, "Laptop", 1200.00, 10},
        {102, "Mouse", 25.50, 50},
        {103, "Keyboard", 75.00, 30}
    };
    int numProducts = 3;
    int i;
    int targetProductId = 102;
    int newStockValue = 40;
    file = fopen("inventory.dat", "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }
    fwrite(inventory, sizeof(Product), numProducts, file);
    fclose(file);
    printf("Initial inventory written to inventory.dat\n\n");
    Product updatedInventory[3];
    file = fopen("inventory.dat", "rb");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return 1;
    }
    fread(updatedInventory, sizeof(Product), numProducts, file);
    fclose(file);
    for (i = 0; i < numProducts; i++) {
        if (updatedInventory[i].id == targetProductId) {
            updatedInventory[i].stock = newStockValue;
            printf("Product ID %d stock updated to %d\n\n", targetProductId, newStockValue);
            break;
        }
    }
    file = fopen("inventory.dat", "wb");
    if (file == NULL) {
        printf("Error opening file for writing updated data.\n");
        return 1;
    }
    fwrite(updatedInventory, sizeof(Product), numProducts, file);
    fclose(file);
    printf("Updated inventory written back to inventory.dat\n\n");
    printf("Final Inventory Details:\n");
    Product finalInventory[3];
    file = fopen("inventory.dat", "rb");
    if (file == NULL) {
        printf("Error opening file for final reading.\n");
        return 1;
    }
    fread(finalInventory, sizeof(Product), numProducts, file);
    fclose(file);
    for (i = 0; i < numProducts; i++) {
        printf("ID: %d, Name: %s, Price: %.2f, Stock: %d\n",
               finalInventory[i].id, finalInventory[i].name, finalInventory[i].price, finalInventory[i].stock);
    }
    printf("\n");
    return 0;
}