#include <stdio.h>
#include <string.h>
typedef struct {
    int id;
    char name[50];
    float price;
    int stock;
} Product;
int main() {
    Product inventory[3];
    inventory[0].id = 101;
    strcpy(inventory[0].name, "Laptop");
    inventory[0].price = 1200.50;
    inventory[0].stock = 5;
    inventory[1].id = 102;
    strcpy(inventory[1].name, "Mouse");
    inventory[1].price = 25.00;
    inventory[1].stock = 20;
    inventory[2].id = 103;
    strcpy(inventory[2].name, "Keyboard");
    inventory[2].price = 75.20;
    inventory[2].stock = 10;
    float total_inventory_value = 0.0;
    int i;
    for (i = 0; i < 3; i++) {
        total_inventory_value += inventory[i].price * inventory[i].stock;
    }
    printf("Total Inventory Value: %.2f TL\n\n", total_inventory_value);
    int search_id;
    int found_index = -1;
    printf("Enter product ID to search: ");
    scanf("%d", &search_id);
    for (i = 0; i < 3; i++) {
        if (inventory[i].id == search_id) {
            found_index = i;
            break;
        }
    }
    if (found_index != -1) {
        printf("\nProduct found:\n");
        printf("ID: %d\n", inventory[found_index].id);
        printf("Name: %s\n", inventory[found_index].name);
        printf("Price: %.2f\n", inventory[found_index].price);
        printf("Stock: %d\n", inventory[found_index].stock);
    } else {
        printf("\nProduct not found. ID: %d\n", search_id);
    }
    return 0;
}