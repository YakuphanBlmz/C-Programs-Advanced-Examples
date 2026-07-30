#include <stdio.h>
typedef struct {
    int id;
    char name[30];
    float price;
} Product;
int main() {
    Product inventory[3];
    int i;
    FILE *fp;
    printf("Enter data for 3 products:\n");
    for (i = 0; i < 3; i++) {
        printf("Product %d ID: ", i + 1);
        scanf("%d", &inventory[i].id);
        printf("Product %d Name: ", i + 1);
        scanf("%s", inventory[i].name);
        printf("Product %d Price: ", i + 1);
        scanf("%f", &inventory[i].price);
    }
    fp = fopen("products.dat", "wb");
    if (fp == NULL) {
        printf("Error opening file for writing!\n");
        return 1;
    }
    fwrite(inventory, sizeof(Product), 3, fp);
    fclose(fp);
    printf("\nProduct data written to products.dat.\n");
    printf("\nReading product data from products.dat:\n");
    fp = fopen("products.dat", "rb");
    if (fp == NULL) {
        printf("Error opening file for reading!\n");
        return 1;
    }
    Product readProducts[3];
    fread(readProducts, sizeof(Product), 3, fp);
    fclose(fp);
    printf("\nProducts read from file:\n");
    for (i = 0; i < 3; i++) {
        printf("ID: %d, Name: %s, Price: %.2f\n", readProducts[i].id, readProducts[i].name, readProducts[i].price);
    }
    return 0;
}