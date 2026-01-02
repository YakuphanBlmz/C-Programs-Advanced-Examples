#include <stdio.h>
#include <stdlib.h>
int** normalizeAndRectify(int** ragged_array, int rows, int* col_counts) {
    if (ragged_array == NULL || col_counts == NULL || rows <= 0) {
        return NULL;
    }
    int max_cols = 0;
    for (int i = 0; i < rows; ++i) {
        if (col_counts[i] > max_cols) {
            max_cols = col_counts[i];
        }
    }
    if (max_cols == 0) {
        for (int i = 0; i < rows; ++i) {
            free(ragged_array[i]);
        }
        free(ragged_array);
        return NULL;
    }
    int** rectangular_array = (int**)malloc(rows * sizeof(int*));
    if (rectangular_array == NULL) {
        for (int i = 0; i < rows; ++i) {
            free(ragged_array[i]);
        }
        free(ragged_array);
        return NULL;
    }
    for (int i = 0; i < rows; ++i) {
        rectangular_array[i] = (int*)malloc(max_cols * sizeof(int));
        if (rectangular_array[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(rectangular_array[j]);
            }
            free(rectangular_array);
            for (int j = 0; j < rows; ++j) {
                free(ragged_array[j]);
            }
            free(ragged_array);
            return NULL;
        }
        for (int j = 0; j < max_cols; ++j) {
            if (j < col_counts[i]) {
                rectangular_array[i][j] = ragged_array[i][j];
            } else {
                rectangular_array[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < rows; ++i) {
        free(ragged_array[i]);
    }
    free(ragged_array);
    return rectangular_array;
}
void printMatrix(int** matrix, int rows, int cols) {
    if (matrix == NULL || rows <= 0 || cols <= 0) {
        return;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
int main() {
    int initial_rows = 3;
    int* initial_col_counts = (int*)malloc(initial_rows * sizeof(int));
    if (initial_col_counts == NULL) {
        return 1;
    }
    initial_col_counts[0] = 4;
    initial_col_counts[1] = 2;
    initial_col_counts[2] = 5;
    int** ragged_matrix = (int**)malloc(initial_rows * sizeof(int*));
    if (ragged_matrix == NULL) {
        free(initial_col_counts);
        return 1;
    }
    for (int i = 0; i < initial_rows; ++i) {
        ragged_matrix[i] = (int*)malloc(initial_col_counts[i] * sizeof(int));
        if (ragged_matrix[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(ragged_matrix[j]);
            }
            free(ragged_matrix);
            free(initial_col_counts);
            return 1;
        }
        for (int j = 0; j < initial_col_counts[i]; ++j) {
            ragged_matrix[i][j] = (i + 1) * 10 + j + 1;
        }
    }
    int max_cols_for_rectified = 0;
    for (int i = 0; i < initial_rows; ++i) {
        if (initial_col_counts[i] > max_cols_for_rectified) {
            max_cols_for_rectified = initial_col_counts[i];
        }
    }
    int** rectified_matrix = normalizeAndRectify(ragged_matrix, initial_rows, initial_col_counts);
    if (rectified_matrix == NULL) {
        free(initial_col_counts);
        return 1;
    }
    printf("Rectified Matrix:\n");
    printMatrix(rectified_matrix, initial_rows, max_cols_for_rectified);
    if (initial_rows >= 2) {
        int* temp_row = rectified_matrix[0];
        rectified_matrix[0] = rectified_matrix[1];
        rectified_matrix[1] = temp_row;
        printf("\nMatrix after swapping row 0 and row 1:\n");
        printMatrix(rectified_matrix, initial_rows, max_cols_for_rectified);
    }
    for (int i = 0; i < initial_rows; ++i) {
        free(rectified_matrix[i]);
    }
    free(rectified_matrix);
    free(initial_col_counts);
    return 0;
}