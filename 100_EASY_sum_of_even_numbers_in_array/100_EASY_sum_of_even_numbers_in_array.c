#include <stdio.h>
int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
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