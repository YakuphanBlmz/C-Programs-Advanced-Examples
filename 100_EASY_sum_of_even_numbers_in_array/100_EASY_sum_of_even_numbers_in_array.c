#include <stdio.h>
int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int even_sum = 0;
    int i;
    for (i = 0; i < size; i++) {
        if (numbers[i] % 2 == 0) {
            even_sum += numbers[i];
        }
    }
    printf("Sum of even numbers: %d\n", even_sum);
    return 0;
}