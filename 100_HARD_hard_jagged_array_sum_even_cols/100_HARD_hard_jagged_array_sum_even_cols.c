#include <stdio.h>
#include <stdlib.h>
int main() {
    int N = 5;
    int **jagged_array = (int **)malloc(N * sizeof(int *));
    if (jagged_array == NULL) {
        return 1;
    }
    long long total_sum = 0;
    int i, j;
    for (i = 0; i < N; i++) {
        jagged_array[i] = (int *)malloc((i + 1) * sizeof(int));
        if (jagged_array[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(jagged_array[k]);
            }
            free(jagged_array);
            return 1;
        }
        for (j = 0; j <= i; j++) {
            jagged_array[i][j] = (i + 1) * (j + 1);
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j <= i; j++) {
            if (j % 2 == 0) {
                total_sum += jagged_array[i][j];
            }
        }
    }
    printf("%lld\n", total_sum);
    for (i = 0; i < N; i++) {
        free(jagged_array[i]);
    }
    free(jagged_array);
    return 0;
}