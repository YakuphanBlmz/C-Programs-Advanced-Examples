#include <stdio.h>
#include <stdlib.h>
int main() {
    int** matrix = NULL;
    int rows = 0;
    int cols = 0;
    int r, c;
    int old_rows, old_cols;
    int new_rows, new_cols;
    rows = 2;
    cols = 3;
    matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        return 1;
    }
    for (r = 0; r < rows; r++) {
        matrix[r] = (int*)malloc(cols * sizeof(int));
        if (matrix[r] == NULL) {
            for (int i = 0; i < r; i++) {
                free(matrix[i]);
            }
            free(matrix);
            return 1;
        }
    }
    printf("Initial matrix (%dx%d):\n", rows, cols);
    for (r = 0; r < rows; r++) {
        for (c = 0; c < cols; c++) {
            matrix[r][c] = (r + 1) * 10 + (c + 1);
            printf("%d ", matrix[r][c]);
        }
        printf("\n");
    }
    printf("\n");
    old_rows = rows;
    new_rows = rows + 1;
    int** temp_matrix_rows_inc = (int**)realloc(matrix, new_rows * sizeof(int*));
    if (temp_matrix_rows_inc == NULL) {
        for (r = 0; r < old_rows; r++) {
            free(matrix[r]);
        }
        free(matrix);
        return 1;
    }
    matrix = temp_matrix_rows_inc;
    rows = new_rows;
    matrix[rows - 1] = (int*)malloc(cols * sizeof(int));
    if (matrix[rows - 1] == NULL) {
        for (r = 0; r < rows - 1; r++) {
            free(matrix[r]);
        }
        free(matrix);
        return 1;
    }
    for (c = 0; c < cols; c++) {
        matrix[rows - 1][c] = (rows) * 10 + (c + 1);
    }
    printf("Matrix after adding a row (%dx%d):\n", rows, cols);
    for (r = 0; r < rows; r++) {
        for (c = 0; c < cols; c++) {
            printf("%d ", matrix[r][c]);
        }
        printf("\n");
    }
    printf("\n");
    old_cols = cols;
    new_cols = cols + 1;
    for (r = 0; r < rows; r++) {
        int* temp_row_cols_inc = (int*)realloc(matrix[r], new_cols * sizeof(int));
        if (temp_row_cols_inc == NULL) {
            for (int i = 0; i < rows; i++) {
                if (matrix[i] != NULL) free(matrix[i]);
            }
            free(matrix);
            return 1;
        }
        matrix[r] = temp_row_cols_inc;
        matrix[r][new_cols - 1] = (r + 1) * 100 + (new_cols);
    }
    cols = new_cols;
    printf("Matrix after adding a column (%dx%d):\n", rows, cols);
    for (r = 0; r < rows; r++) {
        for (c = 0; c < cols; c++) {
            printf("%d ", matrix[r][c]);
        }
        printf("\n");
    }
    printf("\n");
    old_rows = rows;
    new_rows = rows - 1;
    if (new_rows < 1) {
        printf("Cannot decrease rows further.\n\n");
    } else {
        free(matrix[old_rows - 1]);
        int** temp_matrix_rows_dec = (int**)realloc(matrix, new_rows * sizeof(int*));
        if (temp_matrix_rows_dec == NULL) {
            for (r = 0; r < new_rows; r++) {
                free(matrix[r]);
            }
            free(matrix);
            return 1;
        }
        matrix = temp_matrix_rows_dec;
        rows = new_rows;
        printf("Matrix after removing a row (%dx%d):\n", rows, cols);
        for (r = 0; r < rows; r++) {
            for (c = 0; c < cols; c++) {
                printf("%d ", matrix[r][c]);
            }
            printf("\n");
        }
        printf("\n");
    }
    old_cols = cols;
    new_cols = cols - 1;
    if (new_cols < 1) {
        printf("Cannot decrease columns further.\n\n");
    } else {
        for (r = 0; r < rows; r++) {
            int* temp_row_cols_dec = (int*)realloc(matrix[r], new_cols * sizeof(int));
            if (temp_row_cols_dec == NULL && new_cols > 0) {
                for (int i = 0; i < rows; i++) {
                    if (matrix[i] != NULL) free(matrix[i]);
                }
                free(matrix);
                return 1;
            }
            matrix[r] = temp_row_cols_dec;
        }
        cols = new_cols;
        printf("Matrix after removing a column (%dx%d):\n", rows, cols);
        for (r = 0; r < rows; r++) {
            for (c = 0; c < cols; c++) {
                printf("%d ", matrix[r][c]);
            }
            printf("\n");
        }
        printf("\n");
    }
    for (r = 0; r < rows; r++) {
        free(matrix[r]);
    }
    free(matrix);
    return 0;
}