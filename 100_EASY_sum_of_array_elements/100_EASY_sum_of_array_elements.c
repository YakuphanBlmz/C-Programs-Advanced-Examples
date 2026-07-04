#include <stdio.h>
int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = 0;
    int i;
    for (i = 0; i < n; i++) {
        sum += arr[i];
    }
    printf("Array sum: %d\n", sum);
    return 0;
}