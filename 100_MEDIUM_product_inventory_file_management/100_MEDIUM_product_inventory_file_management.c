#include <stdio.h>
#include <string.h>
typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
} Product;
int main() {
    Product inventory_out[3];
    inventory_out[0].id = 101;
    strcpy(inventory_out[0].name, "Laptop");
    inventory_out[0].price = 1200.50;
    inventory_out[0].quantity = 5;
    inventory_out[1].id = 102;
    strcpy(inventory_out[1].name, "Mouse");
    inventory_out[1].price = 25.00;
    inventory_out[1].quantity = 20;
    inventory_out[2].id = 103;
    strcpy(inventory_out[2].name, "Keyboard");
    inventory_out[2].price = 75.25;
    inventory_out[2].quantity = 10;
    FILE *file_ptr_write = fopen("products.dat", "wb");
    if (file_ptr_write == NULL) {
        printf("Error opening file for writing!\n");
        return 1;
    }
    fwrite(inventory_out, sizeof(Product), 3, file_ptr_write);
    fclose(file_ptr_write);
    printf("Products written to products.dat successfully.\n");
    Product inventory_in[3];
    float total_inventory_value = 0.0;
    FILE *file_ptr_read = fopen("products.dat", "rb");
    if (file_ptr_read == NULL) {
        printf("Error opening file for reading!\n");
        return 1;
    }
    fread(inventory_in, sizeof(Product), 3, file_ptr_read);
    fclose(file_ptr_read);
    printf("\nProducts read from products.dat:\n");
    for (int i = 0; i < 3; i++) {
        printf("ID: %d, Name: %s, Price: %.2f, Quantity: %d\n",
               inventory_in[i].id, inventory_in[i].name,
               inventory_in[i].price, inventory_in[i].quantity);
        total_inventory_value += inventory_in[i].price * inventory_in[i].quantity;
    }
    printf("\nTotal Inventory Value: %.2f\n", total_inventory_value);
    return 0;
}