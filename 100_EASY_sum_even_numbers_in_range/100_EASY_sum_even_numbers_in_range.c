#include <stdio.h>
int main() {
    int N;
    int sum = 0;
    int i;
    printf("Enter a positive integer N: ");
    scanf("%d", &N);
    for (i = 1; i <= N; i++) {
        if (i % 2 == 0) {
            sum = sum + i;
        }
    }
    printf("Sum of even numbers from 1 to %d is: %d\n", N, sum);
    return 0;
}