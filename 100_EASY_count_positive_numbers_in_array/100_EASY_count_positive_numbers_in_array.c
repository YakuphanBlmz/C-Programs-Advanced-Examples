#include <stdio.h>
int main() {
    int arr[] = {1, -2, 3, 0, 5, -1, 7, 10, -5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int count = 0;
    int i;
    for (i = 0; i < n; i++) {
        if (arr[i] > 0) {
            count++;
        }
    }
    printf("Pozitif sayilarin sayisi: %d\n", count);
    return 0;
}