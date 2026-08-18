#include <stdio.h>
int main() {
    int arr[5] = {10, 25, 15, 30, 5};
    int sum = 0;
    int i;
    for (i = 0; i < 5; i++) {
        sum = sum + arr[i];
    }
    printf("Dizinin elemanlari toplami: %d\n", sum);
    return 0;
}