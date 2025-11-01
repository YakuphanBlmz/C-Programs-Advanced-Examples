#include <stdio.h>
int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    int sum_of_evens = 0;
    int i;
    for (i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            sum_of_evens = sum_of_evens + arr[i];
        }
    }
    printf("Sum of even numbers: %d\n", sum_of_evens);
    return 0;
}
