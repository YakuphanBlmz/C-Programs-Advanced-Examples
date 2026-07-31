#include <stdio.h>
int main() {
    int numbers[5] = {10, 20, 30, 40, 50};
    int sum = 0;
    int i;
    for (i = 0; i < 5; i++) {
        sum += numbers[i];
    }
    printf("Array Sum: %d\n", sum);
    return 0;
}