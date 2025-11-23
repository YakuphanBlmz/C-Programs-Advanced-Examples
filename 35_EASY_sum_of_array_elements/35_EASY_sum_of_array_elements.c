#include <stdio.h>
int main() {
    int numbers[] = {10, 25, 13, 40, 55, 7, 32};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int sum = 0;
    int i;
    for (i = 0; i < size; i++) {
        sum = sum + numbers[i];
    }
    printf("Total sum of array elements: %d\n", sum);
    return 0;
}