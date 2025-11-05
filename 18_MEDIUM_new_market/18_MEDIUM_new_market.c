#include <stdio.h>
#include <math.h> // ceil ve round fonksiyonları için

// --- Sabitler ---
#define MAX_URUN 3
#define BASLANGIC_BONUS 50.0
#define BONUS_DEGERI 0.75 // 1 Puan = 0.75 TL
#define BONUS_LIMITI 100.0 // Puan kullanmak için minimum harcama

// --- Fonksiyon Protokolleri ---
float urunleri_oku_ve_topla();
void nakit_odeme(float toplam_tutar);
void kart_odeme(float toplam_tutar);
float bonus_hesapla_ve_uygula(float toplam_tutar);

int main() {
    float toplam_alisveris_tutari = 0.0;
    int odeme_secimi;

    printf("--- Yakuphan Magazasina Hos Geldiniz ---\n");

    // 1. Ürünleri Okutma ve Toplam Fiyatı Hesaplama
    toplam_alisveris_tutari = urunleri_oku_ve_topla();

    // 2. Bonus Uygulama (Gerekli Kontroller ile)
    float indirimli_tutar = bonus_hesapla_ve_uygula(toplam_alisveris_tutari);

    printf("\n--- Odeme Secimi ---\n");
    printf("1) Kredi Karti\n");
    printf("2) Nakit\n");
    printf("3) Bonus Puan Kullan (Gecersiz)\n"); // Puan zaten uygulanmış olacak

    // Geçerli bir seçim yapılana kadar döngü
    do {
        printf("Lutfen odeme seciminizi girin (1 veya 2): ");
        if (scanf("%d", &odeme_secimi) != 1) {
            // Hata durumunda girdi tamponunu temizle
            while (getchar() != '\n');
            odeme_secimi = 0; // Tekrar döngüyü zorla
            continue;
        }
    } while (odeme_secimi < 1 || odeme_secimi > 2);

    // 3. Ödeme İşlemi
    switch (odeme_secimi) {
        case 1:
            kart_odeme(indirimli_tutar);
            break;
        case 2:
            nakit_odeme(indirimli_tutar);
            break;
        default:
            printf("Gecersiz odeme secenegi.\n");
            break;
    }

    return 0;
}

// Ürün barkodlarını okur ve toplam tutarı hesaplar (Maks. 3 ürün kısıtlı).
float urunleri_oku_ve_topla() {
    float toplam = 0.0;
    float urun_fiyati;
    int i;

    printf("!! Dikkat: Maksimum %d adet urun okutabilirsiniz (Bakim nedeniyle).\n", MAX_URUN);

    for (i = 1; i <= MAX_URUN; i++) {
        printf("%d. urun fiyatini girin (TL, ornek: 34.50): ", i);
        if (scanf("%f", &urun_fiyati) != 1 || urun_fiyati < 0) {
            printf("Hata! Gecersiz fiyat girisi. Program sonlandiriliyor.\n");
            return 0.0;
        }
        toplam += urun_fiyati;
    }

    printf("\nToplam urun sayisi: %d\n", MAX_URUN);
    printf("Indirimsiz Toplam Tutar: %.2f TL\n", toplam);
    return toplam;
}

// Bonus puanı hesaplar ve uygulanıp uygulanmayacağına karar verir.
float bonus_hesapla_ve_uygula(float toplam_tutar) {
    float indirimli_tutar = toplam_tutar;
    float bonus_TL_degeri = BASLANGIC_BONUS * BONUS_DEGERI;

    printf("\n--- Bonus Puan Kontrolu ---\n");
    printf("Mevcut bonus puaniniz: %.0f Puan (%.2f TL)\n", BASLANGIC_BONUS, bonus_TL_degeri);

    if (toplam_tutar >= BONUS_LIMITI) {
        printf("Kosul saglandi (>%.2f TL). Bonus puan uygulanacak.\n", BONUS_LIMITI);
        indirimli_tutar = toplam_tutar - bonus_TL_degeri;
        // Tutarın negatif olmamasını sağla
        if (indirimli_tutar < 0) {
            indirimli_tutar = 0.0;
        }
        printf("50 Puan (%.2f TL) indirim uygulandi.\n", bonus_TL_degeri);
    } else {
        printf("Kosul saglanmadi (<%.2f TL). Bonus puan uygulanamadi.\n", BONUS_LIMITI);
    }

    printf("ODENECEK SON TUTAR: %.2f TL\n", indirimli_tutar);
    return indirimli_tutar;
}

// Nakit ödeme işlemini yapar ve para üstünü hesaplar.
void nakit_odeme(float toplam_tutar) {
    float odenecek_tutar = 0.0;
    float para_ustu = 0.0;
    float kurus_bonus = 0.0;
    float verilecek_TL_ustu = 0.0;

    printf("\n--- Nakit Odeme ---\n");
    printf("Odenecek Tutar: %.2f TL\n", toplam_tutar);

    // Yeterli nakit tutar girilene kadar döngü
    do {
        printf("Lutfen odeyeceginiz nakit miktari girin: ");
        if (scanf("%f", &odenecek_tutar) != 1 || odenecek_tutar < toplam_tutar) {
            printf("Hata! Gecersiz miktar veya yetersiz nakit. Lutfen tekrar girin.\n");
        }
    } while (odenecek_tutar < toplam_tutar);

    // Para üstü hesaplama
    para_ustu = odenecek_tutar - toplam_tutar;
    printf("\nToplam Para Ustu: %.2f TL\n", para_ustu);

    // Kuruş ayırma ve bonus verme kuralı: 1 TL haricindeki demir paralar (kuruşlar) bonus olur.
    // Para üstünü en yakın alt tam sayıya yuvarlayarak TL üstünü bulalım.
    verilecek_TL_ustu = floorf(para_ustu);

    // Kalan kuruş miktarını hesapla (sadece 1 TL'nin altındaki miktar)
    kurus_bonus = para_ustu - verilecek_TL_ustu;

    printf("\n--- Para Ustu Islemleri ---\n");
    printf("Verilecek Para Ustu (Tam TL): %.0f TL\n", verilecek_TL_ustu);

    // Kuruş bonusunu sisteme aktar
    if (kurus_bonus > 0.009) { // Çok küçük kayan nokta hatalarını engellemek için
        float kazanilan_bonus = kurus_bonus / BONUS_DEGERI;
        printf("Kalan kurus (%.2f TL), %.2f puan olarak sisteminize aktarilmistir.\n", kurus_bonus, kazanilan_bonus);
    } else {
        printf("Kurus kalmadi.\n");
    }

    printf("\nIslem Basarili! Bizi tercih ettiginiz icin tesekkurler.\n");
}

// Kredi kartı ödeme işlemini simüle eder.
void kart_odeme(float toplam_tutar) {
    printf("\n--- Kredi Karti Odeme ---\n");
    printf("Odenecek Tutar: %.2f TL\n", toplam_tutar);
    printf("Lutfen kartinizi okutunuz.\n");
    printf("Odeme alinmistir. Bizi tercih ettiginiz icin tesekkurler.\n");
}