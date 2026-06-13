#include <stdio.h>
#include <stdlib.h>
int main() {
    int** matrix = NULL;
    int* row_sizes = NULL;
    int* row_capacities = NULL;
    int num_rows = 0;
    int max_rows_capacity = 0;
    int initial_rows_capacity = 2;
    max_rows_capacity = initial_rows_capacity;
    matrix = (int**)malloc(max_rows_capacity * sizeof(int*));
    row_sizes = (int*)malloc(max_rows_capacity * sizeof(int));
    row_capacities = (int*)malloc(max_rows_capacity * sizeof(int));
    if (!matrix || !row_sizes || !row_capacities) {
        fprintf(stderr, "Memory allocation failed at initialization.\n");
        return 1;
    }
    if (num_rows >= max_rows_capacity) {
        max_rows_capacity *= 2;
        matrix = (int**)realloc(matrix, max_rows_capacity * sizeof(int*));
        row_sizes = (int*)realloc(row_sizes, max_rows_capacity * sizeof(int));
        row_capacities = (int*)realloc(row_capacities, max_rows_capacity * sizeof(int));
        if (!matrix || !row_sizes || !row_capacities) { fprintf(stderr, "Realloc failed for matrix/metadata.\n"); goto cleanup; }
    }
    matrix[num_rows] = NULL;
    row_sizes[num_rows] = 0;
    row_capacities[num_rows] = 0;
    num_rows++;
    int row_idx_0 = 0;
    int new_element_0 = 10;
    if (row_sizes[row_idx_0] >= row_capacities[row_idx_0]) {
        row_capacities[row_idx_0] = (row_capacities[row_idx_0] == 0) ? 2 : row_capacities[row_idx_0] * 2;
        matrix[row_idx_0] = (int*)realloc(matrix[row_idx_0], row_capacities[row_idx_0] * sizeof(int));
        if (!matrix[row_idx_0]) { fprintf(stderr, "Realloc failed for row 0.\n"); goto cleanup; }
    }
    matrix[row_idx_0][row_sizes[row_idx_0]++] = new_element_0;
    new_element_0 = 20;
    if (row_sizes[row_idx_0] >= row_capacities[row_idx_0]) {
        row_capacities[row_idx_0] = (row_capacities[row_idx_0] == 0) ? 2 : row_capacities[row_idx_0] * 2;
        matrix[row_idx_0] = (int*)realloc(matrix[row_idx_0], row_capacities[row_idx_0] * sizeof(int));
        if (!matrix[row_idx_0]) { fprintf(stderr, "Realloc failed for row 0.\n"); goto cleanup; }
    }
    matrix[row_idx_0][row_sizes[row_idx_0]++] = new_element_0;
    if (num_rows >= max_rows_capacity) {
        max_rows_capacity *= 2;
        matrix = (int**)realloc(matrix, max_rows_capacity * sizeof(int*));
        row_sizes = (int*)realloc(row_sizes, max_rows_capacity * sizeof(int));
        row_capacities = (int*)realloc(row_capacities, max_rows_capacity * sizeof(int));
        if (!matrix || !row_sizes || !row_capacities) { fprintf(stderr, "Realloc failed for matrix/metadata.\n"); goto cleanup; }
    }
    matrix[num_rows] = NULL;
    row_sizes[num_rows] = 0;
    row_capacities[num_rows] = 0;
    num_rows++;
    int row_idx_1 = 1;
    int new_element_1 = 30;
    if (row_sizes[row_idx_1] >= row_capacities[row_idx_1]) {
        row_capacities[row_idx_1] = (row_capacities[row_idx_1] == 0) ? 2 : row_capacities[row_idx_1] * 2;
        matrix[row_idx_1] = (int*)realloc(matrix[row_idx_1], row_capacities[row_idx_1] * sizeof(int));
        if (!matrix[row_idx_1]) { fprintf(stderr, "Realloc failed for row 1.\n"); goto cleanup; }
    }
    matrix[row_idx_1][row_sizes[row_idx_1]++] = new_element_1;
    new_element_1 = 40;
    if (row_sizes[row_idx_1] >= row_capacities[row_idx_1]) {
        row_capacities[row_idx_1] = (row_capacities[row_idx_1] == 0) ? 2 : row_capacities[row_idx_1] * 2;
        matrix[row_idx_1] = (int*)realloc(matrix[row_idx_1], row_capacities[row_idx_1] * sizeof(int));
        if (!matrix[row_idx_1]) { fprintf(stderr, "Realloc failed for row 1.\n"); goto cleanup; }
    }
    matrix[row_idx_1][row_sizes[row_idx_1]++] = new_element_1;
    new_element_1 = 50;
    if (row_sizes[row_idx_1] >= row_capacities[row_idx_1]) {
        row_capacities[row_idx_1] = (row_capacities[row_idx_1] == 0) ? 2 : row_capacities[row_idx_1] * 2;
        matrix[row_idx_1] = (int*)realloc(matrix[row_idx_1], row_capacities[row_idx_1] * sizeof(int));
        if (!matrix[row_idx_1]) { fprintf(stderr, "Realloc failed for row 1.\n"); goto cleanup; }
    }
    matrix[row_idx_1][row_sizes[row_idx_1]++] = new_element_1;
    if (num_rows >= max_rows_capacity) {
        max_rows_capacity *= 2;
        matrix = (int**)realloc(matrix, max_rows_capacity * sizeof(int*));
        row_sizes = (int*)realloc(row_sizes, max_rows_capacity * sizeof(int));
        row_capacities = (int*)realloc(row_capacities, max_rows_capacity * sizeof(int));
        if (!matrix || !row_sizes || !row_capacities) { fprintf(stderr, "Realloc failed for matrix/metadata.\n"); goto cleanup; }
    }
    matrix[num_rows] = NULL;
    row_sizes[num_rows] = 0;
    row_capacities[num_rows] = 0;
    num_rows++;
    int row_idx_2 = 2;
    int new_element_2 = 60;
    if (row_sizes[row_idx_2] >= row_capacities[row_idx_2]) {
        row_capacities[row_idx_2] = (row_capacities[row_idx_2] == 0) ? 2 : row_capacities[row_idx_2] * 2;
        matrix[row_idx_2] = (int*)realloc(matrix[row_idx_2], row_capacities[row_idx_2] * sizeof(int));
        if (!matrix[row_idx_2]) { fprintf(stderr, "Realloc failed for row 2.\n"); goto cleanup; }
    }
    matrix[row_idx_2][row_sizes[row_idx_2]++] = new_element_2;
    printf("Initial matrix:\n");
    for (int i = 0; i < num_rows; i++) {
        printf("Row %d: [", i);
        for (int j = 0; j < row_sizes[i]; j++) {
            printf("%d", matrix[i][j]);
            if (j < row_sizes[i] - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }
    int target_row = 1;
    int element_to_remove_index = 1;
    if (target_row < num_rows && element_to_remove_index >= 0 && element_to_remove_index < row_sizes[target_row]) {
        printf("Removing element at row %d, index %d...\n", target_row, element_to_remove_index);
        for (int i = element_to_remove_index; i < row_sizes[target_row] - 1; i++) {
            matrix[target_row][i] = matrix[target_row][i+1];
        }
        row_sizes[target_row]--;
        if (row_sizes[target_row] > 0 && row_sizes[target_row] < row_capacities[target_row] / 2) {
            int* temp_row = (int*)realloc(matrix[target_row], (row_capacities[target_row] / 2) * sizeof(int));
            if (temp_row) {
                matrix[target_row] = temp_row;
                row_capacities[target_row] /= 2;
            } else {  }
        } else if (row_sizes[target_row] == 0) {
            free(matrix[target_row]);
            matrix[target_row] = NULL;
            row_capacities[target_row] = 0;
        }
    }
    printf("Matrix after removing element from row 1:\n");
    for (int i = 0; i < num_rows; i++) {
        printf("Row %d: [", i);
        for (int j = 0; j < row_sizes[i]; j++) {
            printf("%d", matrix[i][j]);
            if (j < row_sizes[i] - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }
cleanup:
    if (matrix) {
        for (int i = 0; i < num_rows; i++) {
            if (matrix[i] != NULL) {
                free(matrix[i]);
            }
        }
        free(matrix);
    }
    if (row_sizes) {
        free(row_sizes);
    }
    if (row_capacities) {
        free(row_capacities);
    }
    return 0;
}