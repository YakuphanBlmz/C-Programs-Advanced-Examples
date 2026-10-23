#include <stdio.h>
int main() {
    int arr[] = {12, 7, 24, 1, 9, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = 0;
    int i;
    for (i = 0; i < n; i++) {
        sum = sum + arr[i];
    }
    printf("Sum of array elements: %d\n", sum);
    return 0;
}