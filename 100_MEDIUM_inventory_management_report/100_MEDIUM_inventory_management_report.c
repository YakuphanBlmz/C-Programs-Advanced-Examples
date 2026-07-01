#include <stdio.h>
typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
} Product;
int main() {
    FILE *inputFile;
    FILE *outputFile;
    Product currentProduct;
    Product highestQuantityProduct = {0, "", 0.0, -1};
    float totalInventoryValue = 0.0;
    inputFile = fopen("products.txt", "r");
    if (inputFile == NULL) {
        printf("Hata: 'products.txt' dosyasi acilamadi.\n");
        return 1;
    }
    while (fscanf(inputFile, "%d %49s %f %d", &currentProduct.id, currentProduct.name, &currentProduct.price, &currentProduct.quantity) == 4) {
        totalInventoryValue += currentProduct.price * currentProduct.quantity;
        if (currentProduct.quantity > highestQuantityProduct.quantity) {
            highestQuantityProduct = currentProduct;
        }
    }
    fclose(inputFile);
    outputFile = fopen("report.txt", "w");
    if (outputFile == NULL) {
        printf("Hata: 'report.txt' dosyasi olusturulamadi veya acilamadi.\n");
        return 1;
    }
    fprintf(outputFile, "Toplam Envanter Degeri: %.2f TL\n", totalInventoryValue);
    if (highestQuantityProduct.quantity != -1) {
        fprintf(outputFile, "En Yuksek Stoktaki Urun:\n");
        fprintf(outputFile, "  ID: %d\n", highestQuantityProduct.id);
        fprintf(outputFile, "  Ad: %s\n", highestQuantityProduct.name);
        fprintf(outputFile, "  Fiyat: %.2f TL\n", highestQuantityProduct.price);
        fprintf(outputFile, "  Miktar: %d\n", highestQuantityProduct.quantity);
    } else {
        fprintf(outputFile, "Envanterde hic urun bulunamadi.\n");
    }
    fclose(outputFile);
    printf("Envanter raporu basariyla 'report.txt' dosyasina yazildi.\n");
    return 0;
}