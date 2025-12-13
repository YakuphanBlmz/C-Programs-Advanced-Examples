#include <stdio.h>
#include <stdlib.h>
void bubbleSort(int* arr, int size) {
    int i, j, temp;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
int** filterAndRemapMatrix(int** sourceMatrix, int rows, int cols, int threshold, int newRows, int newCols, int padValue) {
    if (sourceMatrix == NULL || rows <= 0 || cols <= 0 || newRows < 0 || newCols < 0) {
        return NULL;
    }
    if (newRows == 0 || newCols == 0) {
        return NULL;
    }
    int *filteredElements = NULL;
    int filteredCount = 0;
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (sourceMatrix[i][j] > threshold) {
                filteredCount++;
            }
        }
    }
    if (filteredCount > 0) {
        filteredElements = (int*)malloc(filteredCount * sizeof(int));
        if (filteredElements == NULL) {
            return NULL;
        }
    }
    int k = 0;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (sourceMatrix[i][j] > threshold) {
                if (k < filteredCount) {
                    filteredElements[k++] = sourceMatrix[i][j];
                }
            }
        }
    }
    if (filteredCount > 1) {
        bubbleSort(filteredElements, filteredCount);
    }
    int** newMatrix = (int**)malloc(newRows * sizeof(int*));
    if (newMatrix == NULL) {
        free(filteredElements);
        return NULL;
    }
    for (i = 0; i < newRows; i++) {
        newMatrix[i] = (int*)malloc(newCols * sizeof(int));
        if (newMatrix[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(newMatrix[j]);
            }
            free(newMatrix);
            free(filteredElements);
            return NULL;
        }
    }
    int currentElementIndex = 0;
    for (i = 0; i < newRows; i++) {
        for (j = 0; j < newCols; j++) {
            if (currentElementIndex < filteredCount) {
                newMatrix[i][j] = filteredElements[currentElementIndex++];
            } else {
                newMatrix[i][j] = padValue;
            }
        }
    }
    free(filteredElements);
    return newMatrix;
}