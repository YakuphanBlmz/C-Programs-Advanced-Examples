#include <stdio.h>
#include <stdlib.h>
int main() {
    int N = 5;
    int **originalJaggedArray;
    int totalElementsOriginal = 0;
    int i, j, k;
    originalJaggedArray = (int **)malloc(N * sizeof(int *));
    if (originalJaggedArray == NULL) {
        return 1;
    }
    for (i = 0; i < N; i++) {
        int currentRowLength = i + 2;
        originalJaggedArray[i] = (int *)malloc(currentRowLength * sizeof(int));
        if (originalJaggedArray[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(originalJaggedArray[j]);
            }
            free(originalJaggedArray);
            return 1;
        }
        totalElementsOriginal += currentRowLength;
        for (j = 0; j < currentRowLength; j++) {
            originalJaggedArray[i][j] = (i * 10) + j;
        }
    }
    int *flattenedArray = (int *)malloc(totalElementsOriginal * sizeof(int));
    if (flattenedArray == NULL) {
        for (i = 0; i < N; i++) {
            free(originalJaggedArray[i]);
        }
        free(originalJaggedArray);
        return 1;
    }
    int currentFlatIndex = 0;
    for (i = 0; i < N; i++) {
        int currentRowLength = i + 2;
        for (j = 0; j < currentRowLength; j++) {
            flattenedArray[currentFlatIndex++] = originalJaggedArray[i][j];
        }
    }
    for (i = 0; i < N; i++) {
        free(originalJaggedArray[i]);
    }
    free(originalJaggedArray);
    int M = 4;
    int **newJaggedArray;
    int totalElementsNew = 0;
    int currentFlatIndexForNew = 0;
    newJaggedArray = (int **)malloc(M * sizeof(int *));
    if (newJaggedArray == NULL) {
        free(flattenedArray);
        return 1;
    }
    for (k = 0; k < M; k++) {
        int newCurrentRowLength = (M - k) + 1;
        newJaggedArray[k] = (int *)malloc(newCurrentRowLength * sizeof(int));
        if (newJaggedArray[k] == NULL) {
            for (int l = 0; l < k; l++) {
                free(newJaggedArray[l]);
            }
            free(newJaggedArray);
            free(flattenedArray);
            return 1;
        }
        totalElementsNew += newCurrentRowLength;
        for (int l = 0; l < newCurrentRowLength; l++) {
            if (currentFlatIndexForNew < totalElementsOriginal) {
                newJaggedArray[k][l] = flattenedArray[currentFlatIndexForNew++];
            } else {
                newJaggedArray[k][l] = -1;
            }
        }
    }
    for (k = 0; k < M; k++) {
        int newCurrentRowLength = (M - k) + 1;
        for (int l = 0; l < newCurrentRowLength; l++) {
            printf("%d ", newJaggedArray[k][l]);
        }
        printf("\n");
    }
    free(flattenedArray);
    for (k = 0; k < M; k++) {
        free(newJaggedArray[k]);
    }
    free(newJaggedArray);
    return 0;
}