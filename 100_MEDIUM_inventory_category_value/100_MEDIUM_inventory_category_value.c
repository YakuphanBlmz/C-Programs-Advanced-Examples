#include <stdio.h>
#include <string.h>
typedef struct {
    int id;
    char name[50];
    int category_id;
    float price;
} Product;
int main() {
    Product inventory[5];
    inventory[0].id = 101;
    strcpy(inventory[0].name, "Laptop");
    inventory[0].category_id = 1;
    inventory[0].price = 1200.50;
    inventory[1].id = 102;
    strcpy(inventory[1].name, "Mouse");
    inventory[1].category_id = 2;
    inventory[1].price = 25.00;
    inventory[2].id = 103;
    strcpy(inventory[2].name, "Keyboard");
    inventory[2].category_id = 2;
    inventory[2].price = 75.99;
    inventory[3].id = 104;
    strcpy(inventory[3].name, "Monitor");
    inventory[3].category_id = 1;
    inventory[3].price = 300.75;
    inventory[4].id = 105;
    strcpy(inventory[4].name, "Webcam");
    inventory[4].category_id = 3;
    inventory[4].price = 49.95;
    int user_category;
    float total_value = 0.0;
    int i;
    printf("Enter category ID to calculate total value (e.g., 1 for Electronics, 2 for Peripherals): ");
    scanf("%d", &user_category);
    for (i = 0; i < 5; i++) {
        if (inventory[i].category_id == user_category) {
            total_value += inventory[i].price;
        }
    }
    printf("Total value for category %d: %.2f\n", user_category, total_value);
    return 0;
}