#include <stdio.h>
#include <string.h>
#define MAX_PRODUCTS 10
#define FILENAME_IN "products.txt"
#define FILENAME_OUT "outofstock.txt"
typedef struct {
    int productId;
    char productName[50];
    int quantity;
    float price;
} Product;
int main() {
    FILE *inputFile;
    FILE *outputFile;
    Product inventory[MAX_PRODUCTS];
    int productCount = 0;
    float totalInventoryValue = 0.0;
    int i;
    inputFile = fopen(FILENAME_IN, "r");
    if (inputFile == NULL) {
        printf("Hata: Giriş dosyası %s açılamadı.\n", FILENAME_IN);
        return 1;
    }
    while (productCount < MAX_PRODUCTS &&
           fscanf(inputFile, "%d,%49[^,],%d,%f\n",
                  &inventory[productCount].productId,
                  inventory[productCount].productName,
                  &inventory[productCount].quantity,
                  &inventory[productCount].price) == 4) {
        productCount++;
    }
    fclose(inputFile);
    for (i = 0; i < productCount; i++) {
        totalInventoryValue += (float)inventory[i].quantity * inventory[i].price;
    }
    outputFile = fopen(FILENAME_OUT, "w");
    if (outputFile == NULL) {
        printf("Hata: Çıkış dosyası %s açılamadı.\n", FILENAME_OUT);
        return 1;
    }
    fprintf(outputFile, "Stok Dışı Ürünler Raporu:\n");
    fprintf(outputFile, "-----------------------------\n");
    for (i = 0; i < productCount; i++) {
        if (inventory[i].quantity == 0) {
            fprintf(outputFile, "%s (ID: %d) stokta yok.\n",
                    inventory[i].productName, inventory[i].productId);
        }
    }
    fclose(outputFile);
    printf("Toplam Envanter Değeri: %.2f\n", totalInventoryValue);
    printf("Stok dışı ürünler raporu %s dosyasına oluşturuldu.\n", FILENAME_OUT);
    return 0;
}