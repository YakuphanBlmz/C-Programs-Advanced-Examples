#include <stdio.h>
#include <string.h>
#define MAX_PRODUCTS 10
#define MAX_NAME_LEN 50
#define INVENTORY_FILE "inventory.txt"
typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int quantity;
    float price;
} Product;
int main() {
    Product inventory[MAX_PRODUCTS];
    int productCount = 0;
    int choice;
    FILE *file;
    int i;
    int foundIndex;
    int searchId;
    int newQuantity;
    file = fopen(INVENTORY_FILE, "r");
    if (file != NULL) {
        while (productCount < MAX_PRODUCTS &&
               fscanf(file, "%d %s %d %f",
                      &inventory[productCount].id,
                      inventory[productCount].name,
                      &inventory[productCount].quantity,
                      &inventory[productCount].price) == 4) {
            productCount++;
        }
        fclose(file);
        printf("Envanter %s dosyasindan yuklendi.\n", INVENTORY_FILE);
    } else {
        printf("'%s' dosyasi bulunamadi veya acilamadi. Yeni bir envanter olusturulacak.\n", INVENTORY_FILE);
    }
    do {
        printf("\n--- Envanter Yonetimi ---\n");
        printf("1. Envanteri Goster\n");
        printf("2. Urun Miktari Guncelle\n");
        printf("3. Cikis\n");
        printf("Seciminizi yapin: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("\n--- Mevcut Envanter ---\n");
                if (productCount == 0) {
                    printf("Envanter bos.\n");
                } else {
                    printf("%-5s %-20s %-10s %-10s\n", "ID", "Isim", "Miktar", "Fiyat");
                    for (i = 0; i < productCount; i++) {
                        printf("%-5d %-20s %-10d %-10.2f\n",
                               inventory[i].id,
                               inventory[i].name,
                               inventory[i].quantity,
                               inventory[i].price);
                    }
                }
                break;
            case 2:
                printf("Guncellenecek urun ID'sini girin: ");
                scanf("%d", &searchId);
                foundIndex = -1;
                for (i = 0; i < productCount; i++) {
                    if (inventory[i].id == searchId) {
                        foundIndex = i;
                        break;
                    }
                }
                if (foundIndex != -1) {
                    printf("Urun bulundu: ID %d, Isim %s, Mevcut Miktar %d\n",
                           inventory[foundIndex].id,
                           inventory[foundIndex].name,
                           inventory[foundIndex].quantity);
                    printf("Yeni miktari girin: ");
                    scanf("%d", &newQuantity);
                    if (newQuantity >= 0) {
                        inventory[foundIndex].quantity = newQuantity;
                        printf("Miktar basariyla guncellendi.\n");
                    } else {
                        printf("Gecersiz miktar. Miktar negatif olamaz.\n");
                    }
                } else {
                    printf("Urun bulunamadi.\n");
                }
                break;
            case 3:
                printf("Programdan cikiliyor. Envanter kaydediliyor...\n");
                break;
            default:
                printf("Gecersiz secim. Lutfen tekrar deneyin.\n");
                while (getchar() != '\n');
                break;
        }
    } while (choice != 3);
    file = fopen(INVENTORY_FILE, "w");
    if (file != NULL) {
        for (i = 0; i < productCount; i++) {
            fprintf(file, "%d %s %d %.2f\n",
                    inventory[i].id,
                    inventory[i].name,
                    inventory[i].quantity,
                    inventory[i].price);
        }
        fclose(file);
        printf("Envanter basariyla '%s' dosyasina kaydedildi.\n", INVENTORY_FILE);
    } else {
        printf("Hata: Envanter '%s' dosyasina kaydedilemedi.\n", INVENTORY_FILE);
    }
    return 0;
}