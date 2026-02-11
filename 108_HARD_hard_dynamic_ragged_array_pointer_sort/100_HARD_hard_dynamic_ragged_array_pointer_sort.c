#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int calculateSum(int *arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}
void printRaggedArray(int **mainArr, int *sizes, int numArrays, const char *msg) {
    printf("%s\n", msg);
    for (int i = 0; i < numArrays; i++) {
        printf("Array %d (Sum: %d): ", i, calculateSum(mainArr[i], sizes[i]));
        for (int j = 0; j < sizes[i]; j++) {
            printf("%d ", mainArr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
int main() {
    srand(time(NULL));
    int numArrays = 7;
    int maxInnerSize = 8;
    int **raggedArray = (int **)malloc(numArrays * sizeof(int *));
    int *innerArraySizes = (int *)malloc(numArrays * sizeof(int));
    if (raggedArray == NULL || innerArraySizes == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < numArrays; i++) {
        int currentInnerSize = (rand() % maxInnerSize) + 1; 
        innerArraySizes[i] = currentInnerSize;
        raggedArray[i] = (int *)malloc(currentInnerSize * sizeof(int));
        if (raggedArray[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for inner array %d\n", i);
            for (int k = 0; k < i; k++) {
                free(raggedArray[k]);
            }
            free(raggedArray);
            free(innerArraySizes);
            return 1;
        }
        for (int j = 0; j < currentInnerSize; j++) {
            raggedArray[i][j] = (rand() % 100) + 1; 
        }
    }
    printRaggedArray(raggedArray, innerArraySizes, numArrays, "Initial Ragged Array:");
    for (int i = 0; i < numArrays - 1; i++) {
        for (int j = 0; j < numArrays - i - 1; j++) {
            int sum1 = calculateSum(raggedArray[j], innerArraySizes[j]);
            int sum2 = calculateSum(raggedArray[j+1], innerArraySizes[j+1]);
            if (sum1 > sum2) {
                int *tempPtr = raggedArray[j];
                raggedArray[j] = raggedArray[j+1];
                raggedArray[j+1] = tempPtr;
                int tempSize = innerArraySizes[j];
                innerArraySizes[j] = innerArraySizes[j+1];
                innerArraySizes[j+1] = tempSize;
            }
        }
    }
    printRaggedArray(raggedArray, innerArraySizes, numArrays, "Ragged Array After Sorting by Sum:");
    for (int i = 0; i < numArrays; i++) {
        free(raggedArray[i]);
    }
    free(raggedArray);
    free(innerArraySizes);
    return 0;
}