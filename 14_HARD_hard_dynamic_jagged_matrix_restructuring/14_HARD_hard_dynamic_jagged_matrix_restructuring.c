#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void restructure_matrix(int ***matrix_ptr, int **row_lengths_ptr, int *num_rows_ptr, int target_row_count, int target_max_col_count) {
    int old_num_rows = *num_rows_ptr;
    int **matrix = *matrix_ptr;
    int *row_lengths = *row_lengths_ptr;
    if (target_row_count < old_num_rows) {
        for (int i = target_row_count; i < old_num_rows; i++) {
            free(matrix[i]);
        }
    }
    int **new_matrix = (int **)realloc(matrix, target_row_count * sizeof(int *));
    int *new_row_lengths = (int *)realloc(row_lengths, target_row_count * sizeof(int));
    if (target_row_count > 0 && (new_matrix == NULL || new_row_lengths == NULL)) {
        return;
    }
    *matrix_ptr = new_matrix;
    *row_lengths_ptr = new_row_lengths;
    *num_rows_ptr = target_row_count;
    matrix = *matrix_ptr;
    row_lengths = *row_lengths_ptr;
    for (int i = old_num_rows; i < target_row_count; i++) {
        matrix[i] = NULL;
        row_lengths[i] = 0;
    }
    for (int i = 0; i < target_row_count; i++) {
        int old_col_count = row_lengths[i];
        int *current_row = matrix[i];
        int *new_row = (int *)realloc(current_row, target_max_col_count * sizeof(int));
        if (target_max_col_count > 0 && new_row == NULL) {
            continue;
        }
        matrix[i] = new_row;
        row_lengths[i] = target_max_col_count;
        if (target_max_col_count > old_col_count) {
            if (matrix[i] != NULL) {
                memset(matrix[i] + old_col_count, 0, (target_max_col_count - old_col_count) * sizeof(int));
            }
        }
    }
}
int main() {
    int **matrix = NULL;
    int *row_lengths = NULL;
    int num_rows = 0;
    num_rows = 2;
    matrix = (int **)malloc(num_rows * sizeof(int *));
    row_lengths = (int *)malloc(num_rows * sizeof(int));
    row_lengths[0] = 3;
    matrix[0] = (int *)malloc(row_lengths[0] * sizeof(int));
    matrix[0][0] = 1; matrix[0][1] = 2; matrix[0][2] = 3;
    row_lengths[1] = 4;
    matrix[1] = (int *)malloc(row_lengths[1] * sizeof(int));
    matrix[1][0] = 10; matrix[1][1] = 20; matrix[1][2] = 30; matrix[1][3] = 40;
    restructure_matrix(&matrix, &row_lengths, &num_rows, 3, 5);
    if (matrix != NULL) {
        for (int i = 0; i < num_rows; i++) {
            free(matrix[i]);
        }
        free(matrix);
    }
    if (row_lengths != NULL) {
        free(row_lengths);
    }
    return 0;
}