#include <stdio.h>
#include <string.h>
typedef struct {
    int id;
    char name[50];
    double price;
} Product;
int main() {
    Product inventory[5];
    inventory[0].id = 101;
    strcpy(inventory[0].name, "Laptop");
    inventory[0].price = 1200.00;
    inventory[1].id = 102;
    strcpy(inventory[1].name, "Mouse");
    inventory[1].price = 25.50;
    inventory[2].id = 103;
    strcpy(inventory[2].name, "Keyboard");
    inventory[2].price = 75.00;
    inventory[3].id = 104;
    strcpy(inventory[3].name, "Monitor");
    inventory[3].price = 300.00;
    inventory[4].id = 105;
    strcpy(inventory[4].name, "Webcam");
    inventory[4].price = 45.99;
    printf("Products with price greater than $50.00:\n");
    for (int i = 0; i < 5; i++) {
        if (inventory[i].price > 50.00) {
            printf("ID: %d, Name: %s, Price: %.2f\n", inventory[i].id, inventory[i].name, inventory[i].price);
        }
    }
    Product mostExpensiveProduct = inventory[0]; 
    for (int i = 1; i < 5; i++) {
        if (inventory[i].price > mostExpensiveProduct.price) {
            mostExpensiveProduct = inventory[i];
        }
    }
    printf("\nMost expensive product:\n");
    printf("ID: %d, Name: %s, Price: %.2f\n", mostExpensiveProduct.id, mostExpensiveProduct.name, mostExpensiveProduct.price);
    return 0;
}