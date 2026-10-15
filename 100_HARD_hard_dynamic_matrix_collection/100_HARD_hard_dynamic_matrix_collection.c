#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void addMatrix(int ****collectionPtr, int **collectionRowsPtr, int **collectionColsPtr,
               int *currentMatricesPtr, int *maxCapacityPtr, int rows, int cols) {
    if (*currentMatricesPtr == *maxCapacityPtr) {
        *maxCapacityPtr *= 2;
        *collectionPtr = (int ***)realloc(*collectionPtr, *maxCapacityPtr * sizeof(int **));
        *collectionRowsPtr = (int *)realloc(*collectionRowsPtr, *maxCapacityPtr * sizeof(int));
        *collectionColsPtr = (int *)realloc(*collectionColsPtr, *maxCapacityPtr * sizeof(int));
        if (*collectionPtr == NULL || *collectionRowsPtr == NULL || *collectionColsPtr == NULL) {
            fprintf(stderr, "Memory reallocation failed.\n");
            exit(EXIT_FAILURE);
        }
    }
    int **newMatrix = (int **)malloc(rows * sizeof(int *));
    if (newMatrix == NULL) {
        fprintf(stderr, "Memory allocation failed for matrix rows.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < rows; i++) {
        newMatrix[i] = (int *)malloc(cols * sizeof(int));
        if (newMatrix[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for matrix column data.\n");
            for (int k = 0; k < i; k++) {
                free(newMatrix[k]);
            }
            free(newMatrix);
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < cols; j++) {
            newMatrix[i][j] = (i + 1) * 100 + (j + 1) + (*currentMatricesPtr) * 1000;
        }
    }
    (*collectionPtr)[*currentMatricesPtr] = newMatrix;
    (*collectionRowsPtr)[*currentMatricesPtr] = rows;
    (*collectionColsPtr)[*currentMatricesPtr] = cols;
    (*currentMatricesPtr)++;
}
void removeMatrix(int ****collectionPtr, int **collectionRowsPtr, int **collectionColsPtr,
                  int *currentMatricesPtr, int *maxCapacityPtr, int indexToRemove) {
    if (indexToRemove < 0 || indexToRemove >= *currentMatricesPtr) {
        return;
    }
    int rowsToFree = (*collectionRowsPtr)[indexToRemove];
    int **matrixToFree = (*collectionPtr)[indexToRemove];
    for (int i = 0; i < rowsToFree; i++) {
        free(matrixToFree[i]);
    }
    free(matrixToFree);
    if (indexToRemove < *currentMatricesPtr - 1) {
        memmove(&(*collectionPtr)[indexToRemove], &(*collectionPtr)[indexToRemove + 1],
                (*currentMatricesPtr - 1 - indexToRemove) * sizeof(int **));
        memmove(&(*collectionRowsPtr)[indexToRemove], &(*collectionRowsPtr)[indexToRemove + 1],
                (*currentMatricesPtr - 1 - indexToRemove) * sizeof(int));
        memmove(&(*collectionColsPtr)[indexToRemove], &(*collectionColsPtr)[indexToRemove + 1],
                (*currentMatricesPtr - 1 - indexToRemove) * sizeof(int));
    }
    (*currentMatricesPtr)--;
    if (*currentMatricesPtr > 0 && *currentMatricesPtr < *maxCapacityPtr / 4) {
        *maxCapacityPtr /= 2;
        *collectionPtr = (int ***)realloc(*collectionPtr, *maxCapacityPtr * sizeof(int **));
        *collectionRowsPtr = (int *)realloc(*collectionRowsPtr, *maxCapacityPtr * sizeof(int));
        *collectionColsPtr = (int *)realloc(*collectionColsPtr, *maxCapacityPtr * sizeof(int));
        if (*collectionPtr == NULL || *collectionRowsPtr == NULL || *collectionColsPtr == NULL) {
             fprintf(stderr, "Memory reallocation failed for shrinkage.\n");
             exit(EXIT_FAILURE);
        }
    } else if (*currentMatricesPtr == 0 && *maxCapacityPtr > 0) {
        free(*collectionPtr); *collectionPtr = NULL;
        free(*collectionRowsPtr); *collectionRowsPtr = NULL;
        free(*collectionColsPtr); *collectionColsPtr = NULL;
        *maxCapacityPtr = 0;
    }
}
void printCollection(int ***collection, int *collectionRows, int *collectionCols, int currentMatrices) {
    if (currentMatrices == 0) {
        printf("Collection is empty.\n");
        return;
    }
    for (int m = 0; m < currentMatrices; m++) {
        printf("Matrix %d (%dx%d):\n", m, collectionRows[m], collectionCols[m]);
        for (int i = 0; i < collectionRows[m]; i++) {
            for (int j = 0; j < collectionCols[m]; j++) {
                printf("%d ", collection[m][i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}
void freeCollection(int ***collection, int *collectionRows, int currentMatrices, int *collectionCols) {
    for (int m = 0; m < currentMatrices; m++) {
        for (int i = 0; i < collectionRows[m]; i++) {
            free(collection[m][i]);
        }
        free(collection[m]);
    }
    free(collection);
    free(collectionRows);
    free(collectionCols);
}
int main() {
    int ***matrixCollection = NULL;
    int *matrixRows = NULL;
    int *matrixCols = NULL;
    int currentMatrixCount = 0;
    int maxCollectionCapacity = 0;
    printf("Initializing dynamic matrix collection.\n");
    maxCollectionCapacity = 2;
    matrixCollection = (int ***)malloc(maxCollectionCapacity * sizeof(int **));
    matrixRows = (int *)malloc(maxCollectionCapacity * sizeof(int));
    matrixCols = (int *)malloc(maxCollectionCapacity * sizeof(int));
    if (matrixCollection == NULL || matrixRows == NULL || matrixCols == NULL) {
        fprintf(stderr, "Initial memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    printf("Adding first matrix (3x2).\n");
    addMatrix(&matrixCollection, &matrixRows, &matrixCols, &currentMatrixCount, &maxCollectionCapacity, 3, 2);
    printf("Adding second matrix (2x4).\n");
    addMatrix(&matrixCollection, &matrixRows, &matrixCols, &currentMatrixCount, &maxCollectionCapacity, 2, 4);
    printf("Adding third matrix (4x1).\n");
    addMatrix(&matrixCollection, &matrixRows, &matrixCols, &currentMatrixCount, &maxCollectionCapacity, 4, 1);
    printf("Adding fourth matrix (1x3).\n");
    addMatrix(&matrixCollection, &matrixRows, &matrixCols, &currentMatrixCount, &maxCollectionCapacity, 1, 3);
    printf("\n--- Current Collection ---\n");
    printCollection(matrixCollection, matrixRows, matrixCols, currentMatrixCount);
    printf("Removing matrix at index 1 (the 2x4 matrix).\n");
    removeMatrix(&matrixCollection, &matrixRows, &matrixCols, &currentMatrixCount, &maxCollectionCapacity, 1);
    printf("\n--- Collection after removal ---\n");
    printCollection(matrixCollection, matrixRows, matrixCols, currentMatrixCount);
    printf("Adding another matrix (3x3).\n");
    addMatrix(&matrixCollection, &matrixRows, &matrixCols, &currentMatrixCount, &maxCollectionCapacity, 3, 3);
    printf("\n--- Collection after adding again ---\n");
    printCollection(matrixCollection, matrixRows, matrixCols, currentMatrixCount);
    printf("Removing all remaining matrices.\n");
    while(currentMatrixCount > 0) {
        removeMatrix(&matrixCollection, &matrixRows, &matrixCols, &currentMatrixCount, &maxCollectionCapacity, 0);
    }
    printf("\n--- Collection after all removals ---\n");
    printCollection(matrixCollection, matrixRows, matrixCols, currentMatrixCount);
    printf("Final cleanup of all allocated memory.\n");
    freeCollection(matrixCollection, matrixRows, currentMatrixCount, matrixCols);
    return 0;
}