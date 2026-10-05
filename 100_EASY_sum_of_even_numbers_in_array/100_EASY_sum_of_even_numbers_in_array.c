#include <stdio.h>
int main() {
    int arr[5] = {10, 3, 8, 15, 20};
    int sum_even = 0;
    int i;
    for (i = 0; i < 5; i++) {
        if (arr[i] % 2 == 0) {
            sum_even += arr[i];
        }
    }
    printf("Sum of even numbers: %d\n", sum_even);
    return 0;
}