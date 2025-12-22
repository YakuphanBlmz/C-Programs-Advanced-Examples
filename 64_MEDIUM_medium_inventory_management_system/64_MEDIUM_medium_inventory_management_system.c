#include <stdio.h>
#include <string.h>
typedef struct {
    int productID;
    char productName[50];
    float price;
    int quantity;
} Product;
int main() {
    FILE *filePtr;
    Product newProduct;
    Product currentProduct;
    float totalInventoryValue = 0.0;
    int productCount = 0;
    printf("Yeni Urun Ekleme:\n");
    printf("Urun ID: ");
    scanf("%d", &newProduct.productID);
    printf("Urun Adi (max 49 karakter): ");
    scanf("%s", newProduct.productName);
    printf("Fiyat: ");
    scanf("%f", &newProduct.price);
    printf("Miktar: ");
    scanf("%d", &newProduct.quantity);
    filePtr = fopen("products.dat", "ab");
    if (filePtr == NULL) {
        printf("Hata: Dosya acilamadi.\n");
        return 1;
    }
    fwrite(&newProduct, sizeof(Product), 1, filePtr);
    fclose(filePtr);
    printf("Urun basariyla eklendi.\n\n");
    printf("Mevcut Urunler:\n");
    filePtr = fopen("products.dat", "rb");
    if (filePtr == NULL) {
        printf("Hata: Dosya okuma icin acilamadi.\n");
        return 1;
    }
    printf("%-5s %-20s %-10s %-10s\n", "ID", "Ad", "Fiyat", "Miktar");
    printf("--------------------------------------------------\n");
    while (fread(&currentProduct, sizeof(Product), 1, filePtr) == 1) {
        printf("%-5d %-20s %-10.2f %-10d\n", 
               currentProduct.productID, 
               currentProduct.productName, 
               currentProduct.price, 
               currentProduct.quantity);
        totalInventoryValue += (currentProduct.price * currentProduct.quantity);
        productCount++;
    }
    fclose(filePtr);
    printf("--------------------------------------------------\n");
    if (productCount > 0) {
        printf("Toplam Envanter Degeri: %.2f\n", totalInventoryValue);
    } else {
        printf("Envanterde henuz urun bulunmamaktadir.\n");
    }
    return 0;
}