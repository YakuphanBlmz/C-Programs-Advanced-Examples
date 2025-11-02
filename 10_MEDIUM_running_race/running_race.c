#include <stdio.h>

#define TOTAL_CONTESTANTS 200

int getJerseyNumber(int personNumber) {
    return TOTAL_CONTESTANTS - personNumber + 1;
}

int getPersonNumber(int jerseyNumber) {
    return TOTAL_CONTESTANTS - jerseyNumber + 1;
}

void function_b(int jersey1, int jersey2, int jersey3) {
    int max = jersey1;
    int min = jersey1;

    if (jersey2 > max) {
        max = jersey2;
    }
    if (jersey3 > max) {
        max = jersey3;
    }

    if (jersey2 < min) {
        min = jersey2;
    }
    if (jersey3 < min) {
        min = jersey3;
    }

    int diff = max - min;
    int loserPerson = getPersonNumber(diff);

    printf("\nb) Kazanan formalarin en buyugu (%d) ile en kucugu (%d) arasindaki fark: %d\n", max, min, diff);
    printf("   Bu fark, kaybeden %d. kisinin forma numarasina denktir.\n", loserPerson);
}

void function_a(int winner1, int winner2, int winner3) {
    int jersey1 = getJerseyNumber(winner1);
    int jersey2 = getJerseyNumber(winner2);
    int jersey3 = getJerseyNumber(winner3);

    printf("a) Yarismayi kazanan kisilerin forma numaralari:\n");
    printf("   %d. kisi (kazanan): %d numarali forma\n", winner1, jersey1);
    printf("   %d. kisi (kazanan): %d numarali forma\n", winner2, jersey2);
    printf("   %d. kisi (kazanan): %d numarali forma\n", winner3, jersey3);

    function_b(jersey1, jersey2, jersey3);
}

void function_c(int winner1, int winner2, int winner3) {
    int redCount = 0;
    int blueCount = 0;
    int currentJersey;

    for (int person = 1; person <= TOTAL_CONTESTANTS; person++) {
        
        if (person == winner1 || person == winner2 || person == winner3) {
            continue;
        }

        currentJersey = getJerseyNumber(person);
        if (currentJersey % 2 == 0) {
            blueCount++;
        } else {
            redCount++;
        }
    }

    printf("\nc) Kaybeden 197 kisi icin tisort dagilimi:\n");
    printf("   Mavi Tisort (Cift Forma Numarasi): %d adet\n", blueCount);
    printf("   Kirmizi Tisort (Tek Forma Numarasi): %d adet\n", redCount);
}

int main() {
    int winnerPerson1 = 25;
    int winnerPerson2 = 59;
    int winnerPerson3 = 143;

    function_a(winnerPerson1, winnerPerson2, winnerPerson3);
    function_c(winnerPerson1, winnerPerson2, winnerPerson3);

    return 0;
}