#include <stdio.h>
#include <stdlib.h>
void initializeMatrix(int*** matPtr, int* rowsPtr, int* colsPtr, int newRows, int newCols) {
    if (newRows <= 0 || newCols <= 0) {
        *matPtr = NULL;
        *rowsPtr = 0;
        *colsPtr = 0;
        return;
    }
    int** tempMatrix = (int**)malloc(newRows * sizeof(int*));
    if (tempMatrix == NULL) {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < newRows; i++) {
        tempMatrix[i] = (int*)malloc(newCols * sizeof(int));
        if (tempMatrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(tempMatrix[j]);
            }
            free(tempMatrix);
            exit(EXIT_FAILURE);
        }
    }
    *matPtr = tempMatrix;
    *rowsPtr = newRows;
    *colsPtr = newCols;
}
void printMatrix(int** mat, int rows, int cols) {
    if (mat == NULL || rows == 0 || cols == 0) {
        printf("Matrix is empty or invalid.\n");
        return;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void resizeMatrix(int*** matPtr, int* rowsPtr, int* colsPtr, int newRows, int newCols) {
    int oldRows = *rowsPtr;
    int oldCols = *colsPtr;
    int** currentMatrix = *matPtr;
    if (newRows <= 0 || newCols <= 0) {
        if (currentMatrix != NULL) {
            for (int i = 0; i < oldRows; i++) {
                free(currentMatrix[i]);
            }
            free(currentMatrix);
        }
        *matPtr = NULL;
        *rowsPtr = 0;
        *colsPtr = 0;
        return;
    }
    if (newRows < oldRows) {
        for (int i = newRows; i < oldRows; i++) {
            free(currentMatrix[i]);
        } 
    }
    int** newMatrix = (int**)realloc(currentMatrix, newRows * sizeof(int*));
    if (newMatrix == NULL) {
        exit(EXIT_FAILURE);
    }
    *matPtr = newMatrix;
    for (int i = 0; i < newRows; i++) {
        int* newRowData;
        if (i < oldRows && newMatrix[i] != NULL) {
            newRowData = (int*)realloc(newMatrix[i], newCols * sizeof(int));
        } else {
            newRowData = (int*)malloc(newCols * sizeof(int));
        }
        if (newRowData == NULL) {
            for (int j = 0; j < i; j++) {
                free(newMatrix[j]);
            }
            free(newMatrix);
            *matPtr = NULL;
            *rowsPtr = 0;
            *colsPtr = 0;
            exit(EXIT_FAILURE);
        }
        newMatrix[i] = newRowData;
    }
    *rowsPtr = newRows;
    *colsPtr = newCols;
}
void freeMatrix(int*** matPtr, int* rowsPtr, int* colsPtr) {
    int** currentMatrix = *matPtr;
    int currentRows = *rowsPtr;
    if (currentMatrix != NULL) {
        for (int i = 0; i < currentRows; i++) {
            free(currentMatrix[i]);
        }
        free(currentMatrix);
    }
    *matPtr = NULL;
    *rowsPtr = 0;
    *colsPtr = 0;
}
int main() {
    int** matrix = NULL;
    int rows = 0;
    int cols = 0;
    initializeMatrix(&matrix, &rows, &cols, 3, 4);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = (i + 1) * 10 + (j + 1);
        }
    }
    printMatrix(matrix, rows, cols);
    printf("Resizing to 5x2:\n");
    resizeMatrix(&matrix, &rows, &cols, 5, 2);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i >= 3 || j >= 4) {
                matrix[i][j] = 99;
            }
        }
    }
    printMatrix(matrix, rows, cols);
    printf("Resizing to 2x5:\n");
    resizeMatrix(&matrix, &rows, &cols, 2, 5);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i >= 5 || j >= 2) {
                matrix[i][j] = 88;
            }
        }
    }
    printMatrix(matrix, rows, cols);
    printf("Deallocating by resizing to 0x0:\n");
    resizeMatrix(&matrix, &rows, &cols, 0, 0);
    printMatrix(matrix, rows, cols);
    printf("Re-initializing to 4x3:\n");
    initializeMatrix(&matrix, &rows, &cols, 4, 3);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = (i + 1) * 100 + (j + 1);
        }
    }
    printMatrix(matrix, rows, cols);
    printf("Explicitly freeing matrix:\n");
    freeMatrix(&matrix, &rows, &cols);
    printMatrix(matrix, rows, cols);
    return 0;
}