#include <stdio.h>
int main() {
    int numbers[] = {-5, 10, 0, 20, -3, 15, 0, 8};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int positiveCount = 0;
    for (int i = 0; i < size; i++) {
        if (numbers[i] > 0) {
            positiveCount++;
        }
    }
    printf("Number of positive elements: %d\n", positiveCount);
    return 0;
}