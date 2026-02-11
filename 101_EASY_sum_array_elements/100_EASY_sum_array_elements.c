#include <stdio.h>
int main() {
    int arr[] = {10, 25, 30, 45, 50};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum = sum + arr[i];
    }
    printf("Dizinin elemanlari: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("Dizi elemanlarinin toplami: %d\n", sum);
    return 0;
}