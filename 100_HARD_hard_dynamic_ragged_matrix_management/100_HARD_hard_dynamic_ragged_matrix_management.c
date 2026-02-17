#include <stdio.h>
#include <stdlib.h>
int main() {
    int **matrix_data = NULL;
    int *row_lengths = NULL;
    int num_rows = 0;
    int capacity_rows = 0;
    int initial_capacity = 2;
    matrix_data = (int **)malloc(initial_capacity * sizeof(int *));
    row_lengths = (int *)malloc(initial_capacity * sizeof(int));
    capacity_rows = initial_capacity;
    printf("Initial setup complete. Capacity: %d, Rows: %d\n\n", capacity_rows, num_rows);
    int new_row_len_0 = 3;
    if (num_rows >= capacity_rows) {
        capacity_rows *= 2;
        matrix_data = (int **)realloc(matrix_data, capacity_rows * sizeof(int *));
        row_lengths = (int *)realloc(row_lengths, capacity_rows * sizeof(int));
    }
    matrix_data[num_rows] = (int *)malloc(new_row_len_0 * sizeof(int));
    row_lengths[num_rows] = new_row_len_0;
    for (int i = 0; i < new_row_len_0; i++) {
        matrix_data[num_rows][i] = (num_rows + 1) * 10 + i;
    }
    num_rows++;
    int new_row_len_1 = 5;
    if (num_rows >= capacity_rows) {
        capacity_rows *= 2;
        matrix_data = (int **)realloc(matrix_data, capacity_rows * sizeof(int *));
        row_lengths = (int *)realloc(row_lengths, capacity_rows * sizeof(int));
    }
    matrix_data[num_rows] = (int *)malloc(new_row_len_1 * sizeof(int));
    row_lengths[num_rows] = new_row_len_1;
    for (int i = 0; i < new_row_len_1; i++) {
        matrix_data[num_rows][i] = (num_rows + 1) * 10 + i;
    }
    num_rows++;
    printf("After adding two rows:\n");
    for (int i = 0; i < num_rows; i++) {
        printf("Row %d (length %d): ", i, row_lengths[i]);
        for (int j = 0; j < row_lengths[i]; j++) {
            printf("%d ", matrix_data[i][j]);
        }
        printf("\n");
    }
    printf("Current Capacity: %d, Rows: %d\n\n", capacity_rows, num_rows);
    int row_to_resize_idx = 0;
    int new_row_len_resized = 4;
    if (row_to_resize_idx < num_rows) {
        matrix_data[row_to_resize_idx] = (int *)realloc(matrix_data[row_to_resize_idx], new_row_len_resized * sizeof(int));
        for (int i = row_lengths[row_to_resize_idx]; i < new_row_len_resized; i++) {
            matrix_data[row_to_resize_idx][i] = 99;
        }
        row_lengths[row_to_resize_idx] = new_row_len_resized;
    }
    printf("After resizing row %d to length %d:\n", row_to_resize_idx, new_row_len_resized);
    for (int i = 0; i < num_rows; i++) {
        printf("Row %d (length %d): ", i, row_lengths[i]);
        for (int j = 0; j < row_lengths[i]; j++) {
            printf("%d ", matrix_data[i][j]);
        }
        printf("\n");
    }
    printf("Current Capacity: %d, Rows: %d\n\n", capacity_rows, num_rows);
    int new_row_len_2 = 2;
    if (num_rows >= capacity_rows) {
        capacity_rows *= 2;
        matrix_data = (int **)realloc(matrix_data, capacity_rows * sizeof(int *));
        row_lengths = (int *)realloc(row_lengths, capacity_rows * sizeof(int));
    }
    matrix_data[num_rows] = (int *)malloc(new_row_len_2 * sizeof(int));
    row_lengths[num_rows] = new_row_len_2;
    for (int i = 0; i < new_row_len_2; i++) {
        matrix_data[num_rows][i] = (num_rows + 1) * 10 + i;
    }
    num_rows++;
    printf("After adding a new row (forcing capacity realloc):\n");
    for (int i = 0; i < num_rows; i++) {
        printf("Row %d (length %d): ", i, row_lengths[i]);
        for (int j = 0; j < row_lengths[i]; j++) {
            printf("%d ", matrix_data[i][j]);
        }
        printf("\n");
    }
    printf("Current Capacity: %d, Rows: %d\n\n", capacity_rows, num_rows);
    int row_to_remove_idx = 1;
    if (row_to_remove_idx < num_rows) {
        free(matrix_data[row_to_remove_idx]);
        for (int i = row_to_remove_idx; i < num_rows - 1; i++) {
            matrix_data[i] = matrix_data[i + 1];
            row_lengths[i] = row_lengths[i + 1];
        }
        num_rows--;
    }
    printf("After removing row %d:\n", row_to_remove_idx);
    for (int i = 0; i < num_rows; i++) {
        printf("Row %d (length %d): ", i, row_lengths[i]);
        for (int j = 0; j < row_lengths[i]; j++) {
            printf("%d ", matrix_data[i][j]);
        }
        printf("\n");
    }
    printf("Current Capacity: %d, Rows: %d\n\n", capacity_rows, num_rows);
    for (int i = 0; i < num_rows; i++) {
        free(matrix_data[i]);
    }
    free(matrix_data);
    free(row_lengths);
    printf("All memory freed. Program finished.\n");
    return 0;
}