#include <stdio.h>
#include <stdlib.h>
int** create_matrix(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(matrix[k]);
            }
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}
void populate_matrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = (i + 1) * 10 + (j + 1);
        }
    }
    matrix[0][0] = 1;
    matrix[0][1] = 1;
    matrix[0][2] = 1;
    matrix[1][0] = 5;
    matrix[1][1] = 5;
    matrix[1][2] = 5;
}
void print_matrix(int** matrix, int rows, int cols) {
    if (matrix == NULL || rows == 0 || cols == 0) {
        printf("Matrix is empty or invalid.\n");
        return;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}
int** filter_matrix(int** original, int original_rows, int original_cols, int threshold, int* new_rows_ptr) {
    int valid_rows_count = 0;
    for (int i = 0; i < original_rows; i++) {
        int row_sum = 0;
        for (int j = 0; j < original_cols; j++) {
            row_sum += original[i][j];
        }
        if (row_sum > threshold) {
            valid_rows_count++;
        }
    }
    *new_rows_ptr = valid_rows_count;
    if (valid_rows_count == 0) {
        return NULL;
    }
    int** new_matrix = create_matrix(valid_rows_count, original_cols);
    if (new_matrix == NULL) {
        return NULL;
    }
    int current_new_row = 0;
    for (int i = 0; i < original_rows; i++) {
        int row_sum = 0;
        for (int j = 0; j < original_cols; j++) {
            row_sum += original[i][j];
        }
        if (row_sum > threshold) {
            for (int j = 0; j < original_cols; j++) {
                new_matrix[current_new_row][j] = original[i][j];
            }
            current_new_row++;
        }
    }
    return new_matrix;
}
void free_matrix(int** matrix, int rows) {
    if (matrix == NULL) {
        return;
    }
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
int main() {
    int R = 5;
    int C = 3;
    int threshold = 20;
    int** original_matrix = create_matrix(R, C);
    if (original_matrix == NULL) {
        fprintf(stderr, "Failed to create original matrix.\n");
        return 1;
    }
    populate_matrix(original_matrix, R, C);
    printf("Original Matrix (%d x %d):\n", R, C);
    print_matrix(original_matrix, R, C);
    printf("Threshold: %d\n\n", threshold);
    int new_R = 0;
    int** filtered_matrix = filter_matrix(original_matrix, R, C, threshold, &new_R);
    printf("Filtered Matrix (%d x %d):\n", new_R, C);
    print_matrix(filtered_matrix, new_R, C);
    free_matrix(original_matrix, R);
    free_matrix(filtered_matrix, new_R);
    return 0;
}