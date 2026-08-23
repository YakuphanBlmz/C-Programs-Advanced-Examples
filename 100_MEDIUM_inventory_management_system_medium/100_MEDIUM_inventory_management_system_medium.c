#include <stdio.h>
#include <string.h>
#define MAX_PRODUCTS 5
#define NAME_LENGTH 50
#define INVENTORY_FILE "inventory.dat"
typedef struct {
    int productId;
    char productName[NAME_LENGTH];
    float price;
    int stock;
} Product;
int main() {
    Product inventory[MAX_PRODUCTS];
    Product loadedInventory[MAX_PRODUCTS];
    int i;
    float totalValue = 0.0;
    float highestPrice = 0.0;
    int highestPriceIndex = -1;
    FILE *filePtr;
    inventory[0].productId = 101;
    strcpy(inventory[0].productName, "Laptop");
    inventory[0].price = 1200.00;
    inventory[0].stock = 5;
    inventory[1].productId = 102;
    strcpy(inventory[1].productName, "Mouse");
    inventory[1].price = 25.50;
    inventory[1].stock = 50;
    inventory[2].productId = 103;
    strcpy(inventory[2].productName, "Keyboard");
    inventory[2].price = 75.00;
    inventory[2].stock = 30;
    inventory[3].productId = 104;
    strcpy(inventory[3].productName, "Monitor");
    inventory[3].price = 300.00;
    inventory[3].stock = 10;
    inventory[4].productId = 105;
    strcpy(inventory[4].productName, "Webcam");
    inventory[4].price = 50.00;
    inventory[4].stock = 20;
    printf("Initial Inventory Data:\n");
    for (i = 0; i < MAX_PRODUCTS; i++) {
        printf("ID: %d, Name: %s, Price: %.2f, Stock: %d\n",
               inventory[i].productId,
               inventory[i].productName,
               inventory[i].price,
               inventory[i].stock);
    }
    printf("\n");
    for (i = 0; i < MAX_PRODUCTS; i++) {
        totalValue += inventory[i].price * inventory[i].stock;
    }
    printf("Total inventory value: %.2f\n\n", totalValue);
    for (i = 0; i < MAX_PRODUCTS; i++) {
        if (inventory[i].price > highestPrice) {
            highestPrice = inventory[i].price;
            highestPriceIndex = i;
        }
    }
    printf("Product with highest unit price:\n");
    if (highestPriceIndex != -1) {
        printf("ID: %d, Name: %s, Price: %.2f, Stock: %d\n\n",
               inventory[highestPriceIndex].productId,
               inventory[highestPriceIndex].productName,
               inventory[highestPriceIndex].price,
               inventory[highestPriceIndex].stock);
    } else {
        printf("No products found.\n\n");
    }
    filePtr = fopen(INVENTORY_FILE, "wb");
    if (filePtr == NULL) {
        printf("Error opening file for writing!\n");
        return 1;
    }
    fwrite(inventory, sizeof(Product), MAX_PRODUCTS, filePtr);
    fclose(filePtr);
    printf("Inventory saved to %s successfully.\n\n", INVENTORY_FILE);
    filePtr = fopen(INVENTORY_FILE, "rb");
    if (filePtr == NULL) {
        printf("Error opening file for reading!\n");
        return 1;
    }
    fread(loadedInventory, sizeof(Product), MAX_PRODUCTS, filePtr);
    fclose(filePtr);
    printf("Inventory loaded from %s:\n", INVENTORY_FILE);
    for (i = 0; i < MAX_PRODUCTS; i++) {
        printf("ID: %d, Name: %s, Price: %.2f, Stock: %d\n",
               loadedInventory[i].productId,
               loadedInventory[i].productName,
               loadedInventory[i].price,
               loadedInventory[i].stock);
    }
    return 0;
}