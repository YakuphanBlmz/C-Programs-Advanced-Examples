#include <stdio.h>
int main() {
    int arr[] = {12, 5, 8, 17, 20, 3, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int evenSum = 0;
    int i;
    for (i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            evenSum += arr[i];
        }
    }
    printf("Sum of even numbers: %d\n", evenSum);
    return 0;
}