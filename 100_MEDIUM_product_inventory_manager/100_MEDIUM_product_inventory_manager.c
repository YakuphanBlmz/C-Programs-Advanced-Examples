#include <stdio.h>
typedef struct {
    int id;
    char name[50];
    float price;
} Product;
int main() {
    Product products[] = {
        {101, "Laptop", 1200.50f},
        {102, "Mouse", 25.00f},
        {103, "Keyboard", 75.99f},
        {104, "Monitor", 300.00f}
    };
    int numProducts = sizeof(products) / sizeof(products[0]);
    const char* filename = "products.dat";
    FILE *file;
    file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Dosya yazma icin acilamadi");
        return 1;
    }
    fwrite(products, sizeof(Product), numProducts, file);
    fclose(file);
    printf("Urunler basariyla %s dosyasina yazildi.\n", filename);
    Product readProducts[numProducts];
    int productsReadCount = 0;
    file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Dosya okuma icin acilamadi");
        return 1;
    }
    productsReadCount = fread(readProducts, sizeof(Product), numProducts, file);
    fclose(file);
    printf("\n%s dosyasindan okunan urunler:\n", filename);
    if (productsReadCount == numProducts) {
        for (int i = 0; i < numProducts; i++) {
            printf("ID: %d, Isim: %s, Fiyat: %.2f\n", 
                   readProducts[i].id, 
                   readProducts[i].name, 
                   readProducts[i].price);
        }
    } else {
        printf("Tum urunler dosyadan okunamadi. Okunan urun sayisi: %d\n", productsReadCount);
    }
    return 0;
}