#include <stdio.h>
int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int evenCount = 0;
    for (int i = 0; i < size; i++) {
        if (numbers[i] % 2 == 0) {
            evenCount++;
        }
    }
    printf("Number of even integers: %d\n", evenCount);
    return 0;
}