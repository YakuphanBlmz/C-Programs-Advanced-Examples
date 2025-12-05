#include <stdio.h>
typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
} Product;
int main() {
    Product p1 = {101, "Laptop", 1200.50, 10};
    Product p2 = {102, "Mouse", 25.99, 50};
    Product p3 = {103, "Keyboard", 75.00, 20};
    FILE *file_ptr_write = fopen("products.dat", "wb");
    if (file_ptr_write == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }
    fwrite(&p1, sizeof(Product), 1, file_ptr_write);
    fwrite(&p2, sizeof(Product), 1, file_ptr_write);
    fwrite(&p3, sizeof(Product), 1, file_ptr_write);
    fclose(file_ptr_write);
    printf("Products written to products.dat\n");
    printf("--------------------------------\n");
    printf("Reading products from file:\n");
    FILE *file_ptr_read = fopen("products.dat", "rb");
    if (file_ptr_read == NULL) {
        printf("Error opening file for reading.\n");
        return 1;
    }
    Product read_product;
    int count = 0;
    while (fread(&read_product, sizeof(Product), 1, file_ptr_read) == 1) {
        count++;
        printf("Product %d:\n", count);
        printf("  ID: %d\n", read_product.id);
        printf("  Name: %s\n", read_product.name);
        printf("  Price: %.2f\n", read_product.price);
        printf("  Quantity: %d\n", read_product.quantity);
        printf("\n");
    }
    fclose(file_ptr_read);
    printf("Finished reading products.\n");
    return 0;
}