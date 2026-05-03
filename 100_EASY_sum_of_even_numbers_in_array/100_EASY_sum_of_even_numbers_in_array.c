#include <stdio.h>
int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int sum_even = 0;
    int i;
    for (i = 0; i < size; i++) {
        if (numbers[i] % 2 == 0) {
            sum_even += numbers[i];
        }
    }
    printf("The sum of even numbers is: %d\n", sum_even);
    return 0;
}