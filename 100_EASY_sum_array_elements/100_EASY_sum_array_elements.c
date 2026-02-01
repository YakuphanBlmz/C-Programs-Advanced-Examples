#include <stdio.h>
int main() {
    int N;
    scanf("%d", &N);
    int arr[N];
    int sum = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
        sum += arr[i];
    }
    printf("%d\n", sum);
    return 0;
}