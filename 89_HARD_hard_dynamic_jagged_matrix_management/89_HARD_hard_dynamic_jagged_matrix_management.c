#include <stdio.h>
#include <stdlib.h>
int main() {
    int **matrix = NULL;
    int *row_lengths = NULL;
    int *row_capacities = NULL;
    int num_rows = 0;
    int matrix_capacity = 0;
    int initial_rows = 3;
    int initial_col_size = 5;
    matrix_capacity = initial_rows;
    matrix = (int **)malloc(matrix_capacity * sizeof(int *));
    if (matrix == NULL) {
        return 1;
    }
    row_lengths = (int *)malloc(matrix_capacity * sizeof(int));
    if (row_lengths == NULL) {
        free(matrix);
        return 1;
    }
    row_capacities = (int *)malloc(matrix_capacity * sizeof(int));
    if (row_capacities == NULL) {
        free(matrix);
        free(row_lengths);
        return 1;
    }
    for (int i = 0; i < initial_rows; i++) {
        matrix[i] = (int *)malloc(initial_col_size * sizeof(int));
        if (matrix[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(matrix[k]);
            }
            free(matrix);
            free(row_lengths);
            free(row_capacities);
            return 1;
        }
        row_lengths[i] = initial_col_size;
        row_capacities[i] = initial_col_size;
        for (int j = 0; j < initial_col_size; j++) {
            matrix[i][j] = (i + 1) * 10 + j;
        }
    }
    num_rows = initial_rows;
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < row_lengths[i]; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("----------\n");
    int new_row_size = 4;
    int grow_factor = 2;
    if (num_rows == matrix_capacity) {
        matrix_capacity *= grow_factor;
        int **temp_matrix = (int **)realloc(matrix, matrix_capacity * sizeof(int *));
        if (temp_matrix == NULL) { return 1; }
        matrix = temp_matrix;
        int *temp_lengths = (int *)realloc(row_lengths, matrix_capacity * sizeof(int));
        if (temp_lengths == NULL) { return 1; }
        row_lengths = temp_lengths;
        int *temp_capacities = (int *)realloc(row_capacities, matrix_capacity * sizeof(int));
        if (temp_capacities == NULL) { return 1; }
        row_capacities = temp_capacities;
    }
    matrix[num_rows] = (int *)malloc(new_row_size * sizeof(int));
    if (matrix[num_rows] == NULL) { return 1; }
    row_lengths[num_rows] = new_row_size;
    row_capacities[num_rows] = new_row_size;
    for (int j = 0; j < new_row_size; j++) {
        matrix[num_rows][j] = (num_rows + 1) * 10 + j;
    }
    num_rows++;
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < row_lengths[i]; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("----------\n");
    int target_row_index_resize = 0;
    int new_row_length_resize = 7;
    if (target_row_index_resize >= 0 && target_row_index_resize < num_rows) {
        if (new_row_length_resize > row_capacities[target_row_index_resize]) {
            int *temp_row = (int *)realloc(matrix[target_row_index_resize], new_row_length_resize * sizeof(int));
            if (temp_row == NULL) { return 1; }
            matrix[target_row_index_resize] = temp_row;
            row_capacities[target_row_index_resize] = new_row_length_resize;
        }
        for (int j = row_lengths[target_row_index_resize]; j < new_row_length_resize; j++) {
            matrix[target_row_index_resize][j] = 0;
        }
        row_lengths[target_row_index_resize] = new_row_length_resize;
    }
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < row_lengths[i]; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("----------\n");
    int target_row_index_remove = 1;
    if (target_row_index_remove >= 0 && target_row_index_remove < num_rows) {
        free(matrix[target_row_index_remove]);
        for (int i = target_row_index_remove; i < num_rows - 1; i++) {
            matrix[i] = matrix[i + 1];
            row_lengths[i] = row_lengths[i + 1];
            row_capacities[i] = row_capacities[i + 1];
        }
        num_rows--;
    }
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < row_lengths[i]; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("----------\n");
    for (int i = 0; i < num_rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(row_lengths);
    free(row_capacities);
    return 0;
}