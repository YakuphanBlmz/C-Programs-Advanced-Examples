#include <stdio.h>
#include <string.h>
#define MAX_PRODUCTS 5
#define FILENAME "inventory.bin"
typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
} Product;
void writeProductsToFile(const Product products[], int count, const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Hata: Dosya yazma modunda açılamadı.\n");
        return;
    }
    fwrite(products, sizeof(Product), count, fp);
    fclose(fp);
    printf("%d ürün başarıyla dosyaya kaydedildi.\n", count);
}
void readProductsFromFile(Product products[], int *count, const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Hata: Dosya okuma modunda açılamadı veya mevcut değil.\n");
        *count = 0;
        return;
    }
    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    int read_count = filesize / sizeof(Product);
    if (read_count > MAX_PRODUCTS) {
        read_count = MAX_PRODUCTS;
    }
    fread(products, sizeof(Product), read_count, fp);
    fclose(fp);
    *count = read_count;
    printf("%d ürün dosyadan başarıyla okundu.\n", *count);
}
void printProductDetails(const Product products[], int count) {
    printf("\n--- Ürün Detayları ---\n");
    if (count == 0) {
        printf("Envanterde ürün bulunmamaktadır.\n");
        return;
    }
    int i;
    for (i = 0; i < count; i++) {
        printf("ID: %d, Ad: %s, Fiyat: %.2f, Miktar: %d\n",
               products[i].id, products[i].name, products[i].price, products[i].quantity);
    }
    printf("------------------------\n");
}
float calculateTotalInventoryValue(const Product products[], int count) {
    float totalValue = 0.0f;
    int i;
    for (i = 0; i < count; i++) {
        totalValue += products[i].price * products[i].quantity;
    }
    return totalValue;
}
int main() {
    Product initial_products[MAX_PRODUCTS];
    int initial_product_count = 3;
    initial_products[0].id = 101;
    strcpy(initial_products[0].name, "Laptop");
    initial_products[0].price = 1200.00f;
    initial_products[0].quantity = 5;
    initial_products[1].id = 102;
    strcpy(initial_products[1].name, "Mouse");
    initial_products[1].price = 25.50f;
    initial_products[1].quantity = 15;
    initial_products[2].id = 103;
    strcpy(initial_products[2].name, "Keyboard");
    initial_products[2].price = 75.00f;
    initial_products[2].quantity = 8;
    printf("Başlangıç ürünlerini dosyaya kaydetme...\n");
    writeProductsToFile(initial_products, initial_product_count, FILENAME);
    Product loaded_products[MAX_PRODUCTS];
    int loaded_product_count;
    printf("\nDosyadan ürünleri okuma...\n");
    readProductsFromFile(loaded_products, &loaded_product_count, FILENAME);
    printProductDetails(loaded_products, loaded_product_count);
    float totalInventoryValue = calculateTotalInventoryValue(loaded_products, loaded_product_count);
    printf("Toplam Envanter Değeri: %.2f TL\n", totalInventoryValue);
    return 0;
}