#include <stdio.h>
int main() {
    int arr[] = {10, 5, 8, 12, 3, 7, 6, 15, 20};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum_of_evens = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            sum_of_evens += arr[i];
        }
    }
    printf("Sum of even numbers: %d\n", sum_of_evens);
    return 0;
}