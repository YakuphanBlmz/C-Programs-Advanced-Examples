#include <stdio.h>
#include <string.h>
#define MAX_AD_UZUNLUGU 50
#define MAX_URUNLER 3
#define DOSYA_ADI "urunler.bin"
typedef struct {
    int urunID;
    char urunAdi[MAX_AD_UZUNLUGU];
    int stokMiktari;
} Urun;
int main() {
    Urun urunlerYaz[MAX_URUNLER];
    Urun urunlerOku[MAX_URUNLER];
    FILE *dosya;
    int i;
    int toplamStok = 0;
    urunlerYaz[0].urunID = 101;
    strcpy(urunlerYaz[0].urunAdi, "Klavye");
    urunlerYaz[0].stokMiktari = 150;
    urunlerYaz[1].urunID = 102;
    strcpy(urunlerYaz[1].urunAdi, "Fare");
    urunlerYaz[1].stokMiktari = 200;
    urunlerYaz[2].urunID = 103;
    strcpy(urunlerYaz[2].urunAdi, "Monitor");
    urunlerYaz[2].stokMiktari = 75;
    dosya = fopen(DOSYA_ADI, "wb");
    if (dosya == NULL) {
        printf("Dosya yazılamadı: %s\n", DOSYA_ADI);
        return 1;
    }
    fwrite(urunlerYaz, sizeof(Urun), MAX_URUNLER, dosya);
    fclose(dosya);
    printf("Ürünler dosyaya yazıldı: %s\n", DOSYA_ADI);
    dosya = fopen(DOSYA_ADI, "rb");
    if (dosya == NULL) {
        printf("Dosya okunamadı: %s\n", DOSYA_ADI);
        return 1;
    }
    fread(urunlerOku, sizeof(Urun), MAX_URUNLER, dosya);
    fclose(dosya);
    printf("Ürünler dosyadan okundu.\n\n");
    printf("Okunan Ürün Detayları:\n");
    for (i = 0; i < MAX_URUNLER; i++) {
        printf("ID: %d, Adı: %s, Stok: %d\n", 
               urunlerOku[i].urunID, 
               urunlerOku[i].urunAdi, 
               urunlerOku[i].stokMiktari);
        toplamStok += urunlerOku[i].stokMiktari;
    }
    printf("\nToplam Stok Miktarı: %d\n", toplamStok);
    return 0;
}