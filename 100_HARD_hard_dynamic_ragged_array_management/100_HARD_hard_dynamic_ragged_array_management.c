#include <stdio.h>
#include <stdlib.h>
#define INITIAL_COLLECTION_CAPACITY 2
int main() {
    int **collection = NULL;
    int *row_sizes = NULL;
    int *row_capacities = NULL;
    int collection_size = 0;
    int collection_capacity = 0;
    collection_capacity = INITIAL_COLLECTION_CAPACITY;
    collection = (int **)malloc(collection_capacity * sizeof(int *));
    row_sizes = (int *)malloc(collection_capacity * sizeof(int));
    row_capacities = (int *)malloc(collection_capacity * sizeof(int));
    if (collection == NULL || row_sizes == NULL || row_capacities == NULL) {
        fprintf(stderr, "ERROR: Initial memory allocation failed.\n");
        return 1;
    }
    collection[0] = NULL;
    row_sizes[0] = 0;
    row_capacities[0] = 0;
    collection_size++;
    collection[1] = NULL;
    row_sizes[1] = 0;
    row_capacities[1] = 0;
    collection_size++;
    int row_idx_0 = 0;
    int new_element_0_1 = 10;
    if (row_sizes[row_idx_0] == row_capacities[row_idx_0]) {
        row_capacities[row_idx_0] = (row_capacities[row_idx_0] == 0) ? 1 : row_capacities[row_idx_0] * 2;
        collection[row_idx_0] = (int *)realloc(collection[row_idx_0], row_capacities[row_idx_0] * sizeof(int));
        if (collection[row_idx_0] == NULL) { fprintf(stderr, "ERROR: Realloc failed for row %d.\n", row_idx_0); return 1; }
    }
    collection[row_idx_0][row_sizes[row_idx_0]++] = new_element_0_1;
    int new_element_0_2 = 20;
    if (row_sizes[row_idx_0] == row_capacities[row_idx_0]) {
        row_capacities[row_idx_0] *= 2;
        collection[row_idx_0] = (int *)realloc(collection[row_idx_0], row_capacities[row_idx_0] * sizeof(int));
        if (collection[row_idx_0] == NULL) { fprintf(stderr, "ERROR: Realloc failed for row %d.\n", row_idx_0); return 1; }
    }
    collection[row_idx_0][row_sizes[row_idx_0]++] = new_element_0_2;
    int row_idx_1 = 1;
    int new_element_1_1 = 100;
    if (row_sizes[row_idx_1] == row_capacities[row_idx_1]) {
        row_capacities[row_idx_1] = (row_capacities[row_idx_1] == 0) ? 1 : row_capacities[row_idx_1] * 2;
        collection[row_idx_1] = (int *)realloc(collection[row_idx_1], row_capacities[row_idx_1] * sizeof(int));
        if (collection[row_idx_1] == NULL) { fprintf(stderr, "ERROR: Realloc failed for row %d.\n", row_idx_1); return 1; }
    }
    collection[row_idx_1][row_sizes[row_idx_1]++] = new_element_1_1;
    if (collection_size == collection_capacity) {
        collection_capacity *= 2;
        collection = (int **)realloc(collection, collection_capacity * sizeof(int *));
        row_sizes = (int *)realloc(row_sizes, collection_capacity * sizeof(int));
        row_capacities = (int *)realloc(row_capacities, collection_capacity * sizeof(int));
        if (collection == NULL || row_sizes == NULL || row_capacities == NULL) {
            fprintf(stderr, "ERROR: Realloc failed for main collection.\n");
            return 1;
        }
    }
    collection[collection_size] = NULL;
    row_sizes[collection_size] = 0;
    row_capacities[collection_size] = 0;
    collection_size++;
    int row_idx_2 = 2;
    int new_element_2_1 = 5;
    if (row_sizes[row_idx_2] == row_capacities[row_idx_2]) {
        row_capacities[row_idx_2] = (row_capacities[row_idx_2] == 0) ? 1 : row_capacities[row_idx_2] * 2;
        collection[row_idx_2] = (int *)realloc(collection[row_idx_2], row_capacities[row_idx_2] * sizeof(int));
        if (collection[row_idx_2] == NULL) { fprintf(stderr, "ERROR: Realloc failed for row %d.\n", row_idx_2); return 1; }
    }
    collection[row_idx_2][row_sizes[row_idx_2]++] = new_element_2_1;
    printf("Current Collection:\n");
    for (int i = 0; i < collection_size; i++) {
        printf("  Sequence %d (Size: %d, Capacity: %d): [", i, row_sizes[i], row_capacities[i]);
        for (int j = 0; j < row_sizes[i]; j++) {
            printf("%d", collection[i][j]);
            if (j < row_sizes[i] - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }
    for (int i = 0; i < collection_size; i++) {
        free(collection[i]);
    }
    free(collection);
    free(row_sizes);
    free(row_capacities);
    return 0;
}