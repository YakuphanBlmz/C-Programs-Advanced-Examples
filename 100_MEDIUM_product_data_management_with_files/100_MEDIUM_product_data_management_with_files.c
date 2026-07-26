#include <stdio.h>
#include <string.h>
typedef struct {
    int id;
    char name[50];
    double price;
} Product;
int main() {
    Product initialProducts[3] = {
        {101, "Laptop", 1200.00},
        {102, "Mouse", 25.50},
        {103, "Keyboard", 75.00}
    };
    int numProducts = 3;
    FILE *outFile = fopen("products.dat", "wb");
    if (outFile == NULL) {
        printf("Error opening products.dat for writing!\n");
        return 1;
    }
    fwrite(initialProducts, sizeof(Product), numProducts, outFile);
    fclose(outFile);
    printf("Initial products written to products.dat\n");
    Product readProducts[3];
    FILE *inFile = fopen("products.dat", "rb");
    if (inFile == NULL) {
        printf("Error opening products.dat for reading!\n");
        return 1;
    }
    fread(readProducts, sizeof(Product), numProducts, inFile);
    fclose(inFile);
    printf("Products read from products.dat:\n");
    for (int i = 0; i < numProducts; i++) {
        printf("ID: %d, Name: %s, Price: %.2f\n", readProducts[i].id, readProducts[i].name, readProducts[i].price);
    }
    int targetId = 102;
    double newPrice = 30.00;
    printf("\nUpdating price for Product ID %d to %.2f\n", targetId, newPrice);
    for (int i = 0; i < numProducts; i++) {
        if (readProducts[i].id == targetId) {
            readProducts[i].price = newPrice;
            break;
        }
    }
    FILE *updatedOutFile = fopen("updated_products.dat", "wb");
    if (updatedOutFile == NULL) {
        printf("Error opening updated_products.dat for writing!\n");
        return 1;
    }
    fwrite(readProducts, sizeof(Product), numProducts, updatedOutFile);
    fclose(updatedOutFile);
    printf("Updated products written to updated_products.dat\n");
    printf("\nVerifying contents of updated_products.dat:\n");
    Product verifiedProducts[3];
    FILE *verifyFile = fopen("updated_products.dat", "rb");
    if (verifyFile == NULL) {
        printf("Error opening updated_products.dat for verification!\n");
        return 1;
    }
    fread(verifiedProducts, sizeof(Product), numProducts, verifyFile);
    fclose(verifyFile);
    for (int i = 0; i < numProducts; i++) {
        printf("ID: %d, Name: %s, Price: %.2f\n", verifiedProducts[i].id, verifiedProducts[i].name, verifiedProducts[i].price);
    }
    return 0;
}