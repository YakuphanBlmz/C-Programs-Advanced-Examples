#include <stdio.h>
#include <stdlib.h>
int** createRaggedArray(int numRows, const int* initialRowLengths, int** actualRowLengthsPtr) {
    int** array = (int**)malloc(numRows * sizeof(int*));
    if (array == NULL) {
        return NULL;
    }
    *actualRowLengthsPtr = (int*)malloc(numRows * sizeof(int));
    if (*actualRowLengthsPtr == NULL) {
        free(array);
        return NULL;
    }
    for (int i = 0; i < numRows; i++) {
        array[i] = (int*)malloc(initialRowLengths[i] * sizeof(int));
        if (array[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(array[j]);
            }
            free(array);
            free(*actualRowLengthsPtr);
            *actualRowLengthsPtr = NULL;
            return NULL;
        }
        for (int j = 0; j < initialRowLengths[i]; j++) {
            array[i][j] = i * 10 + j;
        }
        (*actualRowLengthsPtr)[i] = initialRowLengths[i];
    }
    return array;
}
void printRaggedArray(int** array, int numRows, const int* actualRowLengths, const char* label) {
    printf("%s:\n", label);
    if (array == NULL || actualRowLengths == NULL) {
        printf("Array is NULL or lengths tracker is NULL.\n");
        return;
    }
    for (int i = 0; i < numRows; i++) {
        printf("Row %d (length %d): ", i, actualRowLengths[i]);
        if (array[i] == NULL) {
            printf("[NULL]\n");
            continue;
        }
        for (int j = 0; j < actualRowLengths[i]; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
int normalizeRaggedArray(int** array, int numRows, int* actualRowLengths, int fillValue) {
    if (array == NULL || actualRowLengths == NULL || numRows <= 0) {
        return -1;
    }
    int newMaxColLen = 0;
    for (int i = 0; i < numRows; i++) {
        if (actualRowLengths[i] > newMaxColLen) {
            newMaxColLen = actualRowLengths[i];
        }
    }
    for (int i = 0; i < numRows; i++) {
        if (actualRowLengths[i] < newMaxColLen) {
            int oldLength = actualRowLengths[i];
            int* newRow = (int*)realloc(array[i], newMaxColLen * sizeof(int));
            if (newRow == NULL) {
                return -1;
            }
            array[i] = newRow;
            for (int j = oldLength; j < newMaxColLen; j++) {
                array[i][j] = fillValue;
            }
            actualRowLengths[i] = newMaxColLen;
        }
    }
    return 0;
}
void freeRaggedArray(int** array, int numRows, int* actualRowLengths) {
    if (array == NULL) return;
    for (int i = 0; i < numRows; i++) {
        free(array[i]);
    }
    free(array);
    free(actualRowLengths);
}
int main() {
    int numRows = 4;
    int initialLengths[] = {2, 5, 3, 1};
    int* actualRowLengths = NULL;
    int fillValue = 0;
    int** raggedArray = createRaggedArray(numRows, initialLengths, &actualRowLengths);
    if (raggedArray == NULL || actualRowLengths == NULL) {
        fprintf(stderr, "Failed to create ragged array or lengths tracker.\n");
        return 1;
    }
    printRaggedArray(raggedArray, numRows, actualRowLengths, "Initial Ragged Array");
    if (normalizeRaggedArray(raggedArray, numRows, actualRowLengths, fillValue) != 0) {
        fprintf(stderr, "Failed to normalize ragged array.\n");
        freeRaggedArray(raggedArray, numRows, actualRowLengths);
        return 1;
    }
    printRaggedArray(raggedArray, numRows, actualRowLengths, "Normalized Ragged Array");
    freeRaggedArray(raggedArray, numRows, actualRowLengths);
    return 0;
}