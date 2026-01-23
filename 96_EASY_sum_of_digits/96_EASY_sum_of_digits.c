#include <stdio.h>
int main() {
    int number;
    int sum = 0;
    int digit;
    scanf("%d", &number);
    if (number < 0) {
        number = -number;
    }
    if (number == 0) {
        sum = 0;
    } else {
        while (number > 0) {
            digit = number % 10;
            sum = sum + digit;
            number = number / 10;
        }
    }
    printf("%d\n", sum);
    return 0;
}