#include <stdio.h>
int main() {
    int numbers[] = {10, 5, 8, 12, 3, 7, 6};
    int n = sizeof(numbers) / sizeof(numbers[0]);
    int sum_even = 0;
    int i;
    for (i = 0; i < n; i++) {
        if (numbers[i] % 2 == 0) {
            sum_even += numbers[i];
        }
    }
    printf("Sum of even numbers: %d\n", sum_even);
    return 0;
}