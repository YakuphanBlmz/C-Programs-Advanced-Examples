#include <stdio.h>
int main() {
    int arr[] = {5, 12, 8, 20, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = 0;
    int i;
    for (i = 0; i < n; i++) {
        sum = sum + arr[i];
    }
    printf("Dizideki elemanlarin toplami: %d\n", sum);
    return 0;
}