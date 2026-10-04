#include <stdio.h>
#include <stdlib.h>
int main() {
    int R = 5;
    int C = 3;
    int **matrix;
    int r, c;
    matrix = (int **)malloc(R * sizeof(int *));
    if (matrix == NULL) {
        return 1;
    }
    for (r = 0; r < R; r++) {
        matrix[r] = (int *)malloc(C * sizeof(int));
        if (matrix[r] == NULL) {
            for (int k = 0; k < r; k++) {
                free(matrix[k]);
            }
            free(matrix);
            return 1;
        }
        for (c = 0; c < C; c++) {
            matrix[r][c] = r * C + c + 1;
        }
    }
    printf("Initial Matrix:\n");
    for (r = 0; r < R; r++) {
        for (c = 0; c < C; c++) {
            printf("%4d", matrix[r][c]);
        }
        printf("\n");
    }
    printf("\n");
    int *valid_rows_indices = (int *)malloc(R * sizeof(int));
    if (valid_rows_indices == NULL) {
        for (r = 0; r < R; r++) {
            free(matrix[r]);
        }
        free(matrix);
        return 1;
    }
    int new_R = 0;
    for (r = 0; r < R; r++) {
        int row_sum = 0;
        for (c = 0; c < C; c++) {
            row_sum += matrix[r][c];
        }
        if (row_sum % 2 == 0) {
            valid_rows_indices[new_R++] = r;
        }
    }
    int **new_matrix = NULL;
    if (new_R > 0) {
        new_matrix = (int **)malloc(new_R * sizeof(int *));
        if (new_matrix == NULL) {
            free(valid_rows_indices);
            for (r = 0; r < R; r++) {
                free(matrix[r]);
            }
            free(matrix);
            return 1;
        }
        for (r = 0; r < new_R; r++) {
            new_matrix[r] = (int *)malloc(C * sizeof(int));
            if (new_matrix[r] == NULL) {
                for (int k = 0; k < r; k++) {
                    free(new_matrix[k]);
                }
                free(new_matrix);
                free(valid_rows_indices);
                for (int k_old = 0; k_old < R; k_old++) {
                    free(matrix[k_old]);
                }
                free(matrix);
                return 1;
            }
            int original_row_idx = valid_rows_indices[r];
            for (c = 0; c < C; c++) {
                new_matrix[r][c] = matrix[original_row_idx][c];
            } 
        }
    }
    for (r = 0; r < R; r++) {
        free(matrix[r]);
    }
    free(matrix);
    free(valid_rows_indices);
    matrix = new_matrix;
    R = new_R;
    printf("Filtered Matrix (rows with odd sum removed):\n");
    if (R == 0) {
        printf("Matrix is empty.\n");
    } else {
        for (r = 0; r < R; r++) {
            for (c = 0; c < C; c++) {
                printf("%4d", matrix[r][c]);
            }
            printf("\n");
        }
    }
    printf("\n");
    for (r = 0; r < R; r++) {
        free(matrix[r]);
    }
    free(matrix);
    return 0;
}