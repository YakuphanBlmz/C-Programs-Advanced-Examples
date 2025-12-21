#include <stdio.h>
int main() {
    int number;
    int sum = 0;
    int digit;
    scanf("%d", &number);
    while (number > 0) {
        digit = number % 10;
        sum += digit;
        number /= 10;
    }
    printf("%d\n", sum);
    return 0;
}