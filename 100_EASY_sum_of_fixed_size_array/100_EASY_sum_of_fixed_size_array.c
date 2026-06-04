#include <stdio.h>
int main() {
    int arr[5];
    int i;
    int sum = 0;
    printf("Lutfen 5 adet tam sayi girin:\n");
    for (i = 0; i < 5; i++) {
        printf("Eleman %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
    for (i = 0; i < 5; i++) {
        sum += arr[i];
    }
    printf("Dizideki elemanlarin toplami: %d\n", sum);
    return 0;
}