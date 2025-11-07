#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
void printMatrix(int** matrix, int rows, int cols) {
    if (matrix == NULL || rows <= 0 || cols <= 0) {
        printf("Matrix is empty or invalid.\n");
        return;
    }
    printf("Matrix (%dx%d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}
int** createMatrix(int initialRows, int initialCols, int* actualRows, int* actualCols) {
    if (initialRows <= 0 || initialCols <= 0) {
        *actualRows = 0;
        *actualCols = 0;
        return NULL;
    }
    int** matrix = (int**)malloc(initialRows * sizeof(int*));
    if (matrix == NULL) {
        perror("Failed to allocate memory for matrix rows");
        *actualRows = 0;
        *actualCols = 0;
        return NULL;
    }
    for (int i = 0; i < initialRows; i++) {
        matrix[i] = (int*)malloc(initialCols * sizeof(int));
        if (matrix[i] == NULL) {
            perror("Failed to allocate memory for matrix column");
            for (int k = 0; k < i; k++) {
                free(matrix[k]);
            }
            free(matrix);
            *actualRows = 0;
            *actualCols = 0;
            return NULL;
        }
        for (int j = 0; j < initialCols; j++) {
            matrix[i][j] = i * initialCols + j + 1;
        }
    }
    *actualRows = initialRows;
    *actualCols = initialCols;
    return matrix;
}
void filterMatrix(int*** matrixPtr, int* rowsPtr, int* colsPtr, int threshold) {
    if (*matrixPtr == NULL || *rowsPtr <= 0 || *colsPtr <= 0) {
        return;
    }
    int** currentMatrix = *matrixPtr;
    int currentRowCount = *rowsPtr;
    int currentColCount = *colsPtr;
    int** tempFilteredRows = (int**)malloc(currentRowCount * sizeof(int*));
    if (tempFilteredRows == NULL) {
        perror("Failed to allocate temporary storage for filtered rows");
        return;
    }
    int newRowsCount = 0;
    for (int i = 0; i < currentRowCount; i++) {
        bool allGreaterThanThreshold = true;
        for (int j = 0; j < currentColCount; j++) {
            if (currentMatrix[i][j] <= threshold) {
                allGreaterThanThreshold = false;
                break;
            }
        }
        if (allGreaterThanThreshold) {
            tempFilteredRows[newRowsCount++] = currentMatrix[i];
        } else {
            free(currentMatrix[i]);
        }
    }
    if (newRowsCount == 0) {
        free(currentMatrix);
        *matrixPtr = NULL;
        *rowsPtr = 0;
        free(tempFilteredRows);
        return;
    }
    int** newMatrixBlock = (int**)realloc(currentMatrix, newRowsCount * sizeof(int*));
    if (newMatrixBlock == NULL) {
        free(tempFilteredRows);
        perror("Failed to reallocate matrix rows, matrix might be in an inconsistent state.");
        return;
    }
    for (int i = 0; i < newRowsCount; i++) {
        newMatrixBlock[i] = tempFilteredRows[i];
    }
    *matrixPtr = newMatrixBlock;
    *rowsPtr = newRowsCount;
    free(tempFilteredRows);
}
void freeMatrix(int** matrix, int rows) {
    if (matrix == NULL) {
        return;
    }
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
int main() {
    int rows1 = 0;
    int cols1 = 0;
    int initialRows1 = 5;
    int initialCols1 = 4;
    int filterThreshold1 = 10;
    int** myMatrix1 = createMatrix(initialRows1, initialCols1, &rows1, &cols1);
    printMatrix(myMatrix1, rows1, cols1);
    filterMatrix(&myMatrix1, &rows1, &cols1, filterThreshold1);
    printf("\nAfter filtering (elements > %d):\n", filterThreshold1);
    printMatrix(myMatrix1, rows1, cols1);
    int rows2 = 0;
    int cols2 = 0;
    int initialRows2 = 3;
    int initialCols2 = 3;
    int filterThreshold2 = 5;
    printf("\n--- Test Case 2 ---\n");
    int** myMatrix2 = createMatrix(initialRows2, initialCols2, &rows2, &cols2);
    printMatrix(myMatrix2, rows2, cols2);
    filterMatrix(&myMatrix2, &rows2, &cols2, filterThreshold2);
    printf("\nAfter filtering (elements > %d):\n", filterThreshold2);
    printMatrix(myMatrix2, rows2, cols2);
    int rows3 = 0;
    int cols3 = 0;
    printf("\n--- Test Case 3 (No rows left) ---\n");
    int** myMatrix3 = createMatrix(2, 2, &rows3, &cols3);
    printMatrix(myMatrix3, rows3, cols3);
    filterMatrix(&myMatrix3, &rows3, &cols3, 100); 
    printf("\nAfter filtering (elements > %d):\n", 100);
    printMatrix(myMatrix3, rows3, cols3);
    int rows4 = 0;
    int cols4 = 0;
    printf("\n--- Test Case 4 (All rows left) ---\n");
    int** myMatrix4 = createMatrix(3, 2, &rows4, &cols4);
    printMatrix(myMatrix4, rows4, cols4);
    filterMatrix(&myMatrix4, &rows4, &cols4, 0); 
    printf("\nAfter filtering (elements > %d):\n", 0);
    printMatrix(myMatrix4, rows4, cols4);
    freeMatrix(myMatrix1, rows1);
    freeMatrix(myMatrix2, rows2);
    freeMatrix(myMatrix3, rows3);
    freeMatrix(myMatrix4, rows4);
    return 0;
}