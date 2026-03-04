#include <stdio.h>
#define MAX_NAME_LENGTH 50
#define MAX_PRODUCTS 100
#define MIN_VALUE_THRESHOLD 100.0f
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    float price;
    int quantity;
    float total_value;
} Product;
int main() {
    Product inventory[MAX_PRODUCTS];
    int productCount = 0;
    FILE *inputFile;
    FILE *outputFile;
    inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }
    while (productCount < MAX_PRODUCTS && 
           fscanf(inputFile, "%d %s %f %d", 
                  &inventory[productCount].id, 
                  inventory[productCount].name, 
                  &inventory[productCount].price, 
                  &inventory[productCount].quantity) == 4) {
        inventory[productCount].total_value = 
            inventory[productCount].price * inventory[productCount].quantity;
        productCount++;
    }
    fclose(inputFile);
    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Error opening output file!\n");
        return 1;
    }
    fprintf(outputFile, "ID Name Price Quantity Total_Value\n");
    for (int i = 0; i < productCount; i++) {
        if (inventory[i].total_value > MIN_VALUE_THRESHOLD) {
            fprintf(outputFile, "%d %s %.2f %d %.2f\n", 
                    inventory[i].id, 
                    inventory[i].name, 
                    inventory[i].price, 
                    inventory[i].quantity, 
                    inventory[i].total_value);
        }
    }
    fclose(outputFile);
    printf("Product inventory processed. Filtered products saved to output.txt\n");
    return 0;
}