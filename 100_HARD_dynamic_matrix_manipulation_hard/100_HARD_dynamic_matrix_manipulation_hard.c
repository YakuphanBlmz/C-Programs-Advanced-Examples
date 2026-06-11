#include <stdio.h>
#include <stdlib.h>
int** createMatrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) return NULL;
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) return NULL;
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j + 1;
        }
    }
    return matrix;
}
void printMatrix(int** matrix, int rows, int cols) {
    if (matrix == NULL || rows <= 0 || cols <= 0) {
        printf("Matrix is empty or invalid.\n");
        return;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void freeMatrix(int** matrix, int rows) {
    if (matrix == NULL) return;
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
int addRow(int*** matrixPtr, int* rowsPtr, int cols, int rowIndex) {
    if (matrixPtr == NULL || *matrixPtr == NULL || rowsPtr == NULL || cols <= 0 || rowIndex < 0 || rowIndex > *rowsPtr) {
        return -1;
    }
    int currentRows = *rowsPtr;
    int newRows = currentRows + 1;
    int** tempMatrix = (int**)realloc(*matrixPtr, newRows * sizeof(int*));
    if (tempMatrix == NULL) {
        return -1;
    }
    *matrixPtr = tempMatrix;
    for (int i = newRows - 1; i > rowIndex; i--) {
        (*matrixPtr)[i] = (*matrixPtr)[i-1];
    }
    (*matrixPtr)[rowIndex] = (int*)malloc(cols * sizeof(int));
    if ((*matrixPtr)[rowIndex] == NULL) {
        return -1;
    }
    for (int i = 0; i < cols; i++) {
        (*matrixPtr)[rowIndex][i] = 0;
    }
    *rowsPtr = newRows;
    return 0;
}
int removeColumn(int** matrix, int rows, int* colsPtr, int colIndex) {
    if (matrix == NULL || rows <= 0 || colsPtr == NULL || *colsPtr <= 0 || colIndex < 0 || colIndex >= *colsPtr) {
        return -1;
    }
    int currentCols = *colsPtr;
    int newCols = currentCols - 1;
    if (newCols == 0) {
        for (int i = 0; i < rows; i++) {
            free(matrix[i]);
            matrix[i] = NULL;
        }
        *colsPtr = 0;
        return 0;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = colIndex; j < newCols; j++) {
            matrix[i][j] = matrix[i][j+1];
        }
        int* tempRow = (int*)realloc(matrix[i], newCols * sizeof(int));
        if (tempRow == NULL) {
            return -1;
        }
        matrix[i] = tempRow;
    }
    *colsPtr = newCols;
    return 0;
}
void swapElements(int** matrix, int rows, int cols, int r1, int c1, int r2, int c2) {
    if (matrix == NULL || r1 < 0 || r1 >= rows || c1 < 0 || c1 >= cols ||
        r2 < 0 || r2 >= rows || c2 < 0 || c2 >= cols) {
        return;
    }
    int temp = matrix[r1][c1];
    matrix[r1][c1] = matrix[r2][c2];
    matrix[r2][c2] = temp;
}
int main() {
    int rows = 3;
    int cols = 4;
    int** myMatrix = createMatrix(rows, cols);
    printf("Initial Matrix:\n");
    printMatrix(myMatrix, rows, cols);
    printf("Adding a row at index 1:\n");
    if (addRow(&myMatrix, &rows, cols, 1) == 0) {
        printMatrix(myMatrix, rows, cols);
    } else {
        printf("Failed to add row.\n");
    }
    printf("Swapping elements (0,0) and (2,2):\n");
    swapElements(myMatrix, rows, cols, 0, 0, 2, 2);
    printMatrix(myMatrix, rows, cols);
    printf("Removing column at index 2:\n");
    if (removeColumn(myMatrix, rows, &cols, 2) == 0) {
        printMatrix(myMatrix, rows, cols);
    } else {
        printf("Failed to remove column.\n");
    }
    printf("Adding another row at index 0:\n");
    if (addRow(&myMatrix, &rows, cols, 0) == 0) {
        printMatrix(myMatrix, rows, cols);
    } else {
        printf("Failed to add row.\n");
    }
    freeMatrix(myMatrix, rows);
    return 0;
}