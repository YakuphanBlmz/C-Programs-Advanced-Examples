#include <stdio.h>
int main() {
    int arr[] = {10, -5, 0, 7, -2, 3, -8, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int positiveCount = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            positiveCount++;
        }
    }
    printf("Dizideki pozitif sayilarin adedi: %d\n", positiveCount);
    return 0;
}