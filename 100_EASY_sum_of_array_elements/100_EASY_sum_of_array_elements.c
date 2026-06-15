#include <stdio.h>
int main() {
    int arr[5] = {10, 25, 30, 45, 50};
    int sum = 0;
    int i;
    for (i = 0; i < 5; i++) {
        sum = sum + arr[i];
    }
    printf("The sum of array elements is: %d\n", sum);
    return 0;
}