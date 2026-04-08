#include <stdio.h>
int main() {
    int arr[5];
    int sum = 0;
    int i;
    for (i = 0; i < 5; i++) {
        scanf("%d", &arr[i]);
    }
    for (i = 0; i < 5; i++) {
        sum = sum + arr[i];
    }
    printf("%d\n", sum);
    return 0;
}