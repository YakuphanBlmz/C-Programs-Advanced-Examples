#include <stdio.h>
int main() {
    int arr[] = {5, 12, 8, 20, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    printf("Dizi elemanlarinin toplami: %d\n", sum);
    return 0;
}