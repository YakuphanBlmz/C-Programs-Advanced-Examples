#include <stdio.h>
#include <string.h>
#define MAX_PRODUCTS 3
#define MAX_NAME_LEN 50
typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int quantity;
    float price;
} Product;
int main() {
    Product inventory[MAX_PRODUCTS];
    int productCount = 0;
    char name1[MAX_NAME_LEN] = "Laptop";
    char name2[MAX_NAME_LEN] = "Mouse";
    char name3[MAX_NAME_LEN] = "Keyboard";
    char name4[MAX_NAME_LEN] = "Monitor";
    if (productCount < MAX_PRODUCTS) {
        inventory[productCount].id = 101;
        strcpy(inventory[productCount].name, name1);
        inventory[productCount].quantity = 10;
        inventory[productCount].price = 1200.50;
        printf("Product '%s' added successfully.\n", name1);
        productCount++;
    } else {
        printf("Inventory is full. Cannot add product '%s'.\n", name1);
    }
    if (productCount < MAX_PRODUCTS) {
        inventory[productCount].id = 102;
        strcpy(inventory[productCount].name, name2);
        inventory[productCount].quantity = 50;
        inventory[productCount].price = 25.00;
        printf("Product '%s' added successfully.\n", name2);
        productCount++;
    } else {
        printf("Inventory is full. Cannot add product '%s'.\n", name2);
    }
    if (productCount < MAX_PRODUCTS) {
        inventory[productCount].id = 103;
        strcpy(inventory[productCount].name, name3);
        inventory[productCount].quantity = 30;
        inventory[productCount].price = 75.99;
        printf("Product '%s' added successfully.\n", name3);
        productCount++;
    } else {
        printf("Inventory is full. Cannot add product '%s'.\n", name3);
    }
    if (productCount < MAX_PRODUCTS) {
        inventory[productCount].id = 104;
        strcpy(inventory[productCount].name, name4);
        inventory[productCount].quantity = 5;
        inventory[productCount].price = 300.00;
        printf("Inventory is full. Cannot add product '%s'.\n", name4);
    } else {
        printf("Inventory is full. Cannot add product '%s'.\n", name4);
    }
    if (productCount == 0) {
        printf("Inventory is empty.\n");
    } else {
        printf("\n--- Current Inventory ---\n");
        printf("%-5s %-20s %-10s %-10s\n", "ID", "Name", "Quantity", "Price");
        printf("---------------------------------------------------\n");
        for (int i = 0; i < productCount; i++) {
            printf("%-5d %-20s %-10d %-10.2f\n", 
                   inventory[i].id, 
                   inventory[i].name, 
                   inventory[i].quantity, 
                   inventory[i].price);
        }
        printf("---------------------------------------------------\n");
    }
    return 0;
}