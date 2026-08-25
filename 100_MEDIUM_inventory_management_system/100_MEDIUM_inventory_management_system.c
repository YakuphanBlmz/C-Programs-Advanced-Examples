#include <stdio.h>
typedef struct {
    int id;
    char name[50];
    double price;
    int quantity;
} Product;
int main() {
    Product inventory[3] = {
        {101, "Laptop", 1200.00, 5},
        {102, "Mouse", 25.50, 20},
        {103, "Keyboard", 75.00, 10}
    };
    int numProducts = 3;
    printf("Initial Inventory:\n");
    for (int i = 0; i < numProducts; i++) {
        printf("ID: %d, Name: %s, Price: %.2f, Quantity: %d\n",
               inventory[i].id, inventory[i].name, inventory[i].price, inventory[i].quantity);
    }
    printf("\n");
    int saleId1 = 101;
    int saleQuantity1 = 2;
    int found1 = 0;
    for (int i = 0; i < numProducts; i++) {
        if (inventory[i].id == saleId1) {
            found1 = 1;
            if (inventory[i].quantity >= saleQuantity1) {
                inventory[i].quantity -= saleQuantity1;
                printf("Sold %d units of product ID %d.\n", saleQuantity1, saleId1);
            } else {
                printf("Error: Not enough stock for product ID %d. Available: %d, Requested: %d.\n",
                       saleId1, inventory[i].quantity, saleQuantity1);
            }
            break;
        }
    }
    if (!found1) {
        printf("Error: Product with ID %d not found.\n", saleId1);
    }
    int saleId2 = 102;
    int saleQuantity2 = 25;
    int found2 = 0;
    for (int i = 0; i < numProducts; i++) {
        if (inventory[i].id == saleId2) {
            found2 = 1;
            if (inventory[i].quantity >= saleQuantity2) {
                inventory[i].quantity -= saleQuantity2;
                printf("Sold %d units of product ID %d.\n", saleQuantity2, saleId2);
            } else {
                printf("Error: Not enough stock for product ID %d. Available: %d, Requested: %d.\n",
                       saleId2, inventory[i].quantity, saleQuantity2);
            }
            break;
        }
    }
    if (!found2) {
        printf("Error: Product with ID %d not found.\n", saleId2);
    }
    printf("\nInventory after sales:\n");
    for (int i = 0; i < numProducts; i++) {
        printf("ID: %d, Name: %s, Price: %.2f, Quantity: %d\n",
               inventory[i].id, inventory[i].name, inventory[i].price, inventory[i].quantity);
    }
    double totalInventoryValue = 0.0;
    for (int i = 0; i < numProducts; i++) {
        totalInventoryValue += inventory[i].price * inventory[i].quantity;
    }
    printf("\nTotal Inventory Value: %.2f\n", totalInventoryValue);
    return 0;
}