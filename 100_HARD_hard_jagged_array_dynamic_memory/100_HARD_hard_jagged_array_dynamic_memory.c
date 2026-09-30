#include <stdio.h>
#include <stdlib.h>
int** allocateJaggedArray(int* groupSizes, int numGroups) {
    int** jaggedArray = (int**)malloc(numGroups * sizeof(int*));
    if (jaggedArray == NULL) {
        return NULL;
    }
    for (int i = 0; i < numGroups; i++) {
        jaggedArray[i] = (int*)malloc(groupSizes[i] * sizeof(int));
        if (jaggedArray[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(jaggedArray[j]);
            }
            free(jaggedArray);
            return NULL;
        }
    }
    return jaggedArray;
}
void fillJaggedArray(int** jaggedArray, int* groupSizes, int numGroups) {
    int currentVal = 0;
    for (int i = 0; i < numGroups; i++) {
        for (int j = 0; j < groupSizes[i]; j++) {
            jaggedArray[i][j] = currentVal++;
        }
    }
}
void printJaggedArray(int** jaggedArray, int* groupSizes, int numGroups) {
    for (int i = 0; i < numGroups; i++) {
        printf("Group %d: ", i);
        for (int j = 0; j < groupSizes[i]; j++) {
            printf("%d ", jaggedArray[i][j]);
        }
        printf("\n");
    }
}
void freeJaggedArray(int** jaggedArray, int numGroups) {
    for (int i = 0; i < numGroups; i++) {
        free(jaggedArray[i]);
    }
    free(jaggedArray);
}
int main() {
    int groupSizes[] = {3, 5, 2, 4, 6};
    int numGroups = sizeof(groupSizes) / sizeof(groupSizes[0]);
    int** myJaggedArray = allocateJaggedArray(groupSizes, numGroups);
    if (myJaggedArray == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    fillJaggedArray(myJaggedArray, groupSizes, numGroups);
    printJaggedArray(myJaggedArray, groupSizes, numGroups);
    freeJaggedArray(myJaggedArray, numGroups);
    return 0;
}