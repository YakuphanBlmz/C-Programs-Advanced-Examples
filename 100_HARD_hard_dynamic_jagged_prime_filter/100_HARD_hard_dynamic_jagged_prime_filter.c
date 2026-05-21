#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int isPrime(int num) {
    if (num <= 1) return 0;
    if (num <= 3) return 1;
    if (num % 2 == 0 || num % 3 == 0) return 0;
    for (int i = 5; i * i <= num; i = i + 6) {
        if (num % i == 0 || num % (i + 2) == 0) return 0;
    }
    return 1;
}
void filterPrimesAndCreateNewMatrix(
    int **originalMatrix, int originalRows, int *originalCols,
    int ***newMatrixPtr, int *newRowsPtr, int **newColsPtr
) {
    int actualNewRowsCount = 0;
    int *tempPrimeCounts = (int *)calloc(originalRows, sizeof(int));
    if (tempPrimeCounts == NULL) {
        fprintf(stderr, "Memory allocation failed for tempPrimeCounts.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < originalRows; i++) {
        for (int j = 0; j < originalCols[i]; j++) {
            if (isPrime(originalMatrix[i][j])) {
                tempPrimeCounts[i]++;
            }
        }
        if (tempPrimeCounts[i] > 0) {
            actualNewRowsCount++;
        }
    }
    *newRowsPtr = actualNewRowsCount;
    if (actualNewRowsCount == 0) {
        *newMatrixPtr = NULL;
        *newColsPtr = NULL;
        free(tempPrimeCounts);
        return;
    }
    *newMatrixPtr = (int **)malloc(actualNewRowsCount * sizeof(int *));
    if (*newMatrixPtr == NULL) {
        fprintf(stderr, "Memory allocation failed for newMatrixPtr.\n");
        free(tempPrimeCounts);
        exit(EXIT_FAILURE);
    }
    *newColsPtr = (int *)malloc(actualNewRowsCount * sizeof(int));
    if (*newColsPtr == NULL) {
        fprintf(stderr, "Memory allocation failed for newColsPtr.\n");
        free(tempPrimeCounts);
        free(*newMatrixPtr);
        exit(EXIT_FAILURE);
    }
    int currentNewRow = 0;
    for (int i = 0; i < originalRows; i++) {
        if (tempPrimeCounts[i] > 0) {
            (*newMatrixPtr)[currentNewRow] = (int *)malloc(tempPrimeCounts[i] * sizeof(int));
            if ((*newMatrixPtr)[currentNewRow] == NULL) {
                fprintf(stderr, "Memory allocation failed for newMatrix row.\n");
                for (int k = 0; k < currentNewRow; k++) {
                    free((*newMatrixPtr)[k]);
                }
                free(*newMatrixPtr);
                free(*newColsPtr);
                free(tempPrimeCounts);
                exit(EXIT_FAILURE);
            }
            int currentPrimeCol = 0;
            for (int j = 0; j < originalCols[i]; j++) {
                if (isPrime(originalMatrix[i][j])) {
                    (*newMatrixPtr)[currentNewRow][currentPrimeCol++] = originalMatrix[i][j];
                }
            }
            (*newColsPtr)[currentNewRow] = tempPrimeCounts[i];
            currentNewRow++;
        }
    }
    free(tempPrimeCounts);
}
void printJaggedMatrix(int **matrix, int rows, int *cols, const char *name) {
    printf("--- %s (%d rows) ---\n", name, rows);
    if (matrix == NULL || rows == 0) {
        printf("Matrix is empty or NULL.\n");
        return;
    }
    for (int i = 0; i < rows; i++) {
        printf("Row %d (cols: %d): ", i, cols[i]);
        for (int j = 0; j < cols[i]; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("-------------------------\n");
}
void freeJaggedMatrix(int **matrix, int rows, int *cols) {
    if (matrix == NULL) return;
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(cols);
}
int main() {
    int originalRows = 4;
    int *originalCols = (int *)malloc(originalRows * sizeof(int));
    if (originalCols == NULL) {
        fprintf(stderr, "Memory allocation failed for originalCols.\n");
        return EXIT_FAILURE;
    }
    originalCols[0] = 5;
    originalCols[1] = 3;
    originalCols[2] = 6;
    originalCols[3] = 4;
    int **originalMatrix = (int **)malloc(originalRows * sizeof(int *));
    if (originalMatrix == NULL) {
        fprintf(stderr, "Memory allocation failed for originalMatrix.\n");
        free(originalCols);
        return EXIT_FAILURE;
    }
    originalMatrix[0] = (int *)malloc(originalCols[0] * sizeof(int));
    originalMatrix[1] = (int *)malloc(originalCols[1] * sizeof(int));
    originalMatrix[2] = (int *)malloc(originalCols[2] * sizeof(int));
    originalMatrix[3] = (int *)malloc(originalCols[3] * sizeof(int));
    if (originalMatrix[0] == NULL || originalMatrix[1] == NULL || originalMatrix[2] == NULL || originalMatrix[3] == NULL) {
        fprintf(stderr, "Memory allocation failed for originalMatrix rows.\n");
        for (int i = 0; i < originalRows; i++) {
            free(originalMatrix[i]);
        }
        free(originalMatrix);
        free(originalCols);
        return EXIT_FAILURE;
    }
    originalMatrix[0][0] = 1; originalMatrix[0][1] = 2; originalMatrix[0][2] = 3; originalMatrix[0][3] = 4; originalMatrix[0][4] = 5;
    originalMatrix[1][0] = 6; originalMatrix[1][1] = 7; originalMatrix[1][2] = 8;
    originalMatrix[2][0] = 9; originalMatrix[2][1] = 10; originalMatrix[2][2] = 11; originalMatrix[2][3] = 12; originalMatrix[2][4] = 13; originalMatrix[2][5] = 1;
    originalMatrix[3][0] = 14; originalMatrix[3][1] = 15; originalMatrix[3][2] = 16; originalMatrix[3][3] = 17;
    printJaggedMatrix(originalMatrix, originalRows, originalCols, "Original Matrix");
    int **newMatrix = NULL;
    int newRows = 0;
    int *newCols = NULL;
    filterPrimesAndCreateNewMatrix(
        originalMatrix, originalRows, originalCols,
        &newMatrix, &newRows, &newCols
    );
    printJaggedMatrix(newMatrix, newRows, newCols, "Filtered Prime Matrix");
    freeJaggedMatrix(originalMatrix, originalRows, originalCols);
    freeJaggedMatrix(newMatrix, newRows, newCols);
    return 0;
}