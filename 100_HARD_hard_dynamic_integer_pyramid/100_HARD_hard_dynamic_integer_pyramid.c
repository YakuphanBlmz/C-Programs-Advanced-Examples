#include <stdio.h>
#include <stdlib.h>
int main() {
    int num_rows = 5;
    int **pyramid = (int **)malloc(num_rows * sizeof(int *));
    for (int i = 0; i < num_rows; i++) {
        pyramid[i] = (int *)malloc((i + 1) * sizeof(int));
        for (int j = 0; j <= i; j++) {
            pyramid[i][j] = (i * 100) + j;
        }
    }
    printf("Pyramid structure:\n");
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%d ", pyramid[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < num_rows; i++) {
        free(pyramid[i]);
    }
    free(pyramid);
    return 0;
}