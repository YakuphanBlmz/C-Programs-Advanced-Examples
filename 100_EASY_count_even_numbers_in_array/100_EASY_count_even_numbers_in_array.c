#include <stdio.h>
int main() {
    int numbers[5] = {10, 7, 22, 15, 8};
    int even_count = 0;
    int i;
    for (i = 0; i < 5; i++) {
        if (numbers[i] % 2 == 0) {
            even_count++;
        }
    }
    printf("Total even numbers: %d\n", even_count);
    return 0;
}