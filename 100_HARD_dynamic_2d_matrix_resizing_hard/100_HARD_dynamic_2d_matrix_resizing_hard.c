#include <stdio.h>
#include <stdlib.h>
void printMatrix(int** matrix, int rows, int cols) {
    int i, j;
    if (matrix == NULL || rows == 0 || cols == 0) {
        printf("[Empty Matrix]\n");
        return;
    }
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
int** resizeMatrix(int*** matrixPtr, int* currentRowsPtr, int* currentColPtr, int targetRows, int targetCols) {
    int oldRows = *currentRowsPtr;
    int oldCols = *currentColPtr;
    int i, j;
    if (targetRows < 0 || targetCols < 0) {
        return *matrixPtr;
    }
    if (targetRows == 0 || targetCols == 0) {
        for (i = 0; i < oldRows; i++) {
            free((*matrixPtr)[i]);
        }
        free(*matrixPtr);
        *matrixPtr = NULL;
        *currentRowsPtr = 0;
        *currentColPtr = 0;
        return NULL;
    }
    if (targetRows < oldRows) {
        for (i = targetRows; i < oldRows; i++) {
            free((*matrixPtr)[i]);
        }
    }
    int** newMatrix = (int**)realloc(*matrixPtr, targetRows * sizeof(int*));
    if (newMatrix == NULL && targetRows > 0) {
        return *matrixPtr;
    }
    *matrixPtr = newMatrix;
    int rowsToProcess = (targetRows < oldRows) ? targetRows : oldRows;
    for (i = 0; i < rowsToProcess; i++) {
        int* newRow = (int*)realloc((*matrixPtr)[i], targetCols * sizeof(int));
        if (newRow == NULL && targetCols > 0) {
            return *matrixPtr;
        }
        (*matrixPtr)[i] = newRow;
        if (targetCols > oldCols) {
            for (j = oldCols; j < targetCols; j++) {
                (*matrixPtr)[i][j] = 0;
            }
        }
    }
    if (targetRows > oldRows) {
        for (i = oldRows; i < targetRows; i++) {
            (*matrixPtr)[i] = (int*)malloc(targetCols * sizeof(int));
            if ((*matrixPtr)[i] == NULL) {
                *currentRowsPtr = i;
                *currentColPtr = targetCols;
                return *matrixPtr;
            }
            for (j = 0; j < targetCols; j++) {
                (*matrixPtr)[i][j] = 0;
            }
        }
    }
    *currentRowsPtr = targetRows;
    *currentColPtr = targetCols;
    return *matrixPtr;
}
int main() {
    int rows = 2;
    int cols = 3;
    int i, j;
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        return 1;
    }
    for (i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return 1;
        }
        for (j = 0; j < cols; j++) {
            matrix[i][j] = i * 10 + j + 1;
        }
    }
    printf("Initial matrix (%dx%d):\n", rows, cols);
    printMatrix(matrix, rows, cols);
    printf("\nResizing to 3x5:\n");
    matrix = resizeMatrix(&matrix, &rows, &cols, 3, 5);
    printMatrix(matrix, rows, cols);
    printf("\nResizing to 1x4:\n");
    matrix = resizeMatrix(&matrix, &rows, &cols, 1, 4);
    printMatrix(matrix, rows, cols);
    printf("\nResizing to 2x2:\n");
    matrix = resizeMatrix(&matrix, &rows, &cols, 2, 2);
    printMatrix(matrix, rows, cols);
    printf("\nResizing to 0x0:\n");
    matrix = resizeMatrix(&matrix, &rows, &cols, 0, 0);
    printMatrix(matrix, rows, cols);
    if (matrix != NULL) {
        for (i = 0; i < rows; i++) {
            free(matrix[i]);
        }
        free(matrix);
    }
    return 0;
}