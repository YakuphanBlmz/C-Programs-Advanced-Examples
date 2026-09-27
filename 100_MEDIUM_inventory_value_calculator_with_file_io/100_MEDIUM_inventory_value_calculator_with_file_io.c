#include <stdio.h>
#define MAX_NAME_LEN 50
#define MAX_PRODUCTS 3
#define FILENAME "inventory.dat"
typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    float price;
    int stock;
} Product;
int main() {
    Product products_to_write[MAX_PRODUCTS] = {
        {101, "Laptop", 1200.00, 5},
        {102, "Mouse", 25.50, 20},
        {103, "Keyboard", 75.00, 10}
    };
    FILE *file_ptr_write = fopen(FILENAME, "wb");
    if (file_ptr_write == NULL) {
        printf("Dosya yazma hatasi!\n");
        return 1;
    }
    fwrite(products_to_write, sizeof(Product), MAX_PRODUCTS, file_ptr_write);
    fclose(file_ptr_write);
    Product products_read[MAX_PRODUCTS];
    FILE *file_ptr_read = fopen(FILENAME, "rb");
    if (file_ptr_read == NULL) {
        printf("Dosya okuma hatasi!\n");
        return 1;
    }
    fread(products_read, sizeof(Product), MAX_PRODUCTS, file_ptr_read);
    fclose(file_ptr_read);
    float total_inventory_value = 0.0;
    int i;
    for (i = 0; i < MAX_PRODUCTS; i++) {
        total_inventory_value += products_read[i].price * products_read[i].stock;
    }
    printf("Toplam Envanter Degeri: %.2f TL\n", total_inventory_value);
    return 0;
}