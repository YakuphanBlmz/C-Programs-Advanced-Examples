#include <stdio.h>
#include <string.h>
#define MAX_PRODUCTS 10
#define FILENAME "inventory.bin"
typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
} Product;
Product inventory[MAX_PRODUCTS];
int currentProductCount = 0;
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void addProduct() {
    if (currentProductCount >= MAX_PRODUCTS) {
        printf("Envanter dolu, daha fazla urun eklenemez.\n");
        return;
    }
    printf("Yeni urun bilgileri giriniz:\n");
    printf("ID: ");
    scanf("%d", &inventory[currentProductCount].id);
    clearInputBuffer();
    printf("Ad: ");
    fgets(inventory[currentProductCount].name, sizeof(inventory[currentProductCount].name), stdin);
    inventory[currentProductCount].name[strcspn(inventory[currentProductCount].name, "\n")] = 0;
    printf("Fiyat: ");
    scanf("%f", &inventory[currentProductCount].price);
    printf("Miktar: ");
    scanf("%d", &inventory[currentProductCount].quantity);
    clearInputBuffer();
    currentProductCount++;
    printf("Urun basariyla eklendi.\n");
}
void listProducts() {
    if (currentProductCount == 0) {
        printf("Envanterde urun bulunmamaktadir.\n");
        return;
    }
    printf("\n--- Mevcut Envanter ---\n");
    for (int i = 0; i < currentProductCount; i++) {
        printf("ID: %d, Ad: %s, Fiyat: %.2f, Miktar: %d\n",
               inventory[i].id,
               inventory[i].name,
               inventory[i].price,
               inventory[i].quantity);
    }
    printf("------------------------\n");
}
void saveInventory() {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("Dosya yazilamadi: %s\n", FILENAME);
        return;
    }
    fwrite(&currentProductCount, sizeof(int), 1, file);
    fwrite(inventory, sizeof(Product), currentProductCount, file);
    fclose(file);
    printf("Envanter basariyla dosyaya kaydedildi: %s\n", FILENAME);
}
void loadInventory() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Dosya okunamadi veya bulunamadi: %s\n", FILENAME);
        currentProductCount = 0;
        return;
    }
    int readCount;
    fread(&readCount, sizeof(int), 1, file);
    if (readCount > MAX_PRODUCTS) {
        printf("Yuklenmek istenen urun sayisi maksimum kapasiteyi (%d) asiyor. Yukleme iptal edildi.\n", MAX_PRODUCTS);
        fclose(file);
        return;
    }
    fread(inventory, sizeof(Product), readCount, file);
    currentProductCount = readCount;
    fclose(file);
    printf("Envanter basariyla dosyadan yuklendi: %s\n", FILENAME);
}
int main() {
    int choice;
    do {
        printf("\n--- Envanter Yonetim Sistemi ---\n");
        printf("1. Urun Ekle\n");
        printf("2. Urunleri Listele\n");
        printf("3. Envanteri Kaydet\n");
        printf("4. Envanteri Yukle\n");
        printf("5. Cikis\n");
        printf("Seciminizi yapin: ");
        scanf("%d", &choice);
        clearInputBuffer();
        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                listProducts();
                break;
            case 3:
                saveInventory();
                break;
            case 4:
                loadInventory();
                break;
            case 5:
                printf("Cikis yapiliyor...\n");
                break;
            default:
                printf("Gecersiz secim, lutfen tekrar deneyin.\n");
        }
    } while (choice != 5);
    return 0;
}