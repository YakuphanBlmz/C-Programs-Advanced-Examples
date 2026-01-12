#include <stdio.h>
#include <string.h>
typedef struct {
    int id;
    char name[50];
    int quantity;
} Product;
int main() {
    Product inventory_out[] = {
        {101, "Laptop", 10},
        {102, "Mouse", 50},
        {103, "Keyboard", 25},
        {104, "Monitor", 15},
        {105, "Webcam", 30}
    };
    int num_products = sizeof(inventory_out) / sizeof(inventory_out[0]);
    FILE *file_out = fopen("inventory.dat", "wb");
    if (file_out == NULL) {
        printf("Error opening file for writing!\n");
        return 1;
    }
    fwrite(inventory_out, sizeof(Product), num_products, file_out);
    fclose(file_out);
    printf("Products successfully written to inventory.dat.\n\n");
    Product inventory_in[num_products];
    FILE *file_in = fopen("inventory.dat", "rb");
    if (file_in == NULL) {
        printf("Error opening file for reading!\n");
        return 1;
    }
    fread(inventory_in, sizeof(Product), num_products, file_in);
    fclose(file_in);
    printf("Products read from inventory.dat:\n");
    printf("-----------------------------------\n");
    for (int i = 0; i < num_products; i++) {
        printf("ID: %d, Name: %s, Quantity: %d\n", 
               inventory_in[i].id, 
               inventory_in[i].name, 
               inventory_in[i].quantity);
    }
    printf("-----------------------------------\n");
    return 0;
}