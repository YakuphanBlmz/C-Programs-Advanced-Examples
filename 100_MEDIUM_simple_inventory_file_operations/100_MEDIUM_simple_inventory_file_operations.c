#include <stdio.h>
typedef struct {
    int id;
    char name[50];
    int quantity;
} InventoryItem;
int main() {
    FILE *fp;
    InventoryItem newItem;
    InventoryItem currentItem;
    printf("Yeni Envanter Ogesini Girin:\n");
    printf("ID: ");
    scanf("%d", &newItem.id);
    printf("Ad (bosluksuz): ");
    scanf("%49s", newItem.name);
    printf("Miktar: ");
    scanf("%d", &newItem.quantity);
    fp = fopen("inventory.dat", "ab");
    if (fp == NULL) {
        printf("Hata: Dosya acilamadi!\n");
        return 1;
    }
    fwrite(&newItem, sizeof(InventoryItem), 1, fp);
    fclose(fp);
    printf("Yeni oge basariyla eklendi.\n\n");
    printf("Mevcut Envanter:\n");
    fp = fopen("inventory.dat", "rb");
    if (fp == NULL) {
        printf("Hata: Envanter dosyasi okuma icin acilamadi (belki henuz oge yok).\n");
        return 1;
    }
    printf("%-5s %-20s %-10s\n", "ID", "Ad", "Miktar");
    printf("----------------------------------------\n");
    size_t items_read;
    while ((items_read = fread(&currentItem, sizeof(InventoryItem), 1, fp)) == 1) {
        printf("%-5d %-20s %-10d\n", currentItem.id, currentItem.name, currentItem.quantity);
    }
    fclose(fp);
    return 0;
}