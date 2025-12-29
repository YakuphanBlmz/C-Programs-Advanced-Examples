#include <stdio.h>
#include <string.h>
#define MAX_NAME_LENGTH 50
#define MAX_PRODUCTS 10
#define FILENAME "products.txt"
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    float price;
    int stock;
} Product;
void loadProducts(Product products[], int *count, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        *count = 0;
        return;
    }
    *count = 0;
    while (*count < MAX_PRODUCTS && fscanf(file, "%d %s %f %d", 
                                          &products[*count].id, 
                                          products[*count].name, 
                                          &products[*count].price, 
                                          &products[*count].stock) == 4) {
        (*count)++;
    }
    fclose(file);
}
void saveProducts(const Product products[], int count, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not open file for writing.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %.2f %d\n", 
                products[i].id, 
                products[i].name, 
                products[i].price, 
                products[i].stock);
    }
    fclose(file);
}
void listProducts(const Product products[], int count) {
    if (count == 0) {
        printf("No products to display.\n");
        return;
    }
    printf("--- Product List ---\n");
    printf("%-5s %-20s %-10s %-8s\n", "ID", "Name", "Price", "Stock");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %-10.2f %-8d\n", 
               products[i].id, 
               products[i].name, 
               products[i].price, 
               products[i].stock);
    }
    printf("--------------------------------------------------\n");
}
void addProduct(Product products[], int *count) {
    if (*count >= MAX_PRODUCTS) {
        printf("Cannot add more products. Inventory is full.\n");
        return;
    }
    Product newProduct;
    printf("Enter Product ID: ");
    scanf("%d", &newProduct.id);
    printf("Enter Product Name: ");
    scanf("%s", newProduct.name);
    printf("Enter Product Price: ");
    scanf("%f", &newProduct.price);
    printf("Enter Product Stock: ");
    scanf("%d", &newProduct.stock);
    products[*count] = newProduct;
    (*count)++;
    printf("Product added successfully.\n");
}
void searchProduct(const Product products[], int count) {
    int searchId;
    printf("Enter Product ID to search: ");
    scanf("%d", &searchId);
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (products[i].id == searchId) {
            printf("Product Found:\n");
            printf("ID: %d, Name: %s, Price: %.2f, Stock: %d\n", 
                   products[i].id, products[i].name, products[i].price, products[i].stock);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Product with ID %d not found.\n", searchId);
    }
}
int main() {
    Product inventory[MAX_PRODUCTS];
    int productCount = 0;
    int choice;
    loadProducts(inventory, &productCount, FILENAME);
    do {
        printf("\n--- Product Management System ---\n");
        printf("1. List All Products\n");
        printf("2. Add New Product\n");
        printf("3. Search Product by ID\n");
        printf("4. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                listProducts(inventory, productCount);
                break;
            case 2:
                addProduct(inventory, &productCount);
                break;
            case 3:
                searchProduct(inventory, productCount);
                break;
            case 4:
                saveProducts(inventory, productCount, FILENAME);
                printf("Inventory saved. Exiting.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
    return 0;
}