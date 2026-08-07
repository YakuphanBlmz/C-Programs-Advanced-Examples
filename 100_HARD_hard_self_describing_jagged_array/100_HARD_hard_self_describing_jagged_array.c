#include <stdio.h>
#include <stdlib.h>
int main() {
    int numRows = 4;
    int rowDataLengths[] = {5, 2, 7, 3};
    int **jaggedArray = (int **)malloc(numRows * sizeof(int *));
    if (jaggedArray == NULL) {
        return 1;
    }
    for (int i = 0; i < numRows; i++) {
        int currentLength = rowDataLengths[i];
        jaggedArray[i] = (int *)malloc((currentLength + 1) * sizeof(int));
        if (jaggedArray[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(jaggedArray[j]);
            }
            free(jaggedArray);
            return 1;
        }
        jaggedArray[i][0] = currentLength;
        for (int j = 0; j < currentLength; j++) {
            jaggedArray[i][j+1] = (i * 100) + j + 1;
        }
    }
    printf("Jagged Array Contents:\n");
    for (int i = 0; i < numRows; i++) {
        int storedLength = jaggedArray[i][0];
        printf("Row %d (Data Count: %d): ", i, storedLength);
        for (int j = 0; j < storedLength; j++) {
            printf("%d ", jaggedArray[i][j+1]);
        }
        printf("\n");
    }
    for (int i = 0; i < numRows; i++) {
        free(jaggedArray[i]);
    }
    free(jaggedArray);
    return 0;
}