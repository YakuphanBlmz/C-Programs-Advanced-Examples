#include <stdio.h>
#define NUM_PRODUCTS 3
#define NAME_MAX_LEN 50
typedef struct {
    int id;
    char name[NAME_MAX_LEN];
    float price;
    int stock;
} Product;
int main() {
    Product products[NUM_PRODUCTS];
    Product readProducts[NUM_PRODUCTS];
    FILE *fp;
    int i;
    printf("Lutfen %d urun icin bilgi girin:\n", NUM_PRODUCTS);
    for (i = 0; i < NUM_PRODUCTS; i++) {
        printf("\nUrun %d (ID, Ad, Fiyat, Stok):\n", i + 1);
        printf("ID: ");
        scanf("%d", &products[i].id);
        printf("Ad: ");
        scanf("%s", products[i].name); 
        printf("Fiyat: ");
        scanf("%f", &products[i].price);
        printf("Stok: ");
        scanf("%d", &products[i].stock);
    }
    fp = fopen("products.bin", "wb");
    if (fp == NULL) {
        printf("Hata: Dosya yazma modunda acilamadi!\n");
        return 1;
    }
    fwrite(products, sizeof(Product), NUM_PRODUCTS, fp);
    fclose(fp);
    printf("\nUrunler 'products.bin' dosyasina basariyla yazildi.\n");
    fp = fopen("products.bin", "rb");
    if (fp == NULL) {
        printf("Hata: Dosya okuma modunda acilamadi!\n");
        return 1;
    }
    fread(readProducts, sizeof(Product), NUM_PRODUCTS, fp);
    fclose(fp);
    printf("\n'products.bin' dosyasindan okunan urunler:\n");
    for (i = 0; i < NUM_PRODUCTS; i++) {
        printf("ID: %d, Ad: %s, Fiyat: %.2f, Stok: %d\n",
               readProducts[i].id,
               readProducts[i].name,
               readProducts[i].price,
               readProducts[i].stock);
    }
    return 0;
}