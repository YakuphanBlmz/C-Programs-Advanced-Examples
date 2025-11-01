#include <stdio.h>
#include <stdlib.h>
int** createMatrix(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        exit(1);
    }
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            exit(1);
        }
    }
    return matrix;
}
void freeMatrix(int** matrix, int rows) {
    if (matrix == NULL) return;
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
void printMatrix(int** matrix, int rows, int cols) {
    if (matrix == NULL || rows <= 0 || cols <= 0) {
        printf("Matrix is empty or invalid.\n");
        return;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
int** addRow(int** matrix, int* rowsPtr, int cols, int rowIndex) {
    if (rowIndex < 0 || rowIndex > *rowsPtr) {
        return matrix;
    }
    int newRows = *rowsPtr + 1;
    int** newMatrix = (int**)realloc(matrix, newRows * sizeof(int*));
    if (newMatrix == NULL) {
        exit(1);
    }
    for (int i = newRows - 1; i > rowIndex; i--) {
        newMatrix[i] = newMatrix[i - 1];
    }
    newMatrix[rowIndex] = (int*)malloc(cols * sizeof(int));
    if (newMatrix[rowIndex] == NULL) {
        exit(1);
    }
    for (int j = 0; j < cols; j++) {
        newMatrix[rowIndex][j] = 0;
    }
    *rowsPtr = newRows;
    return newMatrix;
}
int** deleteRow(int** matrix, int* rowsPtr, int cols, int rowIndex) {
    if (matrix == NULL || *rowsPtr <= 0 || rowIndex < 0 || rowIndex >= *rowsPtr) {
        return matrix;
    }
    free(matrix[rowIndex]);
    for (int i = rowIndex; i < *rowsPtr - 1; i++) {
        matrix[i] = matrix[i + 1];
    }
    int newRows = *rowsPtr - 1;
    int** newMatrix = (int**)realloc(matrix, newRows * sizeof(int*));
    if (newRows > 0 && newMatrix == NULL) {
        exit(1);
    }
    *rowsPtr = newRows;
    return newMatrix;
}
void addColumn(int** matrix, int rows, int* colsPtr, int colIndex) {
    if (matrix == NULL || rows <= 0 || colIndex < 0 || colIndex > *colsPtr) {
        return;
    }
    int newCols = *colsPtr + 1;
    for (int i = 0; i < rows; i++) {
        int* newRow = (int*)realloc(matrix[i], newCols * sizeof(int));
        if (newRow == NULL) {
            exit(1);
        }
        matrix[i] = newRow;
        for (int j = newCols - 1; j > colIndex; j--) {
            matrix[i][j] = matrix[i][j - 1];
        }
        matrix[i][colIndex] = 0;
    }
    *colsPtr = newCols;
}
void deleteColumn(int** matrix, int rows, int* colsPtr, int colIndex) {
    if (matrix == NULL || rows <= 0 || *colsPtr <= 0 || colIndex < 0 || colIndex >= *colsPtr) {
        return;
    }
    int newCols = *colsPtr - 1;
    for (int i = 0; i < rows; i++) {
        for (int j = colIndex; j < *colsPtr - 1; j++) {
            matrix[i][j] = matrix[i][j + 1];
        }
        int* newRow = (int*)realloc(matrix[i], newCols * sizeof(int));
        if (newCols > 0 && newRow == NULL) {
            exit(1);
        }
        matrix[i] = newRow;
    }
    *colsPtr = newCols;
}
int main() {
    int rows = 3;
    int cols = 4;
    int i, j;
    int** matrix = createMatrix(rows, cols);
    int counter = 1;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            matrix[i][j] = counter++;
        }
    }
    printf("Original Matrix (%dx%d):\n", rows, cols);
    printMatrix(matrix, rows, cols);
    matrix = addRow(matrix, &rows, cols, 1);
    printf("Matrix after adding a row at index 1 (%dx%d):\n", rows, cols);
    printMatrix(matrix, rows, cols);
    matrix = deleteRow(matrix, &rows, cols, 0);
    printf("Matrix after deleting a row at index 0 (%dx%d):\n", rows, cols);
    printMatrix(matrix, rows, cols);
    addColumn(matrix, rows, &cols, 2);
    printf("Matrix after adding a column at index 2 (%dx%d):\n", rows, cols);
    printMatrix(matrix, rows, cols);
    deleteColumn(matrix, rows, &cols, 0);
    printf("Matrix after deleting a column at index 0 (%dx%d):\n", rows, cols);
    printMatrix(matrix, rows, cols);
    while (rows > 0) {
        matrix = deleteRow(matrix, &rows, cols, 0);
    }
    printf("Matrix after deleting all rows (%dx%d):\n", rows, cols);
    printMatrix(matrix, rows, cols);
    freeMatrix(matrix, rows);
    matrix = NULL;
    return 0;
}