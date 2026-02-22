#include <stdio.h>
int main() {
    int arr[] = {10, 5, 8, 12, 3, 7, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum_even = 0;
    int i;
    for (i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            sum_even += arr[i];
        }
    }
    printf("Sum of even numbers: %d\n", sum_even);
    return 0;
}