#include <stdio.h>
int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    int n = sizeof(numbers) / sizeof(numbers[0]);
    int sum = 0;
    int i;
    for (i = 0; i < n; i++) {
        sum += numbers[i];
    }
    printf("Dizinin elemanları toplamı: %d\n", sum);
    return 0;
}