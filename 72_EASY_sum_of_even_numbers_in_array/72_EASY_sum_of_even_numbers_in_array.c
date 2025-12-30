#include <stdio.h>
int main() {
    int arr[] = {10, 15, 20, 25, 30, 35, 40};
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