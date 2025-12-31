#include <stdio.h>
#include <string.h>
#define MAX_NAME_LENGTH 50
#define MAX_PRODUCTS 3
#define INPUT_FILENAME "products.bin"
#define OUTPUT_FILENAME "inventory_report.txt"
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    float price;
    int stock;
} Product;
int main() {
    Product inventory[MAX_PRODUCTS];
    FILE *inputFile;
    FILE *outputFile;
    int i;
    float totalInventoryValue = 0.0;
    inputFile = fopen(INPUT_FILENAME, "rb");
    if (inputFile == NULL) {
        printf("Error: Could not open input file '%s'. Make sure it exists and is accessible.\n", INPUT_FILENAME);
        return 1;
    }
    size_t readCount = fread(inventory, sizeof(Product), MAX_PRODUCTS, inputFile);
    fclose(inputFile);
    if (readCount < MAX_PRODUCTS) {
        printf("Warning: Expected %d products, but only read %zu from '%s'. Processing available data.\n", MAX_PRODUCTS, readCount, INPUT_FILENAME);
    }
    printf("--- Product Inventory Report ---\n");
    printf("%-5s %-20s %-10s %-8s %-15s\n", "ID", "Name", "Price", "Stock", "Value");
    printf("----------------------------------------------------------------\n");
    for (i = 0; i < readCount; i++) {
        float productValue = inventory[i].price * inventory[i].stock;
        totalInventoryValue += productValue;
        printf("%-5d %-20s %-10.2f %-8d %-15.2f\n",
               inventory[i].id,
               inventory[i].name,
               inventory[i].price,
               inventory[i].stock,
               productValue);
    }
    printf("----------------------------------------------------------------\n");
    printf("Total Inventory Value: %.2f\n", totalInventoryValue);
    printf("----------------------------------------------------------------\n\n");
    outputFile = fopen(OUTPUT_FILENAME, "w");
    if (outputFile == NULL) {
        printf("Error: Could not create output file '%s'.\n", OUTPUT_FILENAME);
        return 1;
    }
    fprintf(outputFile, "Product Inventory Summary\n");
    fprintf(outputFile, "---------------------------\n");
    fprintf(outputFile, "%-5s %-20s %-15s\n", "ID", "Name", "ProductValue");
    fprintf(outputFile, "------------------------------------------------\n");
    for (i = 0; i < readCount; i++) {
        float productValue = inventory[i].price * inventory[i].stock;
        fprintf(outputFile, "%-5d %-20s %-15.2f\n",
                inventory[i].id,
                inventory[i].name,
                productValue);
    }
    fprintf(outputFile, "------------------------------------------------\n");
    fprintf(outputFile, "Overall Total Inventory Value: %.2f\n", totalInventoryValue);
    fclose(outputFile);
    printf("Inventory report saved to %s\n", OUTPUT_FILENAME);
    return 0;
}