#include <stdio.h>
#include <string.h>
typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
} Product;
int main() {
    Product initialInventory[3];
    initialInventory[0].id = 101;
    strcpy(initialInventory[0].name, "Laptop");
    initialInventory[0].price = 1200.00;
    initialInventory[0].quantity = 5;
    initialInventory[1].id = 102;
    strcpy(initialInventory[1].name, "Mouse");
    initialInventory[1].price = 25.50;
    initialInventory[1].quantity = 20;
    initialInventory[2].id = 103;
    strcpy(initialInventory[2].name, "Keyboard");
    initialInventory[2].price = 75.00;
    initialInventory[2].quantity = 10;
    FILE *fp_write = fopen("inventory.dat", "wb");
    if (fp_write == NULL) {
        printf("Error opening file for writing!\n");
        return 1;
    }
    for (int i = 0; i < 3; i++) {
        fwrite(&initialInventory[i], sizeof(Product), 1, fp_write);
    }
    fclose(fp_write);
    printf("Initial inventory written to inventory.dat\n");
    Product loadedInventory[3];
    float totalValue = 0.0;
    FILE *fp_read = fopen("inventory.dat", "rb");
    if (fp_read == NULL) {
        printf("Error opening file for reading!\n");
        return 1;
    }
    for (int i = 0; i < 3; i++) {
        fread(&loadedInventory[i], sizeof(Product), 1, fp_read);
        totalValue += loadedInventory[i].price * loadedInventory[i].quantity;
    }
    fclose(fp_read);
    printf("Inventory loaded from inventory.dat\n");
    printf("Total value of all products in stock: %.2f\n", totalValue);
    return 0;
}