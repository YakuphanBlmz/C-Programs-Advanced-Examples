#include <stdio.h>
#include <stdlib.h>
int main() {
    int **jaggedArray = NULL;
    int *rowSizes = NULL;
    int numRows = 0;
    int i, j;
    printf("
    numRows = 3;
    jaggedArray = (int**)malloc(numRows * sizeof(int*));
    if (jaggedArray == NULL) { fprintf(stderr, "Malloc failed for jaggedArray.\n"); return EXIT_FAILURE; }
    rowSizes = (int*)malloc(numRows * sizeof(int));
    if (rowSizes == NULL) { fprintf(stderr, "Malloc failed for rowSizes.\n"); free(jaggedArray); return EXIT_FAILURE; }
    rowSizes[0] = 5;
    jaggedArray[0] = (int*)malloc(rowSizes[0] * sizeof(int));
    if (jaggedArray[0] == NULL) { fprintf(stderr, "Malloc failed for row 0.\n"); free(rowSizes); free(jaggedArray); return EXIT_FAILURE; }
    for (j = 0; j < rowSizes[0]; j++) jaggedArray[0][j] = j + 10;
    rowSizes[1] = 3;
    jaggedArray[1] = (int*)malloc(rowSizes[1] * sizeof(int));
    if (jaggedArray[1] == NULL) { fprintf(stderr, "Malloc failed for row 1.\n"); free(jaggedArray[0]); free(rowSizes); free(jaggedArray); return EXIT_FAILURE; }
    for (j = 0; j < rowSizes[1]; j++) jaggedArray[1][j] = j + 20;
    rowSizes[2] = 7;
    jaggedArray[2] = (int*)malloc(rowSizes[2] * sizeof(int));
    if (jaggedArray[2] == NULL) { fprintf(stderr, "Malloc failed for row 2.\n"); free(jaggedArray[1]); free(jaggedArray[0]); free(rowSizes); free(jaggedArray); return EXIT_FAILURE; }
    for (j = 0; j < rowSizes[2]; j++) jaggedArray[2][j] = j + 30;
    printf("Initial Jagged Array (%d rows):\n", numRows);
    for (i = 0; i < numRows; i++) {
        printf("  Row %d (size %d): ", i, rowSizes[i]);
        for (j = 0; j < rowSizes[i]; j++) {
            printf("%d ", jaggedArray[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("
    int newRowSize = 4;
    int *temp_rowSizes = (int*)realloc(rowSizes, (numRows + 1) * sizeof(int));
    if (temp_rowSizes == NULL) { fprintf(stderr, "Realloc failed for rowSizes during add.\n"); goto cleanup; }
    rowSizes = temp_rowSizes;
    int **temp_jaggedArray = (int**)realloc(jaggedArray, (numRows + 1) * sizeof(int*));
    if (temp_jaggedArray == NULL) { fprintf(stderr, "Realloc failed for jaggedArray during add.\n"); goto cleanup; }
    jaggedArray = temp_jaggedArray;
    numRows++;
    rowSizes[numRows - 1] = newRowSize;
    jaggedArray[numRows - 1] = (int*)malloc(newRowSize * sizeof(int));
    if (jaggedArray[numRows - 1] == NULL) { fprintf(stderr, "Malloc failed for new row.\n"); goto cleanup; }
    for (j = 0; j < newRowSize; j++) jaggedArray[numRows - 1][j] = j + 40;
    printf("Jagged Array after adding a new row (%d rows):\n", numRows);
    for (i = 0; i < numRows; i++) {
        printf("  Row %d (size %d): ", i, rowSizes[i]);
        for (j = 0; j < rowSizes[i]; j++) {
            printf("%d ", jaggedArray[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("
    int rowIndexToResize = 1;
    int new_col_size = 6;
    int *temp_row = (int*)realloc(jaggedArray[rowIndexToResize], new_col_size * sizeof(int));
    if (temp_row == NULL) { fprintf(stderr, "Realloc failed for row %d.\n", rowIndexToResize); goto cleanup; }
    jaggedArray[rowIndexToResize] = temp_row;
    rowSizes[rowIndexToResize] = new_col_size;
    for (j = rowSizes[rowIndexToResize] - (new_col_size - 1); j < new_col_size; j++) { 
        if (j >= 0) jaggedArray[rowIndexToResize][j] = j + 200; 
    }
    printf("Jagged Array after resizing Row %d (new size %d):\n", rowIndexToResize, new_col_size);
    for (i = 0; i < numRows; i++) {
        printf("  Row %d (size %d): ", i, rowSizes[i]);
        for (j = 0; j < rowSizes[i]; j++) {
            printf("%d ", jaggedArray[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("
    int rowIndexToRemove = 0;
    if (rowIndexToRemove >= 0 && rowIndexToRemove < numRows) {
        free(jaggedArray[rowIndexToRemove]);
        for (i = rowIndexToRemove; i < numRows - 1; i++) {
            jaggedArray[i] = jaggedArray[i + 1];
            rowSizes[i] = rowSizes[i + 1];
        }
        numRows--;
        temp_rowSizes = (int*)realloc(rowSizes, numRows * sizeof(int));
        if (temp_rowSizes == NULL && numRows > 0) { fprintf(stderr, "Realloc failed for rowSizes during remove.\n"); goto cleanup; }
        rowSizes = temp_rowSizes;
        temp_jaggedArray = (int**)realloc(jaggedArray, numRows * sizeof(int*));
        if (temp_jaggedArray == NULL && numRows > 0) { fprintf(stderr, "Realloc failed for jaggedArray during remove.\n"); goto cleanup; }
        jaggedArray = temp_jaggedArray;
    }
    printf("Jagged Array after removing Row %d (%d rows):\n", rowIndexToRemove, numRows);
    for (i = 0; i < numRows; i++) {
        printf("  Row %d (size %d): ", i, rowSizes[i]);
        for (j = 0; j < rowSizes[i]; j++) {
            printf("%d ", jaggedArray[i][j]);
        }
        printf("\n");
    }
    printf("\n");
cleanup:
    printf("
    if (jaggedArray != NULL) {
        for (i = 0; i < numRows; i++) {
            if (jaggedArray[i] != NULL) {
                free(jaggedArray[i]);
                jaggedArray[i] = NULL;
            }
        }
        free(jaggedArray);
        jaggedArray = NULL;
    }
    if (rowSizes != NULL) {
        free(rowSizes);
        rowSizes = NULL;
    }
    printf("All memory freed.\n");
    return EXIT_SUCCESS;
}