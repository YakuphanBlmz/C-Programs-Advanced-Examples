#include <stdio.h>
int main() {
    int numbers[] = {10, 5, 22, 13, 7, 30, 11, 4};
    int n = sizeof(numbers) / sizeof(numbers[0]);
    int even_count = 0;
    int i;
    for (i = 0; i < n; i++) {
        if (numbers[i] % 2 == 0) {
            even_count++;
        }
    }
    printf("Number of even integers: %d\n", even_count);
    return 0;
}