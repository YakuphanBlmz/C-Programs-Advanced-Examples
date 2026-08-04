#include <stdio.h>
#include <string.h>
#define MAX_PRODUCTS 10
typedef struct {
    int productId;
    char productName[50];
    double price;
} Product;
void printAllProducts(Product products[], int count) {
    printf("--- Current Inventory ---\n");
    if (count == 0) {
        printf("Inventory is empty.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        printf("ID: %d, Name: %s, Price: %.2f\n", products[i].productId, products[i].productName, products[i].price);
    }
    printf("-------------------------\n\n");
}
Product findMostExpensiveProduct(Product products[], int count) {
    Product mostExpensive = products[0];
    for (int i = 1; i < count; i++) {
        if (products[i].price > mostExpensive.price) {
            mostExpensive = products[i];
        }
    }
    return mostExpensive;
}
int main() {
    Product inventory[MAX_PRODUCTS];
    int productCount = 0;
    if (productCount < MAX_PRODUCTS) {
        inventory[productCount].productId = 101;
        strcpy(inventory[productCount].productName, "Laptop");
        inventory[productCount].price = 1200.50;
        productCount++;
    }
    if (productCount < MAX_PRODUCTS) {
        inventory[productCount].productId = 102;
        strcpy(inventory[productCount].productName, "Mouse");
        inventory[productCount].price = 25.99;
        productCount++;
    }
    if (productCount < MAX_PRODUCTS) {
        inventory[productCount].productId = 103;
        strcpy(inventory[productCount].productName, "Keyboard");
        inventory[productCount].price = 75.00;
        productCount++;
    }
    if (productCount < MAX_PRODUCTS) {
        inventory[productCount].productId = 104;
        strcpy(inventory[productCount].productName, "Monitor");
        inventory[productCount].price = 350.25;
        productCount++;
    }
    printAllProducts(inventory, productCount);
    if (productCount > 0) {
        Product expensiveItem = findMostExpensiveProduct(inventory, productCount);
        printf("Most expensive product:\n");
        printf("ID: %d, Name: %s, Price: %.2f\n", expensiveItem.productId, expensiveItem.productName, expensiveItem.price);
    } else {
        printf("Cannot find most expensive product, inventory is empty.\n");
    }
    return 0;
}