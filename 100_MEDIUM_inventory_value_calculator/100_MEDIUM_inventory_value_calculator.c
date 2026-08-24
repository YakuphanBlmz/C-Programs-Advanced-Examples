#include <stdio.h>
#include <string.h>
typedef struct {
    int id;
    char name[50];
    double price;
    int quantity;
} Product;
double calculateTotalInventoryValue(Product products[], int count) {
    double totalValue = 0.0;
    for (int i = 0; i < count; i++) {
        totalValue += products[i].price * products[i].quantity;
    }
    return totalValue;
}
void findProductById(Product products[], int count, int searchId) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (products[i].id == searchId) {
            printf("Urun Bulundu:\n");
            printf("ID: %d\n", products[i].id);
            printf("Ad: %s\n", products[i].name);
            printf("Fiyat: %.2f\n", products[i].price);
            printf("Miktar: %d\n", products[i].quantity);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("ID %d ile urun bulunamadi.\n", searchId);
    }
}
int main() {
    Product inventory[3];
    int productCount = 0;
    inventory[productCount].id = 101;
    strcpy(inventory[productCount].name, "Laptop");
    inventory[productCount].price = 1200.00;
    inventory[productCount].quantity = 5;
    productCount++;
    inventory[productCount].id = 102;
    strcpy(inventory[productCount].name, "Mouse");
    inventory[productCount].price = 25.50;
    inventory[productCount].quantity = 20;
    productCount++;
    inventory[productCount].id = 103;
    strcpy(inventory[productCount].name, "Keyboard");
    inventory[productCount].price = 75.00;
    inventory[productCount].quantity = 10;
    productCount++;
    double totalValue = calculateTotalInventoryValue(inventory, productCount);
    printf("Toplam Envanter Degeri: %.2f\n\n", totalValue);
    int searchId1 = 102;
    printf("Urun Arama (ID: %d):\n", searchId1);
    findProductById(inventory, productCount, searchId1);
    printf("\n");
    int searchId2 = 105;
    printf("Urun Arama (ID: %d):\n", searchId2);
    findProductById(inventory, productCount, searchId2);
    printf("\n");
    return 0;
}