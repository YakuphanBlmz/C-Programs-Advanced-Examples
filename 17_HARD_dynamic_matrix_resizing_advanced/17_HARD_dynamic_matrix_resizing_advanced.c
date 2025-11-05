#include <stdio.h>
#include <stdlib.h>
int** create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) return NULL;
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) return NULL;
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 0;
        }
    }
    return matrix;
}
void print_matrix(int** matrix, int rows, int cols) {
    if (matrix == NULL || rows <= 0 || cols <= 0) {
        printf("Matrix is empty or invalid.\n");
        return;
    }
    printf("Matrix (%dx%d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void resize_matrix(int*** matrix_ptr, int* current_rows_ptr, int* current_cols_ptr, int new_rows, int new_cols) {
    int current_rows = *current_rows_ptr;
    int current_cols = *current_cols_ptr;
    if (new_rows < 0 || new_cols < 0) {
        return;
    }
    if (new_rows == 0 || new_cols == 0) {
        if (*matrix_ptr != NULL) {
            for (int i = 0; i < current_rows; i++) {
                free((*matrix_ptr)[i]);
                (*matrix_ptr)[i] = NULL;
            }
            free(*matrix_ptr);
            *matrix_ptr = NULL;
        }
        *current_rows_ptr = 0;
        *current_cols_ptr = 0;
        return;
    }
    if (new_rows < current_rows) {
        for (int i = new_rows; i < current_rows; i++) {
            free((*matrix_ptr)[i]);
            (*matrix_ptr)[i] = NULL;
        }
    }
    int** new_matrix_ptr_array = (int**)realloc(*matrix_ptr, new_rows * sizeof(int*));
    if (new_matrix_ptr_array == NULL) {
        return;
    }
    *matrix_ptr = new_matrix_ptr_array;
    for (int i = 0; i < new_rows; i++) {
        if (i < current_rows) {
            int* new_row_data = (int*)realloc((*matrix_ptr)[i], new_cols * sizeof(int));
            if (new_row_data == NULL) {
                return;
            }
            (*matrix_ptr)[i] = new_row_data;
            if (new_cols > current_cols) {
                for (int j = current_cols; j < new_cols; j++) {
                    (*matrix_ptr)[i][j] = 0;
                }
            }
        } else {
            (*matrix_ptr)[i] = (int*)malloc(new_cols * sizeof(int));
            if ((*matrix_ptr)[i] == NULL) {
                return;
            }
            for (int j = 0; j < new_cols; j++) {
                (*matrix_ptr)[i][j] = 0;
            }
        }
    }
    *current_rows_ptr = new_rows;
    *current_cols_ptr = new_cols;
}
void free_matrix(int*** matrix_ptr, int* rows_ptr) {
    if (*matrix_ptr == NULL) return;
    for (int i = 0; i < *rows_ptr; i++) {
        free((*matrix_ptr)[i]);
        (*matrix_ptr)[i] = NULL;
    }
    free(*matrix_ptr);
    *matrix_ptr = NULL;
    *rows_ptr = 0;
}
int main() {
    int** matrix = NULL;
    int rows = 0;
    int cols = 0;
    rows = 3;
    cols = 4;
    matrix = create_matrix(rows, cols);
    if (matrix == NULL) {
        printf("Failed to create matrix.\n");
        return 1;
    }
    printf("Initial matrix created.\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j + 1;
        }
    }
    print_matrix(matrix, rows, cols);
    printf("Resizing matrix to 5x6...\n");
    resize_matrix(&matrix, &rows, &cols, 5, 6);
    if (matrix == NULL && rows != 0) {
        printf("Resize failed or matrix became empty unexpectedly.\n");
        return 1;
    }
    if (rows > 3 && cols > 4) {
        matrix[3][4] = 99;
        matrix[4][5] = 100;
    }
    print_matrix(matrix, rows, cols);
    printf("Resizing matrix to 2x3...\n");
    resize_matrix(&matrix, &rows, &cols, 2, 3);
    if (matrix == NULL && rows != 0) {
        printf("Resize failed or matrix became empty unexpectedly.\n");
        return 1;
    }
    print_matrix(matrix, rows, cols);
    printf("Resizing matrix to 4x2...\n");
    resize_matrix(&matrix, &rows, &cols, 4, 2);
    if (matrix == NULL && rows != 0) {
        printf("Resize failed or matrix became empty unexpectedly.\n");
        return 1;
    }
    print_matrix(matrix, rows, cols);
    printf("Resizing matrix to 0x0 (freeing all memory)...\n");
    resize_matrix(&matrix, &rows, &cols, 0, 0);
    print_matrix(matrix, rows, cols);
    printf("Attempting to resize a NULL matrix to 2x2...\n");
    resize_matrix(&matrix, &rows, &cols, 2, 2);
    if (matrix != NULL) {
        printf("NULL matrix successfully resized to 2x2.\n");
        print_matrix(matrix, rows, cols);
    } else {
        printf("Failed to resize NULL matrix to 2x2 (expected behavior if initial create_matrix is preferred).");
        printf(" Current implementation tries to realloc NULL which acts like malloc.\n");
    }
    free_matrix(&matrix, &rows);
    return 0;
}