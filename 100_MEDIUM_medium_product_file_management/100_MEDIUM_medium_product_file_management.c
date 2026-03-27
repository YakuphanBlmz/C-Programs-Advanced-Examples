#include <stdio.h>
#include <string.h>
typedef struct {
    int id;
    char name[50];
    float price;
} Product;
int main() {
    Product products_to_write[3];
    products_to_write[0].id = 101;
    strcpy(products_to_write[0].name, "Laptop");
    products_to_write[0].price = 1200.50;
    products_to_write[1].id = 102;
    strcpy(products_to_write[1].name, "Mouse");
    products_to_write[1].price = 25.99;
    products_to_write[2].id = 103;
    strcpy(products_to_write[2].name, "Keyboard");
    products_to_write[2].price = 75.00;
    FILE *fp_write;
    fp_write = fopen("products.dat", "wb");
    if (fp_write == NULL) {
        printf("Error opening file for writing!\n");
        return 1;
    }
    fwrite(products_to_write, sizeof(Product), 3, fp_write);
    fclose(fp_write);
    printf("Products written to products.dat successfully.\n\n");
    Product products_read[3];
    FILE *fp_read;
    fp_read = fopen("products.dat", "rb");
    if (fp_read == NULL) {
        printf("Error opening file for reading!\n");
        return 1;
    }
    fread(products_read, sizeof(Product), 3, fp_read);
    fclose(fp_read);
    printf("Products read from products.dat:\n");
    for (int i = 0; i < 3; i++) {
        printf("ID: %d, Name: %s, Price: %.2f\n", products_read[i].id, products_read[i].name, products_read[i].price);
    }
    return 0;
}