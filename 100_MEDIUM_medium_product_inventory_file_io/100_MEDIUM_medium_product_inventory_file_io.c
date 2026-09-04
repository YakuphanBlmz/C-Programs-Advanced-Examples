#include <stdio.h>
typedef struct {
    int id;
    char name[50];
    float price;
} Product;
int main() {
    FILE *file;
    Product currentProduct;
    Product mostExpensiveProduct = {0, "", 0.0f};
    float totalValue = 0.0f;
    file = fopen("products.txt", "r");
    if (file == NULL) {
        printf("Hata: 'products.txt' dosyasi acilamadi.\n");
        return 1;
    }
    while (fscanf(file, "%d %s %f", &currentProduct.id, currentProduct.name, &currentProduct.price) == 3) {
        totalValue += currentProduct.price;
        if (currentProduct.price > mostExpensiveProduct.price) {
            mostExpensiveProduct = currentProduct;
        }
    }
    fclose(file);
    printf("Tum urunlerin toplam degeri: %.2f\n", totalValue);
    if (mostExpensiveProduct.id != 0) {
        printf("En pahali urun:\n");
        printf("  ID: %d\n", mostExpensiveProduct.id);
        printf("  Ad: %s\n", mostExpensiveProduct.name);
        printf("  Fiyat: %.2f\n", mostExpensiveProduct.price);
    } else {
        printf("Dosyada hic urun bulunamadi veya okunamadi.\n");
    }
    return 0;
}