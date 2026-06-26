#include <stdio.h>
#include <stdlib.h>
void printMatrix(int** matrix, int rows, int cols) {
    if (matrix == NULL || rows <= 0 || cols <= 0) {
        printf("Matrix is empty or invalid (0x0). Please ensure matrix, rows, and cols are valid.\n");
        return;
    }
    printf("Matrix (%dx%d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void deleteRowAndColumn(int*** matrix_ptr, int* rows_ptr, int* cols_ptr, int rowToDelete, int colToDelete) {
    if (*matrix_ptr == NULL || *rows_ptr <= 0 || *cols_ptr <= 0) {
        return;
    }
    if (rowToDelete < 0 || rowToDelete >= *rows_ptr || colToDelete < 0 || colToDelete >= *cols_ptr) {
        return;
    }
    int oldRows = *rows_ptr;
    int oldCols = *cols_ptr;
    int newRows = oldRows - 1;
    int newCols = oldCols - 1;
    if (newRows <= 0 || newCols <= 0) {
        for (int i = 0; i < oldRows; i++) {
            free((*matrix_ptr)[i]);
        }
        free(*matrix_ptr);
        *matrix_ptr = NULL;
        *rows_ptr = 0;
        *cols_ptr = 0;
        return;
    }
    int** newMatrix = (int**)malloc(newRows * sizeof(int*));
    if (newMatrix == NULL) {
        return;
    }
    for (int i = 0; i < newRows; i++) {
        newMatrix[i] = (int*)malloc(newCols * sizeof(int));
        if (newMatrix[i] == NULL) {
            for (int k = 0; k < i; k++) free(newMatrix[k]);
            free(newMatrix);
            return;
        }
    }
    int currentNewRow = 0;
    for (int r = 0; r < oldRows; r++) {
        if (r == rowToDelete) {
            continue;
        }
        int currentNewCol = 0;
        for (int c = 0; c < oldCols; c++) {
            if (c == colToDelete) {
                continue;
            }
            newMatrix[currentNewRow][currentNewCol] = (*matrix_ptr)[r][c];
            currentNewCol++;
        }
        currentNewRow++;
    }
    for (int i = 0; i < oldRows; i++) {
        free((*matrix_ptr)[i]);
    }
    free(*matrix_ptr);
    *matrix_ptr = newMatrix;
    *rows_ptr = newRows;
    *cols_ptr = newCols;
}
int main() {
    int initialRows = 4;
    int initialCols = 5;
    int** matrix = (int**)malloc(initialRows * sizeof(int*));
    if (matrix == NULL) {
        return 1;
    }
    for (int i = 0; i < initialRows; i++) {
        matrix[i] = (int*)malloc(initialCols * sizeof(int));
        if (matrix[i] == NULL) {
            for (int k = 0; k < i; k++) free(matrix[k]);
            free(matrix);
            return 1;
        }
        for (int j = 0; j < initialCols; j++) {
            matrix[i][j] = i * 10 + j;
        }
    }
    printMatrix(matrix, initialRows, initialCols);
    int rowToRemove = 1;
    int colToRemove = 2;
    printf("Removing row %d and column %d...\n\n", rowToRemove, colToRemove);
    deleteRowAndColumn(&matrix, &initialRows, &initialCols, rowToRemove, colToRemove);
    printMatrix(matrix, initialRows, initialCols);
    rowToRemove = 0;
    colToRemove = 0;
    printf("Removing row %d and column %d...\n\n", rowToRemove, colToRemove);
    deleteRowAndColumn(&matrix, &initialRows, &initialCols, rowToRemove, colToRemove);
    printMatrix(matrix, initialRows, initialCols);
    rowToRemove = 0;
    colToRemove = 0;
    printf("Removing row %d and column %d (should lead to 1x2 matrix)...\n\n", rowToRemove, colToRemove);
    deleteRowAndColumn(&matrix, &initialRows, &initialCols, rowToRemove, colToRemove);
    printMatrix(matrix, initialRows, initialCols);
    rowToRemove = 0;
    colToRemove = 0;
    printf("Removing row %d and column %d (should result in 0x0 matrix)...\n\n", rowToRemove, colToRemove);
    deleteRowAndColumn(&matrix, &initialRows, &initialCols, rowToRemove, colToRemove);
    printMatrix(matrix, initialRows, initialCols);
    if (matrix != NULL) {
        for (int i = 0; i < initialRows; i++) {
            free(matrix[i]);
        }
        free(matrix);
    }
    return 0;
}