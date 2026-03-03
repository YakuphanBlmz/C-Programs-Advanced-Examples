#include <stdio.h>
int main() {
    int numbers[] = {10, -5, 20, 0, -15, 30};
    int n = sizeof(numbers) / sizeof(numbers[0]);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (numbers[i] > 0) {
            sum += numbers[i];
        }
    }
    printf("Sum of positive numbers: %d\n", sum);
    return 0;
}