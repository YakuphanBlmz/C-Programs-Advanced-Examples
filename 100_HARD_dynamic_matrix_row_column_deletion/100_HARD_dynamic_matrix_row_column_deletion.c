#include <stdio.h>
#include <stdlib.h>
int main() {
    int initialRows = 5;
    int initialCols = 6;
    int currentRows = initialRows;
    int currentCols = initialCols;
    int i, j;
    int value = 1;
    int **matrix = (int **)malloc(currentRows * sizeof(int *));
    if (matrix == NULL) {
        return 1;
    }
    for (i = 0; i < currentRows; i++) {
        matrix[i] = (int *)malloc(currentCols * sizeof(int));
        if (matrix[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return 1;
        }
        for (j = 0; j < currentCols; j++) {
            matrix[i][j] = value++;
        }
    }
    printf("Original Matrix (%dx%d):\n", currentRows, currentCols);
    for (i = 0; i < currentRows; i++) {
        for (j = 0; j < currentCols; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    int rowToDelete = 2; 
    if (rowToDelete >= 0 && rowToDelete < currentRows) {
        printf("Deleting Row %d...\n", rowToDelete);
        free(matrix[rowToDelete]);
        for (i = rowToDelete; i < currentRows - 1; i++) {
            matrix[i] = matrix[i + 1];
        }
        currentRows--;
        int **tempMatrix = (int **)realloc(matrix, currentRows * sizeof(int *));
        if (tempMatrix == NULL && currentRows > 0) {
        } else if (currentRows == 0) {
             free(matrix);
             matrix = NULL;
        } else {
            matrix = tempMatrix;
        }
        printf("Matrix after deleting Row %d (%dx%d):\n", rowToDelete, currentRows, currentCols);
        for (i = 0; i < currentRows; i++) {
            for (j = 0; j < currentCols; j++) {
                printf("%3d ", matrix[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    int colToDelete = 3; 
    if (colToDelete >= 0 && colToDelete < currentCols) {
        printf("Deleting Column %d...\n", colToDelete);
        for (i = 0; i < currentRows; i++) {
            for (j = colToDelete; j < currentCols - 1; j++) {
                matrix[i][j] = matrix[i][j + 1];
            }
            int *tempRow = (int *)realloc(matrix[i], (currentCols - 1) * sizeof(int));
            if (tempRow == NULL && currentCols - 1 > 0) {
            } else if (currentCols - 1 == 0) {
                free(matrix[i]);
                matrix[i] = NULL;
            } else {
                matrix[i] = tempRow;
            }
        }
        currentCols--;
        printf("Matrix after deleting Column %d (%dx%d):\n", colToDelete, currentRows, currentCols);
        for (i = 0; i < currentRows; i++) {
            for (j = 0; j < currentCols; j++) {
                printf("%3d ", matrix[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    if (matrix != NULL) {
        for (i = 0; i < currentRows; i++) {
            if (matrix[i] != NULL) {
                free(matrix[i]);
            }
        }
        free(matrix);
    }
    return 0;
}