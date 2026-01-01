#include <stdio.h>
int main() {
    int arr[] = {12, 7, 24, 5, 10, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum_even = 0;
    int i;
    for (i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            sum_even += arr[i];
        }
    }
    printf("Dizideki cift sayilarin toplami: %d\n", sum_even);
    return 0;
}