#include <stdio.h>
typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
} Product;
#define MAX_PRODUCTS 3
#define FILENAME "products.dat"
int main() {
    Product products_to_write[MAX_PRODUCTS];
    Product products_read[MAX_PRODUCTS];
    FILE *file_ptr;
    int i;
    printf("Urun bilgilerini girin (%d adet):\n", MAX_PRODUCTS);
    for (i = 0; i < MAX_PRODUCTS; i++) {
        printf("Urun %d ID: ", i + 1);
        scanf("%d", &products_to_write[i].id);
        while (getchar() != '\n');
        printf("Urun %d Ad: ", i + 1);
        scanf("%49s", products_to_write[i].name);
        while (getchar() != '\n');
        printf("Urun %d Fiyat: ", i + 1);
        scanf("%f", &products_to_write[i].price);
        while (getchar() != '\n');
        printf("Urun %d Miktar: ", i + 1);
        scanf("%d", &products_to_write[i].quantity);
        while (getchar() != '\n');
    }
    file_ptr = fopen(FILENAME, "wb");
    if (file_ptr == NULL) {
        printf("Dosya yazma hatasi!\n");
        return 1;
    }
    fwrite(products_to_write, sizeof(Product), MAX_PRODUCTS, file_ptr);
    fclose(file_ptr);
    printf("\nUrunler \"%s\" dosyasina basariyla yazildi.\n", FILENAME);
    file_ptr = fopen(FILENAME, "rb");
    if (file_ptr == NULL) {
        printf("Dosya okuma hatasi!\n");
        return 1;
    }
    fread(products_read, sizeof(Product), MAX_PRODUCTS, file_ptr);
    fclose(file_ptr);
    printf("\n\"%s\" dosyasindan okunan urunler:\n", FILENAME);
    for (i = 0; i < MAX_PRODUCTS; i++) {
        printf("ID: %d, Ad: %s, Fiyat: %.2f, Miktar: %d\n",
               products_read[i].id,
               products_read[i].name,
               products_read[i].price,
               products_read[i].quantity);
    }
    return 0;
}