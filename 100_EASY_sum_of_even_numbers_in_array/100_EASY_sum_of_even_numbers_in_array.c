#include <stdio.h>
int main() {
    int numbers[5] = {10, 3, 7, 12, 5};
    int sum_of_evens = 0;
    int i;
    for (i = 0; i < 5; i++) {
        if (numbers[i] % 2 == 0) {
            sum_of_evens += numbers[i];
        }
    }
    printf("Dizideki cift sayilarin toplami: %d\n", sum_of_evens);
    return 0;
}