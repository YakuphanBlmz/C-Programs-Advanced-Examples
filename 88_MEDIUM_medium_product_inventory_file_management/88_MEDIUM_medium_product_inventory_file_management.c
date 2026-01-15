#include <stdio.h>
#include <string.h>
#define MAX_PRODUCTS 10
#define MAX_NAME_LEN 50
#define INPUT_FILE "inventory.txt"
#define OUTPUT_FILE "updated_inventory.txt"
typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    float price;
    int stock;
} Product;
int main() {
    Product inventory[MAX_PRODUCTS];
    int productCount = 0;
    FILE *inputFile;
    FILE *outputFile;
    char lineBuffer[256];
    int i;
    float totalInventoryValue = 0.0;
    int lowestStockProductIndex = -1;
    int targetProductId = 102;
    int newStockValue = 60;
    inputFile = fopen(INPUT_FILE, "r");
    if (inputFile == NULL) {
        printf("Error: Could not open input file %s\n", INPUT_FILE);
        return 1;
    }
    while (fgets(lineBuffer, sizeof(lineBuffer), inputFile) != NULL && productCount < MAX_PRODUCTS) {
        if (sscanf(lineBuffer, "%d,%49[^,],%f,%d",
                   &inventory[productCount].id,
                   inventory[productCount].name,
                   &inventory[productCount].price,
                   &inventory[productCount].stock) == 4) {
            productCount++;
        }
    }
    fclose(inputFile);
    printf("--- Initial Inventory Data ---\n");
    for (i = 0; i < productCount; i++) {
        printf("ID: %d, Name: %s, Price: %.2f, Stock: %d\n",
               inventory[i].id, inventory[i].name, inventory[i].price, inventory[i].stock);
    }
    printf("\n");
    if (productCount == 0) {
        printf("No products loaded.\n");
    } else {
        lowestStockProductIndex = 0;
        for (i = 0; i < productCount; i++) {
            totalInventoryValue += inventory[i].price * inventory[i].stock;
            if (inventory[i].stock < inventory[lowestStockProductIndex].stock) {
                lowestStockProductIndex = i;
            }
        }
        printf("Total Inventory Value: %.2f\n", totalInventoryValue);
        printf("Product with Lowest Stock: ID: %d, Name: %s, Stock: %d\n",
               inventory[lowestStockProductIndex].id,
               inventory[lowestStockProductIndex].name,
               inventory[lowestStockProductIndex].stock);
        printf("\n");
        for (i = 0; i < productCount; i++) {
            if (inventory[i].id == targetProductId) {
                inventory[i].stock = newStockValue;
                printf("Updated stock for Product ID %d (%s) to %d\n",
                       targetProductId, inventory[i].name, newStockValue);
                break;
            }
        }
        printf("\n");
        outputFile = fopen(OUTPUT_FILE, "w");
        if (outputFile == NULL) {
            printf("Error: Could not open output file %s\n", OUTPUT_FILE);
            return 1;
        }
        for (i = 0; i < productCount; i++) {
            fprintf(outputFile, "%d,%s,%.2f,%d\n",
                    inventory[i].id, inventory[i].name, inventory[i].price, inventory[i].stock);
        }
        fclose(outputFile);
        printf("Updated inventory saved to %s\n", OUTPUT_FILE);
    }
    return 0;
}