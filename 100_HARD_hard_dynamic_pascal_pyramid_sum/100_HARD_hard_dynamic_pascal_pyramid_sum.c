#include <stdio.h>
#include <stdlib.h>
int main() {
    int num_levels = 6;
    long long total_sum = 0;
    int **pyramid = (int **)malloc(num_levels * sizeof(int *));
    if (pyramid == NULL) {
        fprintf(stderr, "Memory allocation failed for pyramid rows.\n");
        return 1;
    }
    for (int i = 0; i < num_levels; i++) {
        pyramid[i] = (int *)malloc((i + 1) * sizeof(int));
        if (pyramid[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for pyramid row %d.\n", i);
            for (int k = 0; k < i; k++) {
                free(pyramid[k]);
            }
            free(pyramid);
            return 1;
        }
        pyramid[i][0] = 1;
        if (i > 0) {
            pyramid[i][i] = 1;
            for (int j = 1; j < i; j++) {
                pyramid[i][j] = pyramid[i-1][j-1] + pyramid[i-1][j];
            }
        }
    }
    for (int i = 0; i < num_levels; i++) {
        for (int j = 0; j <= i; j++) {
            total_sum += pyramid[i][j];
        }
    }
    printf("Pyramid total sum for %d levels: %lld\n", num_levels, total_sum);
    for (int i = 0; i < num_levels; i++) {
        free(pyramid[i]);
    }
    free(pyramid);
    return 0;
}