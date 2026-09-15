#include <stdio.h>
typedef struct {
    int id;
    char name[50];
    float price;
} Product;
int main() {
    Product products_to_write[] = {
        {101, "Laptop", 1200.50f},
        {102, "Mouse", 25.00f},
        {103, "Keyboard", 75.99f},
        {104, "Monitor", 300.00f}
    };
    int num_products = sizeof(products_to_write) / sizeof(products_to_write[0]);
    FILE *file_ptr = fopen("products.dat", "wb");
    if (file_ptr == NULL) {
        printf("Error opening file for writing!\n");
        return 1;
    }
    if (fwrite(products_to_write, sizeof(Product), num_products, file_ptr) != num_products) {
        printf("Error writing all products to file.\n");
        fclose(file_ptr);
        return 1;
    }
    printf("Successfully wrote %d products to products.dat\n", num_products);
    fclose(file_ptr);
    Product products_read[num_products];
    int num_products_read = 0;
    file_ptr = fopen("products.dat", "rb");
    if (file_ptr == NULL) {
        printf("Error opening file for reading!\n");
        return 1;
    }
    num_products_read = fread(products_read, sizeof(Product), num_products, file_ptr);
    printf("\nProducts read from file:\n");
    if (num_products_read == 0) {
        printf("No products were read from the file.\n");
    } else {
        for (int i = 0; i < num_products_read; i++) {
            printf("ID: %d, Name: %s, Price: %.2f\n", 
                   products_read[i].id, products_read[i].name, products_read[i].price);
        }
    }
    fclose(file_ptr);
    return 0;
}