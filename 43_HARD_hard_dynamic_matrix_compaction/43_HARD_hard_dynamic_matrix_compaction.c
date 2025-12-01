#include <stdio.h>
#include <stdlib.h>
int** compactMatrix(int** originalMatrix, int originalRows, int originalCols, int* newRowsPtr) {
    if (originalMatrix == NULL || originalRows <= 0 || originalCols <= 0) {
        *newRowsPtr = 0;
        return NULL;
    }
    int validRowsCount = 0;
    for (int i = 0; i < originalRows; i++) {
        int rowSum = 0;
        for (int j = 0; j < originalCols; j++) {
            rowSum += originalMatrix[i][j];
        }
        if (rowSum != 0) {
            validRowsCount++;
        }
    }
    *newRowsPtr = validRowsCount;
    if (validRowsCount == 0) {
        return NULL;
    }
    int** compactedMatrix = (int**)malloc(validRowsCount * sizeof(int*));
    if (compactedMatrix == NULL) {
        *newRowsPtr = 0;
        return NULL;
    }
    int currentNewRow = 0;
    for (int i = 0; i < originalRows; i++) {
        int rowSum = 0;
        for (int j = 0; j < originalCols; j++) {
            rowSum += originalMatrix[i][j];
        }
        if (rowSum != 0) {
            compactedMatrix[currentNewRow] = (int*)malloc(originalCols * sizeof(int));
            if (compactedMatrix[currentNewRow] == NULL) {
                for (int k = 0; k < currentNewRow; k++) {
                    free(compactedMatrix[k]);
                }
                free(compactedMatrix);
                *newRowsPtr = 0;
                return NULL;
            }
            for (int j = 0; j < originalCols; j++) {
                compactedMatrix[currentNewRow][j] = originalMatrix[i][j];
            }
            currentNewRow++;
        }
    }
    return compactedMatrix;
}
int main() {
    int initialRows = 5;
    int initialCols = 4;
    int** matrix = (int**)malloc(initialRows * sizeof(int*));
    if (matrix == NULL) return 1;
    for (int i = 0; i < initialRows; i++) {
        matrix[i] = (int*)malloc(initialCols * sizeof(int));
        if (matrix[i] == NULL) {
            for (int k = 0; k < i; k++) free(matrix[k]);
            free(matrix);
            return 1;
        }
        for (int j = 0; j < initialCols; j++) {
            if (i == 1) {
                matrix[i][j] = (j == 0 || j == 1) ? (j + 1) : (-j);
            } else if (i == 3) {
                matrix[i][j] = (j == 0) ? 5 : (j == 1 ? -5 : 0);
            } else {
                matrix[i][j] = i * initialCols + j + 1;
            }
        }
    }
    printf("Original Matrix (%dx%d):\n", initialRows, initialCols);
    for (int i = 0; i < initialRows; i++) {
        for (int j = 0; j < initialCols; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    int newRows = 0;
    int** compacted = compactMatrix(matrix, initialRows, initialCols, &newRows);
    printf("Compacted Matrix (%dx%d):\n", newRows, initialCols);
    if (compacted != NULL) {
        for (int i = 0; i < newRows; i++) {
            for (int j = 0; j < initialCols; j++) {
                printf("%4d ", compacted[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    } else {
        printf("Matrix is empty after compaction or an error occurred.\n\n");
    }
    for (int i = 0; i < initialRows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    if (compacted != NULL) {
        for (int i = 0; i < newRows; i++) {
            free(compacted[i]);
        }
        free(compacted);
    }
    return 0;
}