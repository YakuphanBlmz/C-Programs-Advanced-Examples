#include <stdio.h>
int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15, 20};
    int n = sizeof(arr) / sizeof(arr[0]);
    int evenCount = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            evenCount++;
        }
    }
    printf("Even numbers count: %d\n", evenCount);
    return 0;
}