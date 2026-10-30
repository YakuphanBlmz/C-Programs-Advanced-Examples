#include <stdio.h>
#include <string.h>
typedef struct {
    int id;
    char name[50];
    float price;
    int stock;
} Product;
void addProduct() {
    FILE *filePointer;
    Product newProduct;
    filePointer = fopen("products.dat", "ab");
    if (filePointer == NULL) {
        printf("Dosya acma hatasi!\n");
        return;
    }
    printf("\n--- Yeni Urun Ekle ---\n");
    printf("Urun ID: ");
    scanf("%d", &newProduct.id);
    while (getchar() != '\n');
    printf("Urun Adi (max 49 karakter): ");
    fgets(newProduct.name, sizeof(newProduct.name), stdin);
    newProduct.name[strcspn(newProduct.name, "\n")] = 0;
    printf("Fiyat: ");
    scanf("%f", &newProduct.price);
    printf("Stok Miktari: ");
    scanf("%d", &newProduct.stock);
    fwrite(&newProduct, sizeof(Product), 1, filePointer);
    fclose(filePointer);
    printf("Urun basariyla eklendi.\n");
}
void listProducts() {
    FILE *filePointer;
    Product currentProduct;
    filePointer = fopen("products.dat", "rb");
    if (filePointer == NULL) {
        printf("Henuz hic urun kaydi yok veya dosya acma hatasi!\n");
        return;
    }
    printf("\n--- Tum Urunler ---\n");
    printf("%-5s %-20s %-10s %-10s\n", "ID", "AD", "FIYAT", "STOK");
    printf("--------------------------------------------------\n");
    while (fread(&currentProduct, sizeof(Product), 1, filePointer) == 1) {
        printf("%-5d %-20s %-10.2f %-10d\n", currentProduct.id, currentProduct.name, currentProduct.price, currentProduct.stock);
    }
    fclose(filePointer);
}
void calculateTotalValue() {
    FILE *filePointer;
    Product currentProduct;
    float totalValue = 0.0;
    filePointer = fopen("products.dat", "rb");
    if (filePointer == NULL) {
        printf("Henuz hic urun kaydi yok veya dosya acma hatasi!\n");
        return;
    }
    while (fread(&currentProduct, sizeof(Product), 1, filePointer) == 1) {
        totalValue += currentProduct.price * currentProduct.stock;
    }
    fclose(filePointer);
    printf("\n--- Toplam Envanter Degeri ---\n");
    printf("Toplam Deger: %.2f TL\n", totalValue);
}
int main() {
    int choice;
    do {
        printf("\n--- Envanter Yonetim Sistemi ---\n");
        printf("1. Urun Ekle\n");
        printf("2. Tum Urunleri Listele\n");
        printf("3. Toplam Envanter Degerini Hesapla\n");
        printf("0. Cikis\n");
        printf("Seciminizi yapin: ");
        scanf("%d", &choice);
        while (getchar() != '\n');
        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                listProducts();
                break;
            case 3:
                calculateTotalValue();
                break;
            case 0:
                printf("Sistemden cikiliyor...\n");
                break;
            default:
                printf("Gecersiz secim, lutfen tekrar deneyin.\n");
        }
    } while (choice != 0);
    return 0;
}