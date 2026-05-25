#include <stdio.h>
#include <stdlib.h>
int main() {
    int initialRows = 3;
    int initialCols = 4;
    int **matrix = (int **)malloc(initialRows * sizeof(int *));
    if (matrix == NULL) {
        return 1;
    }
    for (int i = 0; i < initialRows; i++) {
        matrix[i] = (int *)malloc(initialCols * sizeof(int));
        if (matrix[i] == NULL) {
            for (int k = 0; k < i; k++) free(matrix[k]);
            free(matrix);
            return 1;
        }
        for (int j = 0; j < initialCols; j++) {
            matrix[i][j] = i * initialCols + j + 1;
        }
    }
    printf("Initial Matrix (%dx%d):\n", initialRows, initialCols);
    for (int i = 0; i < initialRows; i++) {
        for (int j = 0; j < initialCols; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    int rotatedRows = initialCols;
    int rotatedCols = initialRows;
    int **newMatrix = (int **)malloc(rotatedRows * sizeof(int *));
    if (newMatrix == NULL) {
        for (int i = 0; i < initialRows; i++) free(matrix[i]);
        free(matrix);
        return 1;
    }
    for (int i = 0; i < rotatedRows; i++) {
        newMatrix[i] = (int *)malloc(rotatedCols * sizeof(int));
        if (newMatrix[i] == NULL) {
            for (int k = 0; k < i; k++) free(newMatrix[k]);
            free(newMatrix);
            for (int k = 0; k < initialRows; k++) free(matrix[k]);
            free(matrix);
            return 1;
        }
        for (int j = 0; j < rotatedCols; j++) {
            newMatrix[i][j] = matrix[initialRows - 1 - j][i];
        }
    }
    for (int i = 0; i < initialRows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    matrix = newMatrix;
    initialRows = rotatedRows;
    initialCols = rotatedCols;
    printf("Matrix After 90-degree Clockwise Rotation (%dx%d):\n", initialRows, initialCols);
    for (int i = 0; i < initialRows; i++) {
        for (int j = 0; j < initialCols; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    int insertColIndex = 1;
    int defaultValue = -1;
    int newCols = initialCols + 1;
    for (int i = 0; i < initialRows; i++) {
        int *tempRow = (int *)realloc(matrix[i], newCols * sizeof(int));
        if (tempRow == NULL) {
            for (int k = 0; k < initialRows; k++) free(matrix[k]);
            free(matrix);
            return 1;
        }
        matrix[i] = tempRow;
        for (int j = newCols - 1; j > insertColIndex; j--) {
            matrix[i][j] = matrix[i][j-1];
        }
        matrix[i][insertColIndex] = defaultValue;
    }
    initialCols = newCols;
    printf("Matrix After Inserting Column at Index %d (%dx%d):\n", insertColIndex, initialRows, initialCols);
    for (int i = 0; i < initialRows; i++) {
        for (int j = 0; j < initialCols; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < initialRows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}