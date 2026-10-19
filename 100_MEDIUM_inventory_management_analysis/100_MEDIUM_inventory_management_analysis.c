#include <stdio.h>
#include <string.h>
typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
} Product;
int main() {
    Product inventory[5];
    inventory[0].id = 101;
    strcpy(inventory[0].name, "Laptop");
    inventory[0].price = 1200.50;
    inventory[0].quantity = 3;
    inventory[1].id = 102;
    strcpy(inventory[1].name, "Mouse");
    inventory[1].price = 25.00;
    inventory[1].quantity = 10;
    inventory[2].id = 103;
    strcpy(inventory[2].name, "Keyboard");
    inventory[2].price = 75.25;
    inventory[2].quantity = 5;
    inventory[3].id = 104;
    strcpy(inventory[3].name, "Monitor");
    inventory[3].price = 300.00;
    inventory[3].quantity = 2;
    inventory[4].id = 105;
    strcpy(inventory[4].name, "Webcam");
    inventory[4].price = 50.75;
    inventory[4].quantity = 8;
    float totalInventoryValue = 0.0;
    int highestPriceProductIndex = 0;
    int i;
    for (i = 0; i < 5; i++) {
        totalInventoryValue += inventory[i].price * inventory[i].quantity;
        if (inventory[i].price > inventory[highestPriceProductIndex].price) {
            highestPriceProductIndex = i;
        }
    }
    printf("Total Inventory Value: %.2f\n", totalInventoryValue);
    printf("Product with Highest Individual Price:\n");
    printf("ID: %d\n", inventory[highestPriceProductIndex].id);
    printf("Name: %s\n", inventory[highestPriceProductIndex].name);
    printf("Price: %.2f\n", inventory[highestPriceProductIndex].price);
    printf("Quantity: %d\n", inventory[highestPriceProductIndex].quantity);
    return 0;
}