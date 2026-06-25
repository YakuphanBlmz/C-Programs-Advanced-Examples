#include <stdio.h>
int main() {
    int arr[] = {12, 7, 24, 15, 8, 30, 11, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int even_count = 0;
    int odd_count = 0;
    int i;
    for (i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            even_count++;
        } else {
            odd_count++;
        }
    }
    printf("Number of even elements: %d\n", even_count);
    printf("Number of odd elements: %d\n", odd_count);
    return 0;
}