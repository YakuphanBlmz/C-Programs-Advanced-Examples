#include <stdio.h>
int main() {
    int arr[] = {10, 23, 14, 7, 30, 11, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = 0;
    int i;
    for (i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            sum += arr[i];
        }
    }
    printf("Dizideki çift sayıların toplamı: %d\n", sum);
    return 0;
}