#include <stdio.h>
#include <stdlib.h>
void insertColumn(int** matrix, int* row_lengths, int num_rows, int col_index_to_insert, int default_value) {
    for (int i = 0; i < num_rows; i++) {
        int current_row_len = row_lengths[i];
        int* new_row = (int*)realloc(matrix[i], (current_row_len + 1) * sizeof(int));
        if (new_row == NULL) {
            fprintf(stderr, "Memory reallocation failed for row %d\n", i);
            exit(EXIT_FAILURE);
        }
        matrix[i] = new_row;
        for (int j = current_row_len; j > col_index_to_insert; j--) {
            matrix[i][j] = matrix[i][j - 1];
        }
        matrix[i][col_index_to_insert] = default_value;
        row_lengths[i]++;
    }
}
void printMatrix(int** matrix, int* row_lengths, int num_rows) {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < row_lengths[i]; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
int main() {
    int num_rows = 3;
    int* row_lengths = (int*)malloc(num_rows * sizeof(int));
    if (row_lengths == NULL) {
        fprintf(stderr, "Memory allocation failed for row_lengths\n");
        return EXIT_FAILURE;
    }
    int** matrix = (int**)malloc(num_rows * sizeof(int*));
    if (matrix == NULL) {
        fprintf(stderr, "Memory allocation failed for matrix\n");
        free(row_lengths);
        return EXIT_FAILURE;
    }
    row_lengths[0] = 3;
    matrix[0] = (int*)malloc(row_lengths[0] * sizeof(int));
    if (matrix[0] == NULL) {
        fprintf(stderr, "Memory allocation failed for matrix[0]\n");
        free(row_lengths);
        free(matrix);
        return EXIT_FAILURE;
    }
    matrix[0][0] = 1; matrix[0][1] = 2; matrix[0][2] = 3;
    row_lengths[1] = 2;
    matrix[1] = (int*)malloc(row_lengths[1] * sizeof(int));
    if (matrix[1] == NULL) {
        fprintf(stderr, "Memory allocation failed for matrix[1]\n");
        free(matrix[0]);
        free(row_lengths);
        free(matrix);
        return EXIT_FAILURE;
    }
    matrix[1][0] = 4; matrix[1][1] = 5;
    row_lengths[2] = 4;
    matrix[2] = (int*)malloc(row_lengths[2] * sizeof(int));
    if (matrix[2] == NULL) {
        fprintf(stderr, "Memory allocation failed for matrix[2]\n");
        free(matrix[0]);
        free(matrix[1]);
        free(row_lengths);
        free(matrix);
        return EXIT_FAILURE;
    }
    matrix[2][0] = 6; matrix[2][1] = 7; matrix[2][2] = 8; matrix[2][3] = 9;
    printf("Original Matrix:\n");
    printMatrix(matrix, row_lengths, num_rows);
    printf("\n");
    int col_to_insert = 1;
    int default_val = 99;
    printf("Inserting column at index %d with value %d:\n", col_to_insert, default_val);
    insertColumn(matrix, row_lengths, num_rows, col_to_insert, default_val);
    printf("Matrix after insertion:\n");
    printMatrix(matrix, row_lengths, num_rows);
    printf("\n");
    col_to_insert = 5;
    default_val = 111;
    printf("Inserting column at index %d with value %d:\n", col_to_insert, default_val);
    insertColumn(matrix, row_lengths, num_rows, col_to_insert, default_val);
    printf("Matrix after second insertion:\n");
    printMatrix(matrix, row_lengths, num_rows);
    printf("\n");
    for (int i = 0; i < num_rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(row_lengths);
    return EXIT_SUCCESS;
}