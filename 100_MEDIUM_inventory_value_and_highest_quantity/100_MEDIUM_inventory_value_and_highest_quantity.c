#include <stdio.h>
#include <string.h>
typedef struct {
    int id;
    char name[50];
    double price;
    int quantity;
} Product;
int main() {
    Product inventory[3];
    inventory[0].id = 101;
    strcpy(inventory[0].name, "Laptop");
    inventory[0].price = 1200.50;
    inventory[0].quantity = 5;
    inventory[1].id = 102;
    strcpy(inventory[1].name, "Mouse");
    inventory[1].price = 25.00;
    inventory[1].quantity = 15;
    inventory[2].id = 103;
    strcpy(inventory[2].name, "Keyboard");
    inventory[2].price = 75.99;
    inventory[2].quantity = 8;
    double total_inventory_value = 0.0;
    int highest_quantity = -1;
    int highest_quantity_product_index = -1;
    for (int i = 0; i < 3; i++) {
        total_inventory_value += inventory[i].price * inventory[i].quantity;
        if (inventory[i].quantity > highest_quantity) {
            highest_quantity = inventory[i].quantity;
            highest_quantity_product_index = i;
        }
    }
    printf("Total Inventory Value: %.2f\n", total_inventory_value);
    if (highest_quantity_product_index != -1) {
        printf("\nProduct with Highest Quantity:\n");
        printf("ID: %d\n", inventory[highest_quantity_product_index].id);
        printf("Name: %s\n", inventory[highest_quantity_product_index].name);
        printf("Price: %.2f\n", inventory[highest_quantity_product_index].price);
        printf("Quantity: %d\n", inventory[highest_quantity_product_index].quantity);
    } else {
        printf("\nNo products in inventory.\n");
    }
    return 0;
}