#include <stdio.h>
int main() {
    int arr[] = {12, 7, 24, 1, 9, 36, 5, 20, 15, 18};
    int n = sizeof(arr) / sizeof(arr[0]);
    int even_count = 0;
    int odd_count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            even_count++;
        } else {
            odd_count++;
        }
    }
    printf("Total even numbers: %d\n", even_count);
    printf("Total odd numbers: %d\n", odd_count);
    return 0;
}