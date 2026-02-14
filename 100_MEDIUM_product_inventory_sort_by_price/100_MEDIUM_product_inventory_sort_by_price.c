#include <stdio.h>
typedef struct {
    int id;
    char name[50];
    float price;
} Product;
int main() {
    Product inventory[5] = {
        {101, "Laptop", 1200.50f},
        {102, "Mouse", 25.00f},
        {103, "Keyboard", 75.99f},
        {104, "Monitor", 300.75f},
        {105, "Webcam", 49.95f}
    };
    int numProducts = 5;
    int i, j;
    for (i = 0; i < numProducts - 1; i++) {
        for (j = 0; j < numProducts - i - 1; j++) {
            if (inventory[j].price > inventory[j+1].price) {
                Product temp = inventory[j];
                inventory[j] = inventory[j+1];
                inventory[j+1] = temp;
            }
        }
    }
    printf("Sorted Products by Price (Ascending):\n");
    printf("--------------------------------------\n");
    for (i = 0; i < numProducts; i++) {
        printf("ID: %d, Name: %s, Price: %.2f\n", inventory[i].id, inventory[i].name, inventory[i].price);
    }
    return 0;
}