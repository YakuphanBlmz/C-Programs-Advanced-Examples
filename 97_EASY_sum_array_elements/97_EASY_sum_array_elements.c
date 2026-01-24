#include <stdio.h>
int main() {
    int numbers[] = {10, 25, 5, 30, 15};
    int sum = 0;
    int i;
    int size = sizeof(numbers) / sizeof(numbers[0]);
    for (i = 0; i < size; i++) {
        sum = sum + numbers[i];
    }
    printf("Dizi elemanlarının toplamı: %d\n", sum);
    return 0;
}