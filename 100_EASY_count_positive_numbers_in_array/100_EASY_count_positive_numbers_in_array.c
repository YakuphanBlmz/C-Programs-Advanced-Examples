#include <stdio.h>
int main() {
    int arr[] = {1, -2, 3, 0, 5, -6, 7, 10, -4, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int positive_count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            positive_count++;
        }
    }
    printf("Dizideki pozitif sayi adedi: %d\n", positive_count);
    return 0;
}