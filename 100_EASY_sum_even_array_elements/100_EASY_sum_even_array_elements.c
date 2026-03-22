#include <stdio.h>
int main() {
    int arr[5];
    int sum_even = 0;
    int i;
    for (i = 0; i < 5; i++) {
        scanf("%d", &arr[i]);
    }
    for (i = 0; i < 5; i++) {
        if (arr[i] % 2 == 0) {
            sum_even += arr[i];
        }
    }
    printf("%d\n", sum_even);
    return 0;
}