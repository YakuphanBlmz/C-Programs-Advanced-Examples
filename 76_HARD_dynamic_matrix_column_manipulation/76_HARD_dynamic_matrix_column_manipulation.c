#include <stdio.h>
#include <stdlib.h>
void printMatrix(int **matrix, int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void freeMatrix(int **matrix, int rows) {
    int i;
    for (i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
void insertColumn(int **matrix, int rows, int *cols, int columnIndex, int defaultValue) {
    int i, j;
    (*cols)++;
    for (i = 0; i < rows; i++) {
        matrix[i] = (int *)realloc(matrix[i], (*cols) * sizeof(int));
        if (matrix[i] == NULL) {
            fprintf(stderr, "Realloc failed for row %d during column insertion\n", i);
            exit(EXIT_FAILURE);
        }
        for (j = (*cols) - 1; j > columnIndex; j--) {
            matrix[i][j] = matrix[i][j-1];
        }
        matrix[i][columnIndex] = defaultValue;
    }
}
void deleteColumn(int **matrix, int rows, int *cols, int columnIndex) {
    if (*cols <= 1 || columnIndex < 0 || columnIndex >= *cols) {
        return;
    }
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = columnIndex; j < (*cols) - 1; j++) {
            matrix[i][j] = matrix[i][j+1];
        }
        matrix[i] = (int *)realloc(matrix[i], ((*cols) - 1) * sizeof(int));
        if (matrix[i] == NULL) {
            fprintf(stderr, "Realloc failed for row %d during column deletion\n", i);
            exit(EXIT_FAILURE);
        }
    }
    (*cols)--;
}
int main() {
    int initialRows = 3;
    int initialCols = 4;
    int i, j;
    int **matrix = (int **)malloc(initialRows * sizeof(int *));
    if (matrix == NULL) {
        fprintf(stderr, "Malloc failed for matrix rows\n");
        return EXIT_FAILURE;
    }
    for (i = 0; i < initialRows; i++) {
        matrix[i] = (int *)malloc(initialCols * sizeof(int));
        if (matrix[i] == NULL) {
            fprintf(stderr, "Malloc failed for matrix row %d\n", i);
            for (j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return EXIT_FAILURE;
        }
    }
    for (i = 0; i < initialRows; i++) {
        for (j = 0; j < initialCols; j++) {
            matrix[i][j] = (i + 1) * 10 + (j + 1);
        }
    }
    printf("Initial Matrix (%dx%d):\n", initialRows, initialCols);
    printMatrix(matrix, initialRows, initialCols);
    printf("Inserting column at index 1 with value 99:\n");
    insertColumn(matrix, initialRows, &initialCols, 1, 99);
    printf("Matrix after insertion (%dx%d):\n", initialRows, initialCols);
    printMatrix(matrix, initialRows, initialCols);
    printf("Deleting column at index 0:\n");
    deleteColumn(matrix, initialRows, &initialCols, 0);
    printf("Matrix after deletion (%dx%d):\n", initialRows, initialCols);
    printMatrix(matrix, initialRows, initialCols);
    printf("Inserting column at index %d (end) with value 88:\n", initialCols);
    insertColumn(matrix, initialRows, &initialCols, initialCols, 88);
    printf("Matrix after second insertion (%dx%d):\n", initialRows, initialCols);
    printMatrix(matrix, initialRows, initialCols);
    freeMatrix(matrix, initialRows);
    return 0;
}