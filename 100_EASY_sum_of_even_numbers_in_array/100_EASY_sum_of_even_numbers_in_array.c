#include <stdio.h>
int main() {
    int arr[] = {12, 5, 8, 20, 3, 15, 10, 7, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum_of_evens = 0;
    int i;
    for (i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            sum_of_evens += arr[i];
        }
    }
    printf("Sum of even numbers: %d\n", sum_of_evens);
    return 0;
}