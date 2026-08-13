#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
void compress_matrix(int*** matrix_ptr, int** row_lengths_ptr, int* num_rows_ptr);
int main() {
    int initial_rows = 5;
    int** matrix = (int**)malloc(initial_rows * sizeof(int*));
    int* row_lengths = (int*)malloc(initial_rows * sizeof(int));
    int num_rows = initial_rows;
    row_lengths[0] = 3;
    matrix[0] = (int*)malloc(row_lengths[0] * sizeof(int));
    matrix[0][0] = 1; matrix[0][1] = 2; matrix[0][2] = 3;
    row_lengths[1] = 2;
    matrix[1] = (int*)malloc(row_lengths[1] * sizeof(int));
    matrix[1][0] = 0; matrix[1][1] = 0;
    row_lengths[2] = 2;
    matrix[2] = (int*)malloc(row_lengths[2] * sizeof(int));
    matrix[2][0] = 4; matrix[2][1] = 5;
    row_lengths[3] = 3;
    matrix[3] = (int*)malloc(row_lengths[3] * sizeof(int));
    matrix[3][0] = 0; matrix[3][1] = 0; matrix[3][2] = 0;
    row_lengths[4] = 1;
    matrix[4] = (int*)malloc(row_lengths[4] * sizeof(int));
    matrix[4][0] = 6;
    printf("Original Matrix:\n");
    for (int i = 0; i < num_rows; i++) {
        printf("Row %d (len %d): ", i, row_lengths[i]);
        for (int j = 0; j < row_lengths[i]; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    compress_matrix(&matrix, &row_lengths, &num_rows);
    printf("Compressed Matrix:\n");
    for (int i = 0; i < num_rows; i++) {
        printf("Row %d (len %d): ", i, row_lengths[i]);
        for (int j = 0; j < row_lengths[i]; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < num_rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(row_lengths);
    return 0;
}
void compress_matrix(int*** matrix_ptr, int** row_lengths_ptr, int* num_rows_ptr) {
    int** matrix = *matrix_ptr;
    int* row_lengths = *row_lengths_ptr;
    int num_rows = *num_rows_ptr;
    int write_idx = 0;
    for (int read_idx = 0; read_idx < num_rows; read_idx++) {
        bool all_zeros = true;
        for (int j = 0; j < row_lengths[read_idx]; j++) {
            if (matrix[read_idx][j] != 0) {
                all_zeros = false;
                break;
            }
        }
        if (all_zeros) {
            free(matrix[read_idx]);
        } else {
            if (read_idx != write_idx) {
                matrix[write_idx] = matrix[read_idx];
                row_lengths[write_idx] = row_lengths[read_idx];
            }
            write_idx++;
        }
    }
    *num_rows_ptr = write_idx;
    if (write_idx == 0) {
        free(matrix);
        *matrix_ptr = NULL;
        free(row_lengths);
        *row_lengths_ptr = NULL;
    } else {
        int** new_matrix = (int**)realloc(matrix, write_idx * sizeof(int*));
        if (new_matrix != NULL) {
            *matrix_ptr = new_matrix;
        }
        int* new_row_lengths = (int*)realloc(row_lengths, write_idx * sizeof(int));
        if (new_row_lengths != NULL) {
            *row_lengths_ptr = new_row_lengths;
        }
    }
}