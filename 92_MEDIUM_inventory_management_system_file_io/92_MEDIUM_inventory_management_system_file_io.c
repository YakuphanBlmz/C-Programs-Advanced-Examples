#include <stdio.h>
#define MAX_PRODUCTS 3
#define NAME_LENGTH 50
#define FILENAME "products.dat"
typedef struct {
    int id;
    char name[NAME_LENGTH];
    float price;
} Product;
int main() {
    Product inventory[MAX_PRODUCTS];
    Product loaded_inventory[MAX_PRODUCTS];
    FILE *file_ptr;
    int i;
    printf("Urun bilgilerini giriniz (%d urun):\n", MAX_PRODUCTS);
    for (i = 0; i < MAX_PRODUCTS; i++) {
        printf("Urun %d ID: ", i + 1);
        scanf("%d", &inventory[i].id);
        printf("Urun %d Adi: ", i + 1);
        scanf("%s", inventory[i].name);
        printf("Urun %d Fiyati: ", i + 1);
        scanf("%f", &inventory[i].price);
    }
    file_ptr = fopen(FILENAME, "wb");
    if (file_ptr == NULL) {
        printf("Dosya yazma hatasi!\n");
        return 1;
    }
    fwrite(inventory, sizeof(Product), MAX_PRODUCTS, file_ptr);
    fclose(file_ptr);
    printf("\nUrunler '%s' dosyasina kaydedildi.\n", FILENAME);
    file_ptr = fopen(FILENAME, "rb");
    if (file_ptr == NULL) {
        printf("Dosya okuma hatasi!\n");
        return 1;
    }
    fread(loaded_inventory, sizeof(Product), MAX_PRODUCTS, file_ptr);
    fclose(file_ptr);
    printf("Urunler '%s' dosyasindan okundu.\n", FILENAME);
    Product highest_price_product;
    highest_price_product = loaded_inventory[0];
    for (i = 1; i < MAX_PRODUCTS; i++) {
        if (loaded_inventory[i].price > highest_price_product.price) {
            highest_price_product = loaded_inventory[i];
        }
    }
    printf("\nEn yuksek fiyata sahip urun:\n");
    printf("ID: %d\n", highest_price_product.id);
    printf("Ad: %s\n", highest_price_product.name);
    printf("Fiyat: %.2f\n", highest_price_product.price);
    return 0;
}