#include <stdio.h>
#include <stdlib.h>
int main() {
    int numRows;
    scanf("%d", &numRows);
    int **jaggedArray = (int **)malloc(numRows * sizeof(int *));
    for (int i = 0; i < numRows; i++) {
        int numCols = i + 1;
        jaggedArray[i] = (int *)malloc(numCols * sizeof(int));
        for (int j = 0; j < numCols; j++) {
            jaggedArray[i][j] = (i * 10) + j;
        }
    }
    for (int i = 0; i < numRows; i++) {
        int numCols = i + 1;
        printf("Row %d: ", i);
        for (int j = 0; j < numCols; j++) {
            printf("%d ", jaggedArray[i][j]);
        }
        printf("\n");
    }
    printf("Row Sums:\n");
    for (int i = 0; i < numRows; i++) {
        int numCols = i + 1;
        int rowSum = 0;
        for (int j = 0; j < numCols; j++) {
            rowSum += jaggedArray[i][j];
        }
        printf("Row %d Sum: %d\n", i, rowSum);
    }
    for (int i = 0; i < numRows; i++) {
        free(jaggedArray[i]);
    }
    free(jaggedArray);
    return 0;
}