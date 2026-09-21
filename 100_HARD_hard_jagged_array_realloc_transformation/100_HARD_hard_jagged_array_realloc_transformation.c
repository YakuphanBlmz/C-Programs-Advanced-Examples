#include <stdio.h>
#include <stdlib.h>
void printMatrix(int** matrix, int R, int* row_sizes) {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < row_sizes[i]; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
void transformMatrix(int** matrix, int R, int* row_sizes, int threshold) {
    for (int i = 0; i < R; i++) {
        int currentSum = 0;
        for (int j = 0; j < row_sizes[i]; j++) {
            currentSum += matrix[i][j];
        }
        if (currentSum > threshold) {
            int oldSize = row_sizes[i];
            int newSize = oldSize * 2;
            matrix[i] = (int*)realloc(matrix[i], newSize * sizeof(int));
            if (matrix[i] == NULL) {
                exit(EXIT_FAILURE);
            }
            for (int k = oldSize; k < newSize; k++) {
                matrix[i][k] = -1;
            }
            row_sizes[i] = newSize;
        }
    }
}
int main() {
    int R = 5;
    int threshold = 30;
    int** matrix = (int**)malloc(R * sizeof(int*));
    if (matrix == NULL) {
        exit(EXIT_FAILURE);
    }
    int* row_sizes = (int*)malloc(R * sizeof(int));
    if (row_sizes == NULL) {
        free(matrix);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < R; i++) {
        row_sizes[i] = i + 1;
        matrix[i] = (int*)malloc(row_sizes[i] * sizeof(int));
        if (matrix[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(matrix[k]);
            }
            free(matrix);
            free(row_sizes);
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < row_sizes[i]; j++) {
            matrix[i][j] = (i * 10) + j;
        }
    }
    printf("Initial Matrix:\n");
    printMatrix(matrix, R, row_sizes);
    printf("\n");
    transformMatrix(matrix, R, row_sizes, threshold);
    printf("Transformed Matrix (threshold = %d):\n", threshold);
    printMatrix(matrix, R, row_sizes);
    for (int i = 0; i < R; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(row_sizes);
    return 0;
}