#include <stdio.h>
int main() {
    int numbers[] = {10, -5, 20, 0, 30, -15, 40};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int positiveCount = 0;
    for (int i = 0; i < size; i++) {
        if (numbers[i] > 0) {
            positiveCount++;
        }
    }
    printf("Number of positive numbers: %d\n", positiveCount);
    return 0;
}