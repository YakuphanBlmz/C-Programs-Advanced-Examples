#include <stdio.h>
#include <stdlib.h>
void manipulateJaggedMatrix(int*** matrixPtr, int** rowColCountsPtr, int* totalRowsPtr) {
    *matrixPtr = NULL;
    *rowColCountsPtr = NULL;
    *totalRowsPtr = 0;
    int currentCapacity = 0;
    int newCols1 = 3;
    if (*totalRowsPtr >= currentCapacity) {
        currentCapacity = (currentCapacity == 0) ? 1 : currentCapacity * 2;
        int** tempMatrix = (int**)realloc(*matrixPtr, currentCapacity * sizeof(int*));
        if (tempMatrix == NULL) {
            fprintf(stderr, "Error: Reallocation for matrixPtr failed at step 1.\n");
            return;
        }
        *matrixPtr = tempMatrix;
        int* tempRowColCounts = (int*)realloc(*rowColCountsPtr, currentCapacity * sizeof(int));
        if (tempRowColCounts == NULL) {
            fprintf(stderr, "Error: Reallocation for rowColCountsPtr failed at step 1.\n");
            free(*matrixPtr);
            *matrixPtr = NULL;
            return;
        }
        *rowColCountsPtr = tempRowColCounts;
    }
    (*totalRowsPtr)++;
    (*matrixPtr)[(*totalRowsPtr) - 1] = (int*)malloc(newCols1 * sizeof(int));
    if ((*matrixPtr)[(*totalRowsPtr) - 1] == NULL) {
        fprintf(stderr, "Error: Malloc for new row failed at step 1.\n");
        (*totalRowsPtr)--;
        if (*totalRowsPtr == 0) {
            free(*matrixPtr);
            *matrixPtr = NULL;
            free(*rowColCountsPtr);
            *rowColCountsPtr = NULL;
        } else {
            int** tempMatrix = (int**)realloc(*matrixPtr, (*totalRowsPtr) * sizeof(int*));
            if (tempMatrix != NULL || (*totalRowsPtr) == 0) *matrixPtr = tempMatrix;
            int* tempRowColCounts = (int*)realloc(*rowColCountsPtr, (*totalRowsPtr) * sizeof(int));
            if (tempRowColCounts != NULL || (*totalRowsPtr) == 0) *rowColCountsPtr = tempRowColCounts;
        }
        return;
    }
    (*rowColCountsPtr)[(*totalRowsPtr) - 1] = newCols1;
    int newCols2 = 5;
    if (*totalRowsPtr >= currentCapacity) {
        currentCapacity = (currentCapacity == 0) ? 1 : currentCapacity * 2;
        int** tempMatrix = (int**)realloc(*matrixPtr, currentCapacity * sizeof(int*));
        if (tempMatrix == NULL) {
            fprintf(stderr, "Error: Reallocation for matrixPtr failed at step 2.\n");
            return;
        }
        *matrixPtr = tempMatrix;
        int* tempRowColCounts = (int*)realloc(*rowColCountsPtr, currentCapacity * sizeof(int));
        if (tempRowColCounts == NULL) {
            fprintf(stderr, "Error: Reallocation for rowColCountsPtr failed at step 2.\n");
            free(*matrixPtr);
            *matrixPtr = NULL;
            return;
        }
        *rowColCountsPtr = tempRowColCounts;
    }
    (*totalRowsPtr)++;
    (*matrixPtr)[(*totalRowsPtr) - 1] = (int*)malloc(newCols2 * sizeof(int));
    if ((*matrixPtr)[(*totalRowsPtr) - 1] == NULL) {
        fprintf(stderr, "Error: Malloc for new row failed at step 2.\n");
        (*totalRowsPtr)--;
        int** tempMatrix = (int**)realloc(*matrixPtr, (*totalRowsPtr) * sizeof(int*));
        if (tempMatrix != NULL || (*totalRowsPtr) == 0) *matrixPtr = tempMatrix;
        int* tempRowColCounts = (int*)realloc(*rowColCountsPtr, (*totalRowsPtr) * sizeof(int));
        if (tempRowColCounts != NULL || (*totalRowsPtr) == 0) *rowColCountsPtr = tempRowColCounts;
        return;
    }
    (*rowColCountsPtr)[(*totalRowsPtr) - 1] = newCols2;
    int rowIndexToResize = 0;
    int newSizeForRow0 = 7;
    if (rowIndexToResize < *totalRowsPtr) {
        int* resizedRow = (int*)realloc((*matrixPtr)[rowIndexToResize], newSizeForRow0 * sizeof(int));
        if (resizedRow == NULL) {
            fprintf(stderr, "Error: Reallocation for row %d failed.\n", rowIndexToResize);
            return;
        }
        (*matrixPtr)[rowIndexToResize] = resizedRow;
        (*rowColCountsPtr)[rowIndexToResize] = newSizeForRow0;
    } else {
        fprintf(stderr, "Error: Attempted to resize non-existent row %d.\n", rowIndexToResize);
    }
    for (int i = 0; i < *totalRowsPtr; i++) {
        for (int j = 0; j < (*rowColCountsPtr)[i]; j++) {
            (*matrixPtr)[i][j] = i * 100 + j;
        }
    }
    int newCols3 = 2;
    if (*totalRowsPtr >= currentCapacity) {
        currentCapacity = (currentCapacity == 0) ? 1 : currentCapacity * 2;
        int** tempMatrix = (int**)realloc(*matrixPtr, currentCapacity * sizeof(int*));
        if (tempMatrix == NULL) {
            fprintf(stderr, "Error: Reallocation for matrixPtr failed at step 3.\n");
            return;
        }
        *matrixPtr = tempMatrix;
        int* tempRowColCounts = (int*)realloc(*rowColCountsPtr, currentCapacity * sizeof(int));
        if (tempRowColCounts == NULL) {
            fprintf(stderr, "Error: Reallocation for rowColCountsPtr failed at step 3.\n");
            free(*matrixPtr);
            *matrixPtr = NULL;
            return;
        }
        *rowColCountsPtr = tempRowColCounts;
    }
    (*totalRowsPtr)++;
    (*matrixPtr)[(*totalRowsPtr) - 1] = (int*)malloc(newCols3 * sizeof(int));
    if ((*matrixPtr)[(*totalRowsPtr) - 1] == NULL) {
        fprintf(stderr, "Error: Malloc for new row failed at step 3.\n");
        (*totalRowsPtr)--;
        int** tempMatrix = (int**)realloc(*matrixPtr, (*totalRowsPtr) * sizeof(int*));
        if (tempMatrix != NULL || (*totalRowsPtr) == 0) *matrixPtr = tempMatrix;
        int* tempRowColCounts = (int*)realloc(*rowColCountsPtr, (*totalRowsPtr) * sizeof(int));
        if (tempRowColCounts != NULL || (*totalRowsPtr) == 0) *rowColCountsPtr = tempRowColCounts;
        return;
    }
    (*rowColCountsPtr)[(*totalRowsPtr) - 1] = newCols3;
    for (int j = 0; j < (*rowColCountsPtr)[(*totalRowsPtr) - 1]; j++) {
        (*matrixPtr)[(*totalRowsPtr) - 1][j] = ((*totalRowsPtr) - 1) * 100 + j;
    }
}
int main() {
    int** matrix = NULL;
    int* rowColCounts = NULL;
    int totalRows = 0;
    manipulateJaggedMatrix(&matrix, &rowColCounts, &totalRows);
    if (matrix != NULL && rowColCounts != NULL) {
        printf("Final Jagged Matrix State:\n");
        for (int i = 0; i < totalRows; i++) {
            printf("Row %d (cols: %d): ", i, rowColCounts[i]);
            if (matrix[i] != NULL) {
                for (int j = 0; j < rowColCounts[i]; j++) {
                    printf("%d ", matrix[i][j]);
                }
            } else {
                printf("[NULL ROW]");
            }
            printf("\n");
        }
    } else {
        printf("Matrix is not initialized or an error occurred.\n");
    }
    if (matrix != NULL) {
        for (int i = 0; i < totalRows; i++) {
            if (matrix[i] != NULL) {
                free(matrix[i]);
            }
        }
        free(matrix);
    }
    if (rowColCounts != NULL) {
        free(rowColCounts);
    }
    return 0;
}