#include <stdio.h>
#include <stdlib.h>
int create_matrix(int*** matrix_ptr, int initial_rows, int initial_cols) {
    int i, j;
    *matrix_ptr = (int**)malloc(initial_rows * sizeof(int*));
    if (*matrix_ptr == NULL) return 0;
    for (i = 0; i < initial_rows; i++) {
        (*matrix_ptr)[i] = (int*)malloc(initial_cols * sizeof(int));
        if ((*matrix_ptr)[i] == NULL) {
            for (j = 0; j < i; j++) free((*matrix_ptr)[j]);
            free(*matrix_ptr);
            *matrix_ptr = NULL;
            return 0;
        }
        for (j = 0; j < initial_cols; j++) {
            (*matrix_ptr)[i][j] = 0;
        }
    }
    return 1;
}
void print_matrix(int** matrix, int rows, int cols) {
    int i, j;
    if (matrix == NULL || rows == 0 || cols == 0) {
        printf("Matrix is empty or invalid.\n");
        return;
    }
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("--------------------\n");
}
void free_matrix(int*** matrix_ptr, int rows) {
    int i;
    if (*matrix_ptr == NULL) return;
    for (i = 0; i < rows; i++) {
        free((*matrix_ptr)[i]);
    }
    free(*matrix_ptr);
    *matrix_ptr = NULL;
}
int add_row(int*** matrix_ptr, int* rows_ptr, int cols, int* new_row_data) {
    int i;
    int** temp_matrix;
    if (cols == 0) {
        printf("Cannot add row to matrix with 0 columns.\n");
        return 0;
    }
    temp_matrix = (int**)realloc(*matrix_ptr, (*rows_ptr + 1) * sizeof(int*));
    if (temp_matrix == NULL) return 0;
    *matrix_ptr = temp_matrix;
    (*matrix_ptr)[*rows_ptr] = (int*)malloc(cols * sizeof(int));
    if ((*matrix_ptr)[*rows_ptr] == NULL) {
        printf("Malloc for new row failed.\n");
        return 0;
    }
    if (new_row_data != NULL) {
        for (i = 0; i < cols; i++) {
            (*matrix_ptr)[*rows_ptr][i] = new_row_data[i];
        }
    } else {
        for (i = 0; i < cols; i++) {
            (*matrix_ptr)[*rows_ptr][i] = 0;
        }
    }
    (*rows_ptr)++;
    return 1;
}
int remove_row(int*** matrix_ptr, int* rows_ptr, int cols, int row_index) {
    int i;
    int** temp_matrix;
    if (*rows_ptr == 0 || row_index < 0 || row_index >= *rows_ptr) {
        printf("Invalid row index or empty matrix for removal.\n");
        return 0;
    }
    free((*matrix_ptr)[row_index]);
    for (i = row_index; i < *rows_ptr - 1; i++) {
        (*matrix_ptr)[i] = (*matrix_ptr)[i + 1];
    }
    if (*rows_ptr - 1 == 0) {
        free(*matrix_ptr);
        *matrix_ptr = NULL;
    } else {
        temp_matrix = (int**)realloc(*matrix_ptr, (*rows_ptr - 1) * sizeof(int*));
        if (temp_matrix == NULL) {
            printf("Realloc during row removal failed.\n");
            return 0;
        }
        *matrix_ptr = temp_matrix;
    }
    (*rows_ptr)--;
    return 1;
}
int add_column(int*** matrix_ptr, int* rows_ptr, int* cols_ptr, int col_index, int default_val) {
    int i, j;
    int* temp_row;
    if (col_index < 0 || col_index > *cols_ptr) {
        printf("Invalid column index for addition.\n");
        return 0;
    }
    if (*rows_ptr == 0) {
        printf("Matrix has no rows, cannot add a column directly.\n");
        return 0;
    }
    for (i = 0; i < *rows_ptr; i++) {
        temp_row = (int*)realloc((*matrix_ptr)[i], (*cols_ptr + 1) * sizeof(int));
        if (temp_row == NULL) {
            printf("Realloc failed for row %d during column addition.\n", i);
            return 0;
        }
        (*matrix_ptr)[i] = temp_row;
        for (j = *cols_ptr; j > col_index; j--) {
            (*matrix_ptr)[i][j] = (*matrix_ptr)[i][j - 1];
        }
        (*matrix_ptr)[i][col_index] = default_val;
    }
    (*cols_ptr)++;
    return 1;
}
int remove_column(int*** matrix_ptr, int* rows_ptr, int* cols_ptr, int col_index) {
    int i, j;
    int* temp_row;
    if (*cols_ptr == 0 || col_index < 0 || col_index >= *cols_ptr) {
        printf("Invalid column index or empty matrix for removal.\n");
        return 0;
    }
    for (i = 0; i < *rows_ptr; i++) {
        for (j = col_index; j < *cols_ptr - 1; j++) {
            (*matrix_ptr)[i][j] = (*matrix_ptr)[i][j + 1];
        }
        if (*cols_ptr - 1 == 0) {
            free((*matrix_ptr)[i]);
            (*matrix_ptr)[i] = NULL;
        } else {
            temp_row = (int*)realloc((*matrix_ptr)[i], (*cols_ptr - 1) * sizeof(int));
            if (temp_row == NULL) {
                printf("Realloc failed for row %d during column removal.\n", i);
                return 0; 
            }
            (*matrix_ptr)[i] = temp_row;
        }
    }
    (*cols_ptr)--;
    return 1;
}
int main() {
    int** my_matrix = NULL;
    int current_rows = 0;
    int current_cols = 0;
    int initial_data[] = {1, 2, 3};
    int another_row_data[] = {10, 20, 30};
    int third_row_data[] = {100, 200, 300};
    current_rows = 3;
    current_cols = 3;
    if (!create_matrix(&my_matrix, current_rows, current_cols)) {
        printf("Failed to create matrix.\n");
        return 1;
    }
    my_matrix[0][0] = 1; my_matrix[0][1] = 2; my_matrix[0][2] = 3;
    my_matrix[1][0] = 4; my_matrix[1][1] = 5; my_matrix[1][2] = 6;
    my_matrix[2][0] = 7; my_matrix[2][1] = 8; my_matrix[2][2] = 9;
    printf("Initial Matrix:\n");
    print_matrix(my_matrix, current_rows, current_cols);
    printf("Adding a new row (10, 20, 30):\n");
    if (add_row(&my_matrix, &current_rows, current_cols, another_row_data)) {
        print_matrix(my_matrix, current_rows, current_cols);
    } else {
        printf("Failed to add row.\n");
    }
    printf("Adding another row (100, 200, 300):\n");
    if (add_row(&my_matrix, &current_rows, current_cols, third_row_data)) {
        print_matrix(my_matrix, current_rows, current_cols);
    } else {
        printf("Failed to add row.\n");
    }
    printf("Removing row at index 1:\n");
    if (remove_row(&my_matrix, &current_rows, current_cols, 1)) {
        print_matrix(my_matrix, current_rows, current_cols);
    } else {
        printf("Failed to remove row.\n");
    }
    printf("Adding a column at index 1 with value 99:\n");
    if (add_column(&my_matrix, &current_rows, &current_cols, 1, 99)) {
        print_matrix(my_matrix, current_rows, current_cols);
    } else {
        printf("Failed to add column.\n");
    }
    printf("Removing column at index 0:\n");
    if (remove_column(&my_matrix, &current_rows, &current_cols, 0)) {
        print_matrix(my_matrix, current_rows, current_cols);
    } else {
        printf("Failed to remove column.\n");
    }
    printf("Adding a column at the end with value 111:\n");
    if (add_column(&my_matrix, &current_rows, &current_cols, current_cols, 111)) {
        print_matrix(my_matrix, current_rows, current_cols);
    } else {
        printf("Failed to add column.\n");
    }
    printf("Removing the last column (index %d):\n", current_cols - 1);
    if (remove_column(&my_matrix, &current_rows, &current_cols, current_cols - 1)) {
        print_matrix(my_matrix, current_rows, current_cols);
    } else {
        printf("Failed to remove column.\n");
    }
    printf("Freeing matrix memory.\n");
    free_matrix(&my_matrix, current_rows);
    if (my_matrix == NULL) {
        printf("Matrix memory successfully freed and pointer nulled.\n");
    } else {
        printf("Matrix pointer was not nulled, possible issue.\n");
    }
    return 0;
}