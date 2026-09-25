#include <stdio.h>
#include <stdlib.h>
int main() {
    int **collection = NULL;
    int *rowLengths = NULL;
    int rowCount = 0;
    collection = (int**)realloc(collection, sizeof(int*) * (rowCount + 1));
    if (collection == NULL) { return 1; }
    rowLengths = (int*)realloc(rowLengths, sizeof(int) * (rowCount + 1));
    if (rowLengths == NULL) { return 1; }
    collection[rowCount] = (int*)malloc(sizeof(int) * 3);
    if (collection[rowCount] == NULL) { return 1; }
    collection[rowCount][0] = 10;
    collection[rowCount][1] = 20;
    collection[rowCount][2] = 30;
    rowLengths[rowCount] = 3;
    rowCount++;
    collection = (int**)realloc(collection, sizeof(int*) * (rowCount + 1));
    if (collection == NULL) { return 1; }
    rowLengths = (int*)realloc(rowLengths, sizeof(int) * (rowCount + 1));
    if (rowLengths == NULL) { return 1; }
    collection[rowCount] = (int*)malloc(sizeof(int) * 2);
    if (collection[rowCount] == NULL) { return 1; }
    collection[rowCount][0] = 40;
    collection[rowCount][1] = 50;
    rowLengths[rowCount] = 2;
    rowCount++;
    collection = (int**)realloc(collection, sizeof(int*) * (rowCount + 1));
    if (collection == NULL) { return 1; }
    rowLengths = (int*)realloc(rowLengths, sizeof(int) * (rowCount + 1));
    if (rowLengths == NULL) { return 1; }
    collection[rowCount] = (int*)malloc(sizeof(int) * 4);
    if (collection[rowCount] == NULL) { return 1; }
    collection[rowCount][0] = 60;
    collection[rowCount][1] = 70;
    collection[rowCount][2] = 80;
    collection[rowCount][3] = 90;
    rowLengths[rowCount] = 4;
    rowCount++;
    printf("Initial Collection:\n");
    for (int i = 0; i < rowCount; i++) {
        printf("Row %d (length %d): ", i, rowLengths[i]);
        for (int j = 0; j < rowLengths[i]; j++) {
            printf("%d ", collection[i][j]);
        }
        printf("\n");
    }
    printf("---\n");
    int targetRowIndex = 1;
    int newLength = 4;
    if (targetRowIndex < rowCount) {
        collection[targetRowIndex] = (int*)realloc(collection[targetRowIndex], sizeof(int) * newLength);
        if (collection[targetRowIndex] == NULL) { return 1; }
        for (int j = rowLengths[targetRowIndex]; j < newLength; j++) {
            collection[targetRowIndex][j] = (j % 2 == 0) ? 55 : 65;
        }
        rowLengths[targetRowIndex] = newLength;
    }
    printf("Collection after extending Row %d:\n", targetRowIndex);
    for (int i = 0; i < rowCount; i++) {
        printf("Row %d (length %d): ", i, rowLengths[i]);
        for (int j = 0; j < rowLengths[i]; j++) {
            printf("%d ", collection[i][j]);
        }
        printf("\n");
    }
    printf("---\n");
    int removeRowIndex = 0;
    if (removeRowIndex >= 0 && removeRowIndex < rowCount) {
        free(collection[removeRowIndex]);
        for (int i = removeRowIndex; i < rowCount - 1; i++) {
            collection[i] = collection[i+1];
            rowLengths[i] = rowLengths[i+1];
        }
        rowCount--;
        collection = (int**)realloc(collection, sizeof(int*) * rowCount);
        rowLengths = (int*)realloc(rowLengths, sizeof(int) * rowCount);
        if (rowCount > 0 && collection == NULL) { return 1; }
        if (rowCount > 0 && rowLengths == NULL) { return 1; }
    }
    printf("Collection after removing Row %d:\n", removeRowIndex);
    for (int i = 0; i < rowCount; i++) {
        printf("Row %d (length %d): ", i, rowLengths[i]);
        for (int j = 0; j < rowLengths[i]; j++) {
            printf("%d ", collection[i][j]);
        }
        printf("\n");
    }
    printf("---\n");
    for (int i = 0; i < rowCount; i++) {
        free(collection[i]);
    }
    free(collection);
    free(rowLengths);
    return 0;
}