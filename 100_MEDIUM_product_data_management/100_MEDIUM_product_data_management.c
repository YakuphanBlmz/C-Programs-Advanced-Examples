#include <stdio.h>
#define MAX_PRODUCTS 5
#define MAX_NAME_LEN 50
typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    float price;
    int quantity;
} Product;
int main() {
    Product products[MAX_PRODUCTS];
    Product currentProduct;
    Product highestPriceProduct = {0, "", -1.0f, 0};
    int numProductsToEnter;
    int i;
    FILE *fp;
    printf("Kaç ürün gireceksiniz? (En fazla %d): ", MAX_PRODUCTS);
    scanf("%d", &numProductsToEnter);
    if (numProductsToEnter <= 0) {
        printf("En az bir ürün girmelisiniz. Program sonlandırılıyor.\n");
        return 1;
    }
    if (numProductsToEnter > MAX_PRODUCTS) {
        printf("Girilen ürün sayısı izin verilenin üzerinde. %d ürün işlenecek.\n", MAX_PRODUCTS);
        numProductsToEnter = MAX_PRODUCTS;
    }
    for (i = 0; i < numProductsToEnter; i++) {
        printf("\n%d. ürün bilgilerini girin:\n", i + 1);
        printf("ID: ");
        scanf("%d", &products[i].id);
        printf("Ad (boşluksuz): ");
        scanf("%s", products[i].name);
        printf("Fiyat: ");
        scanf("%f", &products[i].price);
        printf("Miktar: ");
        scanf("%d", &products[i].quantity);
    }
    fp = fopen("products.dat", "wb");
    if (fp == NULL) {
        printf("Dosya yazma modunda açılamadı!\n");
        return 1;
    }
    for (i = 0; i < numProductsToEnter; i++) {
        fwrite(&products[i], sizeof(Product), 1, fp);
    }
    fclose(fp);
    printf("\n%d ürün 'products.dat' dosyasına başarıyla kaydedildi.\n", numProductsToEnter);
    fp = fopen("products.dat", "rb");
    if (fp == NULL) {
        printf("Dosya okuma modunda açılamadı!\n");
        return 1;
    }
    printf("\n'products.dat' dosyasından okunan ürünler:\n");
    while (fread(&currentProduct, sizeof(Product), 1, fp) == 1) {
        printf("ID: %d, Ad: %s, Fiyat: %.2f, Miktar: %d\n",
               currentProduct.id, currentProduct.name, currentProduct.price, currentProduct.quantity);
        if (currentProduct.price > highestPriceProduct.price) {
            highestPriceProduct = currentProduct;
        }
    }
    fclose(fp);
    if (highestPriceProduct.price != -1.0f) {
        printf("\nEn yüksek fiyatlı ürün:\n");
        printf("ID: %d\n", highestPriceProduct.id);
        printf("Ad: %s\n", highestPriceProduct.name);
        printf("Fiyat: %.2f\n", highestPriceProduct.price);
        printf("Miktar: %d\n", highestPriceProduct.quantity);
    } else {
        printf("\nDosyadan ürün okunurken bir hata oluştu veya hiç ürün yoktu.\n");
    }
    return 0;
}