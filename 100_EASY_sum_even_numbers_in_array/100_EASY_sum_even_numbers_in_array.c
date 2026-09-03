#include <stdio.h>
int main() {
    int numbers[] = {10, 5, 20, 15, 30, 7};
    int n = sizeof(numbers) / sizeof(numbers[0]);
    int sum_of_evens = 0;
    int i;
    for (i = 0; i < n; i++) {
        if (numbers[i] % 2 == 0) {
            sum_of_evens += numbers[i];
        }
    }
    printf("Sum of even numbers: %d\n", sum_of_evens);
    return 0;
}