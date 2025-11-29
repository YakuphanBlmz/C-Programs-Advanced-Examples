#include <stdio.h>
int main() {
    int arr[5];
    int sum_of_evens = 0;
    int i;
    for (i = 0; i < 5; i++) {
        scanf("%d", &arr[i]);
    }
    for (i = 0; i < 5; i++) {
        if (arr[i] % 2 == 0) {
            sum_of_evens += arr[i];
        }
    }
    printf("Sum of even numbers: %d\n", sum_of_evens);
    return 0;
}