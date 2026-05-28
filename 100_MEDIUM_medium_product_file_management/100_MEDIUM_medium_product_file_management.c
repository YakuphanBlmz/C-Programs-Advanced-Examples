#include <stdio.h>
typedef struct {
    int id;
    char name[50];
    float price;
    int stock;
} Product;
int main() {
    FILE *fp;
    Product p;
    int num_products, i;
    fp = fopen("products.dat", "wb");
    if (fp == NULL) {
        printf("Error opening file for writing!\n");
        return 1;
    }
    printf("How many products do you want to enter? ");
    scanf("%d", &num_products);
    for (i = 0; i < num_products; i++) {
        printf("\nEnter details for product %d:\n", i + 1);
        printf("ID: ");
        scanf("%d", &p.id);
        printf("Name (no spaces): ");
        scanf("%49s", p.name);
        printf("Price: ");
        scanf("%f", &p.price);
        printf("Stock: ");
        scanf("%d", &p.stock);
        fwrite(&p, sizeof(Product), 1, fp);
    }
    fclose(fp);
    printf("\nProducts saved to products.dat\n");
    fp = fopen("products.dat", "rb");
    if (fp == NULL) {
        printf("Error opening file for reading!\n");
        return 1;
    }
    printf("\n--- Products from file ---\n");
    printf("%-5s %-20s %-10s %-10s\n", "ID", "Name", "Price", "Stock");
    printf("--------------------------------------------------\n");
    while (fread(&p, sizeof(Product), 1, fp) == 1) {
        printf("%-5d %-20s %-10.2f %-10d\n", p.id, p.name, p.price, p.stock);
    }
    fclose(fp);
    return 0;
}