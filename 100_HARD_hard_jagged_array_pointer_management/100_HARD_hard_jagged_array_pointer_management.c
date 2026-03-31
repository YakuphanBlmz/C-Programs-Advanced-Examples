#include <stdio.h>
#include <stdlib.h>
int main() {
    int **jaggedArray = NULL;
    int currentRows = 0;
    int maxRowsCapacity = 0;
    int row1_len = 3;
    if (currentRows == maxRowsCapacity) {
        maxRowsCapacity = (maxRowsCapacity == 0) ? 2 : maxRowsCapacity * 2;
        jaggedArray = (int**)realloc(jaggedArray, maxRowsCapacity * sizeof(int*));
        if (jaggedArray == NULL) return 1;
    }
    int *newRow1 = (int*)malloc((1 + row1_len) * sizeof(int));
    if (newRow1 == NULL) return 1;
    newRow1[0] = row1_len;
    newRow1[1] = 10;
    newRow1[2] = 20;
    newRow1[3] = 30;
    jaggedArray[currentRows++] = newRow1;
    int row2_len = 2;
    if (currentRows == maxRowsCapacity) {
        maxRowsCapacity = (maxRowsCapacity == 0) ? 2 : maxRowsCapacity * 2;
        jaggedArray = (int**)realloc(jaggedArray, maxRowsCapacity * sizeof(int*));
        if (jaggedArray == NULL) return 1;
    }
    int *newRow2 = (int*)malloc((1 + row2_len) * sizeof(int));
    if (newRow2 == NULL) return 1;
    newRow2[0] = row2_len;
    newRow2[1] = 100;
    newRow2[2] = 200;
    jaggedArray[currentRows++] = newRow2;
    int row3_len = 4;
    if (currentRows == maxRowsCapacity) {
        maxRowsCapacity = (maxRowsCapacity == 0) ? 2 : maxRowsCapacity * 2;
        jaggedArray = (int**)realloc(jaggedArray, maxRowsCapacity * sizeof(int*));
        if (jaggedArray == NULL) return 1;
    }
    int *newRow3 = (int*)malloc((1 + row3_len) * sizeof(int));
    if (newRow3 == NULL) return 1;
    newRow3[0] = row3_len;
    newRow3[1] = 1;
    newRow3[2] = 2;
    newRow3[3] = 3;
    newRow3[4] = 4;
    jaggedArray[currentRows++] = newRow3;
    printf("Initial State:\n");
    for (int i = 0; i < currentRows; i++) {
        int len = jaggedArray[i][0];
        printf("Row %d (len %d):", i, len);
        for (int j = 1; j <= len; j++) {
            printf(" %d", jaggedArray[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    int resizeIndex = 0;
    int newLen = 5;
    if (resizeIndex >= 0 && resizeIndex < currentRows) {
        int *oldRow = jaggedArray[resizeIndex];
        int oldLen = oldRow[0];
        int *resizedRow = (int*)realloc(oldRow, (1 + newLen) * sizeof(int));
        if (resizedRow == NULL) return 1;
        resizedRow[0] = newLen;
        if (newLen > oldLen) {
            for (int k = oldLen + 1; k <= newLen; k++) {
                resizedRow[k] = k * 100;
            }
        }
        jaggedArray[resizeIndex] = resizedRow;
    }
    printf("State after resizing Row %d to length %d:\n", resizeIndex, newLen);
    for (int i = 0; i < currentRows; i++) {
        int len = jaggedArray[i][0];
        printf("Row %d (len %d):", i, len);
        for (int j = 1; j <= len; j++) {
            printf(" %d", jaggedArray[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    int removeIndex = 1;
    if (removeIndex >= 0 && removeIndex < currentRows) {
        free(jaggedArray[removeIndex]);
        for (int i = removeIndex; i < currentRows - 1; i++) {
            jaggedArray[i] = jaggedArray[i+1];
        }
        currentRows--;
    }
    printf("State after removing Row %d:\n", removeIndex);
    for (int i = 0; i < currentRows; i++) {
        int len = jaggedArray[i][0];
        printf("Row %d (len %d):", i, len);
        for (int j = 1; j <= len; j++) {
            printf(" %d", jaggedArray[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < currentRows; i++) {
        free(jaggedArray[i]);
    }
    free(jaggedArray);
    return 0;
}