#include <stdio.h>
int main() {
    int numbers[] = {10, 25, 5, 30, 15};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += numbers[i];
    }
    printf("Array elements sum: %d\n", sum);
    return 0;
}