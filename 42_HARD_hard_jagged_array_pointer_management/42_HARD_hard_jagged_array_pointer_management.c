#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int* createRow(int length) {
    if (length < 0) return NULL;
    int* block = (int*)malloc((length + 1) * sizeof(int));
    if (block == NULL) return NULL;
    block[0] = length;
    return block + 1;
}
int getRowLength(int* row) {
    if (row == NULL) return 0;
    return *(row - 1);
}
void freeRow(int* row) {
    if (row != NULL) {
        free(row - 1);
    }
}
void printJaggedArray(int** array, int numRows) {
    printf("\n--- Current Jagged Array ---\n");
    if (array == NULL || numRows == 0) {
        printf("Array is empty.\n");
        return;
    }
    for (int i = 0; i < numRows; i++) {
        printf("Row %d [length %d]: ", i, getRowLength(array[i]));
        int rowLength = getRowLength(array[i]);
        for (int j = 0; j < rowLength; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
    printf("------------------------------\n");
}
int resizeRow(int** array, int rowIndex, int newLength) {
    if (array == NULL || array[rowIndex] == NULL || newLength < 0) return 0; 
    int* oldBasePtr = array[rowIndex] - 1;
    int* newBasePtr = (int*)realloc(oldBasePtr, (newLength + 1) * sizeof(int));
    if (newBasePtr == NULL) {
        return 0; 
    }
    *newBasePtr = newLength;
    array[rowIndex] = newBasePtr + 1;
    return 1;
}
int insertRow(int*** arrayPtr, int* numRowsPtr, int newRowIndex, int* newRowData, int newRowLength) {
    if (arrayPtr == NULL || numRowsPtr == NULL || newRowIndex < 0 || newRowIndex > *numRowsPtr) return 0;
    if (newRowData == NULL && newRowLength > 0) return 0;
    int** currentArray = *arrayPtr;
    int currentNumRows = *numRowsPtr;
    int** temp = (int**)realloc(currentArray, (currentNumRows + 1) * sizeof(int*));
    if (temp == NULL) {
        return 0;
    }
    *arrayPtr = temp;
    currentArray = *arrayPtr;
    for (int i = currentNumRows; i > newRowIndex; i--) {
        currentArray[i] = currentArray[i - 1];
    }
    int* newRow = createRow(newRowLength);
    if (newRow == NULL) {
        return 0; 
    }
    for (int j = 0; j < newRowLength; j++) {
        newRow[j] = newRowData[j];
    }
    currentArray[newRowIndex] = newRow;
    (*numRowsPtr)++;
    return 1;
}
int deleteRow(int*** arrayPtr, int* numRowsPtr, int rowIndex) {
    if (arrayPtr == NULL || numRowsPtr == NULL || rowIndex < 0 || rowIndex >= *numRowsPtr) return 0;
    int** currentArray = *arrayPtr;
    int currentNumRows = *numRowsPtr;
    freeRow(currentArray[rowIndex]);
    for (int i = rowIndex; i < currentNumRows - 1; i++) {
        currentArray[i] = currentArray[i + 1];
    }
    (*numRowsPtr)--;
    if (*numRowsPtr == 0) {
        free(currentArray);
        *arrayPtr = NULL;
    } else {
        int** temp = (int**)realloc(currentArray, (*numRowsPtr) * sizeof(int*));
        if (temp == NULL && *numRowsPtr > 0) {
            return 0; 
        }
        *arrayPtr = temp;
    }
    return 1;
}
int main() {
    int** jaggedArray = NULL;
    int numRows = 0;
    printf("Initializing jagged array.\n");
    int row0_data[] = {10, 20, 30};
    insertRow(&jaggedArray, &numRows, 0, row0_data, 3);
    int row1_data[] = {1, 2, 3, 4, 5};
    insertRow(&jaggedArray, &numRows, 1, row1_data, 5);
    int row2_data[] = {100, 200};
    insertRow(&jaggedArray, &numRows, 2, row2_data, 2);
    printJaggedArray(jaggedArray, numRows);
    printf("\nResizing Row 1 to length 2 (elements 1, 2). Old: 1 2 3 4 5\n");
    resizeRow(jaggedArray, 1, 2);
    printJaggedArray(jaggedArray, numRows);
    printf("\nInserting new row [50, 51, 52, 53] at index 1.\n");
    int newRowData[] = {50, 51, 52, 53};
    insertRow(&jaggedArray, &numRows, 1, newRowData, 4);
    printJaggedArray(jaggedArray, numRows);
    printf("\nDeleting Row 0.\n");
    deleteRow(&jaggedArray, &numRows, 0);
    printJaggedArray(jaggedArray, numRows);
    printf("\nDeleting Row 0 (which is now [50, 51, 52, 53]).\n");
    deleteRow(&jaggedArray, &numRows, 0);
    printJaggedArray(jaggedArray, numRows);
    printf("\nDeleting Row 0 (which is now [100, 200]).\n");
    deleteRow(&jaggedArray, &numRows, 0);
    printJaggedArray(jaggedArray, numRows);
    printf("All operations complete. Freeing remaining memory.\n");
    while(numRows > 0) {
        deleteRow(&jaggedArray, &numRows, 0);
    }
    if (jaggedArray != NULL) {
        free(jaggedArray);
    }
    return 0;
}