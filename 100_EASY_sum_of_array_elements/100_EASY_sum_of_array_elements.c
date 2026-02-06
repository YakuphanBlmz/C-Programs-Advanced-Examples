#include <stdio.h>
int main() {
    int arr[] = {15, 25, 35, 45, 55};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = 0;
    int i;
    for (i = 0; i < n; i++) {
        sum += arr[i];
    }
    printf("Dizinin elemanları toplamı: %d\n", sum);
    return 0;
}