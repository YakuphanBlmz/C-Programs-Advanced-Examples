#include <stdio.h>
#include <string.h>
#define MAX_PRODUCTS 10
typedef struct {
    char productID[10];
    char productName[50];
    int quantity;
    float price;
} Product;
int main() {
    Product inventory[MAX_PRODUCTS];
    int productCount = 0;
    FILE *inputFile;
    FILE *outputFile;
    float totalInventoryValue = 0.0;
    int highestQuantityIndex = -1;
    inputFile = fopen("inventory.txt", "r");
    if (inputFile == NULL) {
        printf("Error: Could not open inventory.txt\n");
        return 1;
    }
    while (productCount < MAX_PRODUCTS &&
           fscanf(inputFile, "%s %s %d %f",
                  inventory[productCount].productID,
                  inventory[productCount].productName,
                  &inventory[productCount].quantity,
                  &inventory[productCount].price) == 4) {
        productCount++;
    }
    fclose(inputFile);
    if (productCount > 0) {
        highestQuantityIndex = 0;
        for (int i = 0; i < productCount; i++) {
            totalInventoryValue += (float)inventory[i].quantity * inventory[i].price;
            if (inventory[i].quantity > inventory[highestQuantityIndex].quantity) {
                highestQuantityIndex = i;
            }
        }
    }
    outputFile = fopen("report.txt", "w");
    if (outputFile == NULL) {
        printf("Error: Could not open report.txt\n");
        return 1;
    }
    fprintf(outputFile, "Inventory Report\n");
    fprintf(outputFile, "----------------\n");
    fprintf(outputFile, "Total Inventory Value: %.2f\n", totalInventoryValue);
    if (highestQuantityIndex != -1) {
        fprintf(outputFile, "\nProduct with Highest Quantity:\n");
        fprintf(outputFile, "ID: %s\n", inventory[highestQuantityIndex].productID);
        fprintf(outputFile, "Name: %s\n", inventory[highestQuantityIndex].productName);
        fprintf(outputFile, "Quantity: %d\n", inventory[highestQuantityIndex].quantity);
        fprintf(outputFile, "Price: %.2f\n", inventory[highestQuantityIndex].price);
    } else {
        fprintf(outputFile, "\nNo products found in inventory.\n");
    }
    fclose(outputFile);
    return 0;
}