#include <stdio.h>
#include <stdlib.h>
void compressRaggedArray(int ***dataPtr, int **rowSizesPtr, int *numRowsPtr, int threshold) {
    int numRows = *numRowsPtr;
    int **data = *dataPtr;
    int *rowSizes = *rowSizesPtr;
    int writeIdx = 0;
    for (int i = 0; i < numRows; i++) {
        int currentRowSum = 0;
        for (int j = 0; j < rowSizes[i]; j++) {
            currentRowSum += data[i][j];
        }
        if (currentRowSum >= threshold) {
            if (writeIdx != i) {
                data[writeIdx] = data[i];
                rowSizes[writeIdx] = rowSizes[i];
            }
            writeIdx++;
        } else {
            free(data[i]);
        }
    }
    *dataPtr = (int**)realloc(data, writeIdx * sizeof(int*));
    if (*dataPtr == NULL && writeIdx > 0) {
        exit(EXIT_FAILURE);
    }
    *rowSizesPtr = (int*)realloc(rowSizes, writeIdx * sizeof(int));
    if (*rowSizesPtr == NULL && writeIdx > 0) {
        if (*dataPtr != NULL) {
             for(int k=0; k<writeIdx; k++) {
                 free((*dataPtr)[k]);
             }
             free(*dataPtr);
        }
        exit(EXIT_FAILURE);
    }
    *numRowsPtr = writeIdx;
}
int main() {
    int initialNumRows = 5;
    int **data = (int **)malloc(initialNumRows * sizeof(int *));
    int *rowSizes = (int *)malloc(initialNumRows * sizeof(int));
    int i, j;
    int rowsToCreate[5][4] = {
        {1, 2, 3, -1},  
        {10, 20, -1, -1}, 
        {0, 0, 1, -1},  
        {5, 5, 5, -1},  
        {1, 1, 1, 1}    
    };
    int actualRowSizes[5] = {3, 2, 3, 3, 4};
    for (i = 0; i < initialNumRows; i++) {
        rowSizes[i] = actualRowSizes[i];
        data[i] = (int *)malloc(rowSizes[i] * sizeof(int));
        for (j = 0; j < rowSizes[i]; j++) {
            data[i][j] = rowsToCreate[i][j];
        }
    }
    printf("Initial Ragged Array:\n");
    for (i = 0; i < initialNumRows; i++) {
        printf("Row %d (size %d): ", i, rowSizes[i]);
        for (j = 0; j < rowSizes[i]; j++) {
            printf("%d ", data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    int threshold = 10;
    printf("Compressing array with threshold = %d\n\n", threshold);
    compressRaggedArray(&data, &rowSizes, &initialNumRows, threshold);
    printf("Compressed Ragged Array (New num_rows: %d):\n", initialNumRows);
    for (i = 0; i < initialNumRows; i++) {
        printf("Row %d (size %d): ", i, rowSizes[i]);
        for (j = 0; j < rowSizes[i]; j++) {
            printf("%d ", data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (i = 0; i < initialNumRows; i++) {
        free(data[i]);
    }
    free(data);
    free(rowSizes);
    return 0;
}