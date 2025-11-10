#include <stdio.h>
#include <stdlib.h>
void printCollection(int **collection, int rowCount, int *rowSizes) {
    int i, j;
    for (i = 0; i < rowCount; i++) {
        printf("Row %d (Size: %d, Sum: ", i, rowSizes[i]);
        int currentSum = 0;
        for (j = 0; j < rowSizes[i]; j++) {
            currentSum += collection[i][j];
        }
        printf("%d): [", currentSum);
        for (j = 0; j < rowSizes[i]; j++) {
            printf("%d", collection[i][j]);
            if (j < rowSizes[i] - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }
    printf("\n");
}
int calculateRowSum(int *row, int size) {
    int sum = 0;
    int i;
    for (i = 0; i < size; i++) {
        sum += row[i];
    }
    return sum;
}
int main() {
    int **rows = NULL;
    int *rowSizes = NULL;
    int rowCount = 0;
    printf("Initial setup: Creating 3 dynamic rows.\n");
    int initialRowCounts[3] = {3, 2, 4};
    int i, j;
    for (i = 0; i < 3; i++) {
        int newRowSize = initialRowCounts[i];
        rows = (int **)realloc(rows, (rowCount + 1) * sizeof(int *));
        if (rows == NULL) {
            fprintf(stderr, "Memory allocation failed for rows.\n");
            exit(EXIT_FAILURE);
        }
        rowSizes = (int *)realloc(rowSizes, (rowCount + 1) * sizeof(int));
        if (rowSizes == NULL) {
            fprintf(stderr, "Memory allocation failed for rowSizes.\n");
            exit(EXIT_FAILURE);
        }
        rows[rowCount] = (int *)malloc(newRowSize * sizeof(int));
        if (rows[rowCount] == NULL) {
            fprintf(stderr, "Memory allocation failed for individual row.\n");
            exit(EXIT_FAILURE);
        }
        for (j = 0; j < newRowSize; j++) {
            rows[rowCount][j] = (rowCount + 1) * 10 + j;
        }
        rowSizes[rowCount] = newRowSize;
        rowCount++;
    }
    printf("Collection after initial creation:\n");
    printCollection(rows, rowCount, rowSizes);
    printf("Adding a new row of size 5.\n");
    int newRowSizeToAdd = 5;
    rows = (int **)realloc(rows, (rowCount + 1) * sizeof(int *));
    if (rows == NULL) {
        fprintf(stderr, "Memory reallocation failed for rows.\n");
        exit(EXIT_FAILURE);
    }
    rowSizes = (int *)realloc(rowSizes, (rowCount + 1) * sizeof(int));
    if (rowSizes == NULL) {
        fprintf(stderr, "Memory reallocation failed for rowSizes.\n");
        exit(EXIT_FAILURE);
    }
    rows[rowCount] = (int *)malloc(newRowSizeToAdd * sizeof(int));
    if (rows[rowCount] == NULL) {
        fprintf(stderr, "Memory allocation failed for new row.\n");
        exit(EXIT_FAILURE);
    }
    for (j = 0; j < newRowSizeToAdd; j++) {
        rows[rowCount][j] = (rowCount + 1) * 10 + j;
    }
    rowSizes[rowCount] = newRowSizeToAdd;
    rowCount++;
    printf("Collection after adding a new row:\n");
    printCollection(rows, rowCount, rowSizes);
    printf("Sorting rows based on sum (then first element).\n");
    for (i = 0; i < rowCount - 1; i++) {
        for (j = 0; j < rowCount - 1 - i; j++) {
            int sum1 = calculateRowSum(rows[j], rowSizes[j]);
            int sum2 = calculateRowSum(rows[j+1], rowSizes[j+1]);
            if (sum1 > sum2 || (sum1 == sum2 && rows[j][0] > rows[j+1][0])) {
                int *tempRow = rows[j];
                rows[j] = rows[j+1];
                rows[j+1] = tempRow;
                int tempSize = rowSizes[j];
                rowSizes[j] = rowSizes[j+1];
                rowSizes[j+1] = tempSize;
            }
        }
    }
    printf("Collection after sorting:\n");
    printCollection(rows, rowCount, rowSizes);
    printf("Removing row at index 1.\n");
    int indexToRemove = 1;
    if (indexToRemove >= 0 && indexToRemove < rowCount) {
        free(rows[indexToRemove]);
        for (i = indexToRemove; i < rowCount - 1; i++) {
            rows[i] = rows[i+1];
            rowSizes[i] = rowSizes[i+1];
        }
        rowCount--;
        rows = (int **)realloc(rows, rowCount * sizeof(int *));
        if (rowCount > 0 && rows == NULL) {
            fprintf(stderr, "Memory reallocation failed for rows after removal.\n");
            exit(EXIT_FAILURE);
        }
        rowSizes = (int *)realloc(rowSizes, rowCount * sizeof(int));
        if (rowCount > 0 && rowSizes == NULL) {
            fprintf(stderr, "Memory reallocation failed for rowSizes after removal.\n");
            exit(EXIT_FAILURE);
        }
        if (rowCount == 0) {
            rows = NULL;
            rowSizes = NULL;
        }
    } else {
        printf("Invalid index for removal.\n");
    }
    printf("Collection after removing row at index 1:\n");
    printCollection(rows, rowCount, rowSizes);
    printf("Freeing all allocated memory.\n");
    for (i = 0; i < rowCount; i++) {
        free(rows[i]);
    }
    free(rows);
    free(rowSizes);
    rows = NULL;
    rowSizes = NULL;
    rowCount = 0;
    printf("Memory freed. Program finished.\n");
    return 0;
}