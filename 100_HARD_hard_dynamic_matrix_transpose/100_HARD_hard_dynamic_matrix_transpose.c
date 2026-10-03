#include <stdio.h>
#include <stdlib.h>
void printMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}
int** allocateMatrix(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(matrix[k]);
            }
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}
int** transposeMatrix(int **originalMatrix, int rows, int cols) {
    int **transposed = allocateMatrix(cols, rows);
    if (transposed == NULL) {
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transposed[j][i] = originalMatrix[i][j];
        }
    }
    return transposed;
}
void freeMatrix(int **matrix, int rows) {
    if (matrix == NULL) {
        return;
    }
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
int main() {
    int initialRows = 3;
    int initialCols = 4;
    int **originalMatrix = allocateMatrix(initialRows, initialCols);
    if (originalMatrix == NULL) {
        printf("Memory allocation failed for original matrix.\n");
        return 1;
    }
    for (int i = 0; i < initialRows; i++) {
        for (int j = 0; j < initialCols; j++) {
            originalMatrix[i][j] = i * 10 + j;
        }
    }
    printf("Original Matrix (%d x %d):\n", initialRows, initialCols);
    printMatrix(originalMatrix, initialRows, initialCols);
    printf("\n");
    int **transposedMatrix = transposeMatrix(originalMatrix, initialRows, initialCols);
    if (transposedMatrix == NULL) {
        printf("Memory allocation failed for transposed matrix.\n");
        freeMatrix(originalMatrix, initialRows);
        return 1;
    }
    printf("Transposed Matrix (%d x %d):\n", initialCols, initialRows);
    printMatrix(transposedMatrix, initialCols, initialRows);
    printf("\n");
    freeMatrix(originalMatrix, initialRows);
    freeMatrix(transposedMatrix, initialCols);
    return 0;
}