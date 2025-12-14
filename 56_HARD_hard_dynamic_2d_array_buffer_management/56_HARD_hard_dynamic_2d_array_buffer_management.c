#include <stdio.h>
#include <stdlib.h>
void initializeBuffer(int*** bufferPtr, int* numRowsPtr, int* maxRowsPtr, int** rowLengthsPtr, int** rowCapacitiesPtr, int initialMaxRows) {
    *numRowsPtr = 0;
    *maxRowsPtr = initialMaxRows;
    *bufferPtr = (int**)malloc(initialMaxRows * sizeof(int*));
    *rowLengthsPtr = (int*)malloc(initialMaxRows * sizeof(int));
    *rowCapacitiesPtr = (int*)malloc(initialMaxRows * sizeof(int));
    int i;
    for (i = 0; i < initialMaxRows; i++) {
        (*rowLengthsPtr)[i] = 0;
        (*rowCapacitiesPtr)[i] = 0;
        (*bufferPtr)[i] = NULL;
    }
}
void addLine(int*** bufferPtr, int* numRowsPtr, int* maxRowsPtr, int** rowLengthsPtr, int** rowCapacitiesPtr, int initialColCapacity) {
    if (*numRowsPtr == *maxRowsPtr) {
        *maxRowsPtr *= 2;
        *bufferPtr = (int**)realloc(*bufferPtr, *maxRowsPtr * sizeof(int*));
        *rowLengthsPtr = (int*)realloc(*rowLengthsPtr, *maxRowsPtr * sizeof(int));
        *rowCapacitiesPtr = (int*)realloc(*rowCapacitiesPtr, *maxRowsPtr * sizeof(int));
        int i;
        for (i = *numRowsPtr; i < *maxRowsPtr; i++) {
            (*rowLengthsPtr)[i] = 0;
            (*rowCapacitiesPtr)[i] = 0;
            (*bufferPtr)[i] = NULL;
        }
    }
    int newRowIndex = *numRowsPtr;
    (*bufferPtr)[newRowIndex] = (int*)malloc(initialColCapacity * sizeof(int));
    (*rowLengthsPtr)[newRowIndex] = 0;
    (*rowCapacitiesPtr)[newRowIndex] = initialColCapacity;
    (*numRowsPtr)++;
}
void addElement(int** buffer, int numRows, int rowIndex, int value, int* rowLengths, int* rowCapacities) {
    if (buffer == NULL || rowLengths == NULL || rowCapacities == NULL || rowIndex < 0 || rowIndex >= numRows) return;
    if (rowLengths[rowIndex] == rowCapacities[rowIndex]) {
        rowCapacities[rowIndex] = (rowCapacities[rowIndex] == 0) ? 1 : rowCapacities[rowIndex] * 2;
        int* newRow = (int*)realloc(buffer[rowIndex], rowCapacities[rowIndex] * sizeof(int));
        if (newRow == NULL) {
            return;
        }
        buffer[rowIndex] = newRow;
    }
    buffer[rowIndex][rowLengths[rowIndex]] = value;
    rowLengths[rowIndex]++;
}
void deleteLine(int*** bufferPtr, int* numRowsPtr, int* maxRowsPtr, int** rowLengthsPtr, int** rowCapacitiesPtr, int rowIndex) {
    if (rowIndex < 0 || rowIndex >= *numRowsPtr || *numRowsPtr == 0) return;
    free((*bufferPtr)[rowIndex]);
    int i;
    for (i = rowIndex; i < *numRowsPtr - 1; i++) {
        (*bufferPtr)[i] = (*bufferPtr)[i+1];
        (*rowLengthsPtr)[i] = (*rowLengthsPtr)[i+1];
        (*rowCapacitiesPtr)[i] = (*rowCapacitiesPtr)[i+1];
    }
    (*numRowsPtr)--;
    if (*numRowsPtr > 0 && *numRowsPtr < *maxRowsPtr / 4 && *maxRowsPtr > 2) {
        *maxRowsPtr /= 2;
        *bufferPtr = (int**)realloc(*bufferPtr, *maxRowsPtr * sizeof(int*));
        *rowLengthsPtr = (int*)realloc(*rowLengthsPtr, *maxRowsPtr * sizeof(int));
        *rowCapacitiesPtr = (int*)realloc(*rowCapacitiesPtr, *maxRowsPtr * sizeof(int));
    } else if (*numRowsPtr == 0 && *maxRowsPtr > 2) {
        *maxRowsPtr = 2;
        free(*bufferPtr);
        *bufferPtr = (int**)malloc(*maxRowsPtr * sizeof(int*));
        free(*rowLengthsPtr);
        *rowLengthsPtr = (int*)malloc(*maxRowsPtr * sizeof(int));
        free(*rowCapacitiesPtr);
        *rowCapacitiesPtr = (int*)malloc(*maxRowsPtr * sizeof(int));
        for (i = 0; i < *maxRowsPtr; i++) {
            (*rowLengthsPtr)[i] = 0;
            (*rowCapacitiesPtr)[i] = 0;
            (*bufferPtr)[i] = NULL;
        }
    }
}
void deleteElement(int** buffer, int numRows, int rowIndex, int colIndex, int* rowLengths, int* rowCapacities) {
    if (buffer == NULL || rowLengths == NULL || rowCapacities == NULL || rowIndex < 0 || rowIndex >= numRows || colIndex < 0 || colIndex >= rowLengths[rowIndex]) return;
    int i;
    for (i = colIndex; i < rowLengths[rowIndex] - 1; i++) {
        buffer[rowIndex][i] = buffer[rowIndex][i+1];
    }
    rowLengths[rowIndex]--;
    if (rowLengths[rowIndex] > 0 && rowLengths[rowIndex] < rowCapacities[rowIndex] / 4 && rowCapacities[rowIndex] > 2) {
        rowCapacities[rowIndex] /= 2;
        int* newRow = (int*)realloc(buffer[rowIndex], rowCapacities[rowIndex] * sizeof(int));
        if (newRow == NULL) {
            return;
        }
        buffer[rowIndex] = newRow;
    } else if (rowLengths[rowIndex] == 0) {
        free(buffer[rowIndex]);
        buffer[rowIndex] = NULL;
        rowCapacities[rowIndex] = 0;
    }
}
void printBuffer(int** buffer, int numRows, int* rowLengths) {
    if (buffer == NULL || rowLengths == NULL) {
        printf("Buffer is not initialized or invalid.\n");
        return;
    }
    int i, j;
    for (i = 0; i < numRows; i++) {
        printf("Line %d (len %d): [", i, rowLengths[i]);
        if (buffer[i] == NULL || rowLengths[i] == 0) {
            printf("EMPTY");
        } else {
            for (j = 0; j < rowLengths[i]; j++) {
                printf("%d", buffer[i][j]);
                if (j < rowLengths[i] - 1) {
                    printf(", ");
                }
            }
        }
        printf("]\n");
    }
    if (numRows == 0) {
        printf("Buffer is empty.\n");
    }
}
void freeBuffer(int*** bufferPtr, int* numRowsPtr, int** rowLengthsPtr, int** rowCapacitiesPtr) {
    if (*bufferPtr == NULL) return;
    int i;
    for (i = 0; i < *numRowsPtr; i++) {
        free((*bufferPtr)[i]);
    }
    free(*bufferPtr);
    *bufferPtr = NULL;
    free(*rowLengthsPtr);
    *rowLengthsPtr = NULL;
    free(*rowCapacitiesPtr);
    *rowCapacitiesPtr = NULL;
    *numRowsPtr = 0;
}
int main() {
    int** textBuffer = NULL;
    int numRows = 0;
    int maxRows = 0;
    int* rowLengths = NULL;
    int* rowCapacities = NULL;
    initializeBuffer(&textBuffer, &numRows, &maxRows, &rowLengths, &rowCapacities, 2);
    addLine(&textBuffer, &numRows, &maxRows, &rowLengths, &rowCapacities, 5);
    addElement(textBuffer, numRows, 0, 10, rowLengths, rowCapacities);
    addElement(textBuffer, numRows, 0, 20, rowLengths, rowCapacities);
    addElement(textBuffer, numRows, 0, 30, rowLengths, rowCapacities);
    addLine(&textBuffer, &numRows, &maxRows, &rowLengths, &rowCapacities, 3);
    addElement(textBuffer, numRows, 1, 11, rowLengths, rowCapacities);
    addElement(textBuffer, numRows, 1, 22, rowLengths, rowCapacities);
    addLine(&textBuffer, &numRows, &maxRows, &rowLengths, &rowCapacities, 4);
    addElement(textBuffer, numRows, 2, 111, rowLengths, rowCapacities);
    addElement(textBuffer, numRows, 2, 222, rowLengths, rowCapacities);
    addElement(textBuffer, numRows, 2, 333, rowLengths, rowCapacities);
    printf("--- Initial Buffer ---\n");
    printBuffer(textBuffer, numRows, rowLengths);
    printf("Buffer status: numRows=%d, maxRows=%d\n\n", numRows, maxRows);
    addElement(textBuffer, numRows, 0, 40, rowLengths, rowCapacities);
    printf("--- After adding 40 to Line 0 ---\n");
    printBuffer(textBuffer, numRows, rowLengths);
    printf("Buffer status: numRows=%d, maxRows=%d\n\n", numRows, maxRows);
    deleteElement(textBuffer, numRows, 0, 1, rowLengths, rowCapacities);
    printf("--- After deleting element at index 1 (value 20) from Line 0 ---\n");
    printBuffer(textBuffer, numRows, rowLengths);
    printf("Buffer status: numRows=%d, maxRows=%d\n\n", numRows, maxRows);
    deleteLine(&textBuffer, &numRows, &maxRows, &rowLengths, &rowCapacities, 1);
    printf("--- After deleting Line 1 ---\n");
    printBuffer(textBuffer, numRows, rowLengths);
    printf("Buffer status: numRows=%d, maxRows=%d\n\n", numRows, maxRows);
    addLine(&textBuffer, &numRows, &maxRows, &rowLengths, &rowCapacities, 6);
    addElement(textBuffer, numRows, numRows - 1, 500, rowLengths, rowCapacities);
    addElement(textBuffer, numRows, numRows - 1, 600, rowLengths, rowCapacities);
    printf("--- After adding a new line and elements ---\n");
    printBuffer(textBuffer, numRows, rowLengths);
    printf("Buffer status: numRows=%d, maxRows=%d\n\n", numRows, maxRows);
    freeBuffer(&textBuffer, &numRows, &rowLengths, &rowCapacities);
    printf("--- After freeing buffer ---\n");
    printBuffer(textBuffer, numRows, rowLengths);
    printf("Buffer status: numRows=%d, maxRows=%d\n\n", numRows, maxRows);
    return 0;
}