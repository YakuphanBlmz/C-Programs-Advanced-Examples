#include <stdio.h>
int main() {
    int arr[] = {10, -5, 20, -1, 15, 0, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = 0;
    int i;
    for (i = 0; i < n; i++) {
        if (arr[i] > 0) {
            sum += arr[i];
        }
    }
    printf("Sum of positive numbers: %d\n", sum);
    return 0;
}