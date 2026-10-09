#include <stdio.h>
#include <string.h>
#define MAX_PRODUCTS 5
typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
} Product;
int main() {
    Product inventory[MAX_PRODUCTS] = {
        {101, "Laptop", 1200.00, 5},
        {102, "Mouse", 25.50, 20},
        {103, "Keyboard", 75.00, 10},
        {104, "Monitor", 300.00, 7},
        {105, "Webcam", 50.00, 15}
    };
    float totalInventoryValue = 0.0;
    int maxQuantity = -1;
    char productWithMaxQuantity[50];
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        totalInventoryValue += inventory[i].price * inventory[i].quantity;
        if (inventory[i].quantity > maxQuantity) {
            maxQuantity = inventory[i].quantity;
            strcpy(productWithMaxQuantity, inventory[i].name);
        }
    }
    printf("Total Inventory Value: %.2f\n", totalInventoryValue);
    printf("Product with Highest Quantity: %s\n", productWithMaxQuantity);
    return 0;
}