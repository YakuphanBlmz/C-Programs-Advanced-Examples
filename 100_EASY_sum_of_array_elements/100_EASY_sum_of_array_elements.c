#include <stdio.h>
int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int sum = 0;
    int i;
    for (i = 0; i < 5; i++) {
        sum = sum + arr[i];
    }
    printf("Dizi elemanlarının toplamı: %d\n", sum);
    return 0;
}