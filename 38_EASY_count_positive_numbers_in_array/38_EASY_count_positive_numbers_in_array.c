#include <stdio.h>
int main() {
    int arr[] = {-5, 10, 0, 3, -2, 7, -1, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int positive_count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            positive_count++;
        }
    }
    printf("%d\n", positive_count);
    return 0;
}