#include <stdio.h>
#include <string.h>
typedef struct {
    int productID;
    char productName[50];
    float unitPrice;
    int stockQuantity;
} Product;
int main() {
    Product inventory[5];
    int numProducts = 0;
    inventory[numProducts].productID = 101;
    strcpy(inventory[numProducts].productName, "Laptop Pro");
    inventory[numProducts].unitPrice = 1200.50;
    inventory[numProducts].stockQuantity = 10;
    numProducts++;
    inventory[numProducts].productID = 102;
    strcpy(inventory[numProducts].productName, "Wireless Mouse");
    inventory[numProducts].unitPrice = 25.00;
    inventory[numProducts].stockQuantity = 50;
    numProducts++;
    inventory[numProducts].productID = 103;
    strcpy(inventory[numProducts].productName, "Mechanical Keyboard");
    inventory[numProducts].unitPrice = 99.99;
    inventory[numProducts].stockQuantity = 15;
    numProducts++;
    inventory[numProducts].productID = 104;
    strcpy(inventory[numProducts].productName, "Monitor 27-inch");
    inventory[numProducts].unitPrice = 350.75;
    inventory[numProducts].stockQuantity = 8;
    numProducts++;
    inventory[numProducts].productID = 105;
    strcpy(inventory[numProducts].productName, "Webcam HD");
    inventory[numProducts].unitPrice = 45.00;
    inventory[numProducts].stockQuantity = 25;
    numProducts++;
    float totalInventoryValue = 0.0;
    int i;
    for (i = 0; i < numProducts; i++) {
        totalInventoryValue += inventory[i].unitPrice * inventory[i].stockQuantity;
    }
    int maxStockQuantity = -1;
    int maxStockIndex = -1;
    for (i = 0; i < numProducts; i++) {
        if (inventory[i].stockQuantity > maxStockQuantity) {
            maxStockQuantity = inventory[i].stockQuantity;
            maxStockIndex = i;
        }
    }
    int minStockQuantity = 999999;
    int minStockIndex = -1;
    for (i = 0; i < numProducts; i++) {
        if (inventory[i].stockQuantity < minStockQuantity) {
            minStockQuantity = inventory[i].stockQuantity;
            minStockIndex = i;
        }
    }
    printf("Inventory Report:\n");
    printf("-------------------\n");
    printf("Total inventory value: %.2f TL\n", totalInventoryValue);
    if (maxStockIndex != -1) {
        printf("Product with highest stock: ID %d, Name %s, Quantity %d\n",
               inventory[maxStockIndex].productID,
               inventory[maxStockIndex].productName,
               inventory[maxStockIndex].stockQuantity);
    } else {
        printf("No products found to determine highest stock.\n");
    }
    if (minStockIndex != -1) {
        printf("Product with lowest stock: ID %d, Name %s, Quantity %d\n",
               inventory[minStockIndex].productID,
               inventory[minStockIndex].productName,
               inventory[minStockIndex].stockQuantity);
    } else {
        printf("No products found to determine lowest stock.\n");
    }
    return 0;
}