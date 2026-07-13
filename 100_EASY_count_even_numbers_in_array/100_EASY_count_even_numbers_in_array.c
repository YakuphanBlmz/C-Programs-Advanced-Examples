#include <stdio.h>
int main() {
    int arr[] = {10, 5, 22, 13, 7, 30, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int even_count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            even_count++;
        }
    }
    printf("Dizideki cift sayi adedi: %d\n", even_count);
    return 0;
}