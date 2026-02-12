#include <stdio.h>
#include <stdlib.h>
#define INITIAL_ROW_CAPACITY 4
#define INITIAL_NUM_ROWS_CAPACITY 2
#define GROWTH_FACTOR 2
int main() {
    int **jagged_array_data = NULL;
    int *row_current_sizes = NULL;
    int *row_allocated_capacities = NULL;
    int num_active_rows = 0;
    int total_rows_capacity = 0;
    total_rows_capacity = INITIAL_NUM_ROWS_CAPACITY;
    jagged_array_data = (int **)malloc(total_rows_capacity * sizeof(int *));
    row_current_sizes = (int *)malloc(total_rows_capacity * sizeof(int));
    row_allocated_capacities = (int *)malloc(total_rows_capacity * sizeof(int));
    if (!jagged_array_data || !row_current_sizes || !row_allocated_capacities) {
        fprintf(stderr, "Memory allocation failed during initialization.\n");
        return 1;
    }
    printf("Adding initial elements:\n");
    for (int i = 0; i < 3; ++i) {
        if (num_active_rows >= total_rows_capacity) {
            total_rows_capacity *= GROWTH_FACTOR;
            jagged_array_data = (int **)realloc(jagged_array_data, total_rows_capacity * sizeof(int *));
            row_current_sizes = (int *)realloc(row_current_sizes, total_rows_capacity * sizeof(int));
            row_allocated_capacities = (int *)realloc(row_allocated_capacities, total_rows_capacity * sizeof(int));
            if (!jagged_array_data || !row_current_sizes || !row_allocated_capacities) {
                fprintf(stderr, "Memory reallocation failed for main arrays.\n");
                return 1;
            }
        }
        jagged_array_data[num_active_rows] = (int *)malloc(INITIAL_ROW_CAPACITY * sizeof(int));
        if (!jagged_array_data[num_active_rows]) {
            fprintf(stderr, "Memory allocation failed for row %d.\n", num_active_rows);
            return 1;
        }
        row_current_sizes[num_active_rows] = 0;
        row_allocated_capacities[num_active_rows] = INITIAL_ROW_CAPACITY;
        num_active_rows++;
    }
    for (int i = 0; i < 5; ++i) {
        int row_idx = 0;
        if (row_idx >= num_active_rows) {
            fprintf(stderr, "Invalid row index %d.\n", row_idx);
            break;
        }
        if (row_current_sizes[row_idx] >= row_allocated_capacities[row_idx]) {
            row_allocated_capacities[row_idx] *= GROWTH_FACTOR;
            jagged_array_data[row_idx] = (int *)realloc(jagged_array_data[row_idx], row_allocated_capacities[row_idx] * sizeof(int));
            if (!jagged_array_data[row_idx]) {
                fprintf(stderr, "Memory reallocation failed for row %d.\n", row_idx);
                return 1;
            }
        }
        jagged_array_data[row_idx][row_current_sizes[row_idx]++] = 100 + i;
    }
    for (int i = 0; i < 2; ++i) {
        int row_idx = 1;
        if (row_idx >= num_active_rows) {
            fprintf(stderr, "Invalid row index %d.\n", row_idx);
            break;
        }
        if (row_current_sizes[row_idx] >= row_allocated_capacities[row_idx]) {
            row_allocated_capacities[row_idx] *= GROWTH_FACTOR;
            jagged_array_data[row_idx] = (int *)realloc(jagged_array_data[row_idx], row_allocated_capacities[row_idx] * sizeof(int));
            if (!jagged_array_data[row_idx]) {
                fprintf(stderr, "Memory reallocation failed for row %d.\n", row_idx);
                return 1;
            }
        }
        jagged_array_data[row_idx][row_current_sizes[row_idx]++] = 200 + i;
    }
    printf("\nAdding another row:\n");
    int new_row_idx = num_active_rows;
    if (new_row_idx >= total_rows_capacity) {
        total_rows_capacity *= GROWTH_FACTOR;
        jagged_array_data = (int **)realloc(jagged_array_data, total_rows_capacity * sizeof(int *));
        row_current_sizes = (int *)realloc(row_current_sizes, total_rows_capacity * sizeof(int));
        row_allocated_capacities = (int *)realloc(row_allocated_capacities, total_rows_capacity * sizeof(int));
        if (!jagged_array_data || !row_current_sizes || !row_allocated_capacities) {
            fprintf(stderr, "Memory reallocation failed for main arrays.\n");
            return 1;
        }
    }
    jagged_array_data[new_row_idx] = (int *)malloc(INITIAL_ROW_CAPACITY * sizeof(int));
    if (!jagged_array_data[new_row_idx]) {
        fprintf(stderr, "Memory allocation failed for new row %d.\n", new_row_idx);
        return 1;
    }
    row_current_sizes[new_row_idx] = 0;
    row_allocated_capacities[new_row_idx] = INITIAL_ROW_CAPACITY;
    num_active_rows++;
    for (int i = 0; i < 6; ++i) {
        int row_idx = new_row_idx;
        if (row_current_sizes[row_idx] >= row_allocated_capacities[row_idx]) {
            row_allocated_capacities[row_idx] *= GROWTH_FACTOR;
            jagged_array_data[row_idx] = (int *)realloc(jagged_array_data[row_idx], row_allocated_capacities[row_idx] * sizeof(int));
            if (!jagged_array_data[row_idx]) {
                fprintf(stderr, "Memory reallocation failed for row %d.\n", row_idx);
                return 1;
            }
        }
        jagged_array_data[row_idx][row_current_sizes[row_idx]++] = 300 + i;
    }
    printf("\nCurrent state of the jagged array (%d active rows):\n", num_active_rows);
    for (int i = 0; i < num_active_rows; ++i) {
        printf("Row %d (size: %d, capacity: %d): [", i, row_current_sizes[i], row_allocated_capacities[i]);
        for (int j = 0; j < row_current_sizes[i]; ++j) {
            printf("%d%s", jagged_array_data[i][j], (j == row_current_sizes[i] - 1) ? "" : ", ");
        }
        printf("]\n");
    }
    for (int i = 0; i < num_active_rows; ++i) {
        free(jagged_array_data[i]);
    }
    free(jagged_array_data);
    free(row_current_sizes);
    free(row_allocated_capacities);
    printf("\nMemory successfully freed.\n");
    return 0;
}