#include <stdio.h>
#include <stdlib.h>
int calculateRowSum(int* row, int size) {
    if (row == NULL || size <= 0) {
        return 0;
    }
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += row[i];
    }
    return sum;
}
void processJaggedArray(int** dynamicArray, int numRows, int* rowSizes) {
    int* currentSums = (int*)malloc(numRows * sizeof(int));
    if (currentSums == NULL) {
        return;
    }
    for (int i = 0; i < numRows; i++) {
        currentSums[i] = calculateRowSum(dynamicArray[i], rowSizes[i]);
    }
    for (int i = 0; i < numRows - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < numRows; j++) {
            if (currentSums[j] > currentSums[max_idx]) {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            int tempSum = currentSums[i];
            currentSums[i] = currentSums[max_idx];
            currentSums[max_idx] = tempSum;
            int* tempRowPtr = dynamicArray[i];
            dynamicArray[i] = dynamicArray[max_idx];
            dynamicArray[max_idx] = tempRowPtr;
            int tempSize = rowSizes[i];
            rowSizes[i] = rowSizes[max_idx];
            rowSizes[max_idx] = tempSize;
        }
    }
    for (int i = 0; i < numRows; i++) {
        if (dynamicArray[i] == NULL || rowSizes[i] <= 0) {
            continue;
        }
        int currentElementSum = calculateRowSum(dynamicArray[i], rowSizes[i]);
        if (currentElementSum % 2 == 0) {
            int newSize = rowSizes[i] + 1;
            int* newRow = (int*)realloc(dynamicArray[i], newSize * sizeof(int));
            if (newRow == NULL) {
                continue;
            }
            dynamicArray[i] = newRow;
            dynamicArray[i][newSize - 1] = 0;
            rowSizes[i] = newSize;
        } else {
            if (rowSizes[i] > 1) {
                int newSize = rowSizes[i] - 1;
                int* newRow = (int*)realloc(dynamicArray[i], newSize * sizeof(int));
                if (newRow == NULL && newSize > 0) {
                    continue;
                }
                dynamicArray[i] = newRow;
                rowSizes[i] = newSize;
            } else {
                free(dynamicArray[i]);
                dynamicArray[i] = NULL;
                rowSizes[i] = 0;
            }
        }
    }
    free(currentSums);
}
int main() {
    int numRows = 3;
    int** dynamicArray = (int**)malloc(numRows * sizeof(int*));
    int* rowSizes = (int*)malloc(numRows * sizeof(int));
    rowSizes[0] = 3;
    dynamicArray[0] = (int*)malloc(rowSizes[0] * sizeof(int));
    dynamicArray[0][0] = 1;
    dynamicArray[0][1] = 2;
    dynamicArray[0][2] = 3;
    rowSizes[1] = 2;
    dynamicArray[1] = (int*)malloc(rowSizes[1] * sizeof(int));
    dynamicArray[1][0] = 10;
    dynamicArray[1][1] = 20;
    rowSizes[2] = 4;
    dynamicArray[2] = (int*)malloc(rowSizes[2] * sizeof(int));
    dynamicArray[2][0] = 5;
    dynamicArray[2][1] = 5;
    dynamicArray[2][2] = 5;
    dynamicArray[2][3] = 5;
    printf("Initial Jagged Array:\n");
    for (int i = 0; i < numRows; i++) {
        printf("Row %d (size %d, sum %d): ", i, rowSizes[i], calculateRowSum(dynamicArray[i], rowSizes[i]));
        if (dynamicArray[i] == NULL) {
            printf("NULL\n");
        } else {
            for (int j = 0; j < rowSizes[i]; j++) {
                printf("%d ", dynamicArray[i][j]);
            }
            printf("\n");
        }
    }
    processJaggedArray(dynamicArray, numRows, rowSizes);
    printf("\nProcessed Jagged Array:\n");
    for (int i = 0; i < numRows; i++) {
        printf("Row %d (size %d, sum %d): ", i, rowSizes[i], calculateRowSum(dynamicArray[i], rowSizes[i]));
        if (dynamicArray[i] == NULL) {
            printf("NULL\n");
        } else {
            for (int j = 0; j < rowSizes[i]; j++) {
                printf("%d ", dynamicArray[i][j]);
            }
            printf("\n");
        }
    }
    for (int i = 0; i < numRows; i++) {
        if (dynamicArray[i] != NULL) {
            free(dynamicArray[i]);
        }
    }
    free(dynamicArray);
    free(rowSizes);
    return 0;
}