#include <stdio.h>
#include <stdlib.h>
void print_matrix(int **matrix, int rows, int cols, const char *name) {
    printf("\n--- %s (%dx%d) ---\n", name, rows, cols);
    if (matrix == NULL) {
        printf("Matrix is NULL.\n");
        return;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}
int*** create_matrix_pool(int *initial_capacity_ptr, int *pool_count_ptr, int **pool_rows_ptr, int **pool_cols_ptr) {
    *initial_capacity_ptr = 4;
    *pool_count_ptr = 0;
    int*** pool = (int***)malloc(*initial_capacity_ptr * sizeof(int**));
    if (pool == NULL) { return NULL; }
    *pool_rows_ptr = (int*)malloc(*initial_capacity_ptr * sizeof(int));
    if (*pool_rows_ptr == NULL) { free(pool); return NULL; }
    *pool_cols_ptr = (int*)malloc(*initial_capacity_ptr * sizeof(int));
    if (*pool_cols_ptr == NULL) { free(pool); free(*pool_rows_ptr); return NULL; }
    return pool;
}
void add_matrix(int*** pool_ptr, int *pool_capacity_ptr, int *pool_count_ptr, int **pool_rows_ptr, int **pool_cols_ptr, int rows, int cols) {
    if (rows <= 0 || cols <= 0) { return; }
    if (*pool_count_ptr == *pool_capacity_ptr) {
        *pool_capacity_ptr *= 2;
        int*** temp_pool = (int***)realloc(*pool_ptr, *pool_capacity_ptr * sizeof(int**));
        if (temp_pool == NULL) { return; }
        *pool_ptr = temp_pool;
        int* temp_rows = (int*)realloc(*pool_rows_ptr, *pool_capacity_ptr * sizeof(int));
        if (temp_rows == NULL) { return; }
        *pool_rows_ptr = temp_rows;
        int* temp_cols = (int*)realloc(*pool_cols_ptr, *pool_capacity_ptr * sizeof(int));
        if (temp_cols == NULL) { return; }
        *pool_cols_ptr = temp_cols;
    }
    int **new_matrix = (int**)malloc(rows * sizeof(int*));
    if (new_matrix == NULL) { return; }
    for (int i = 0; i < rows; i++) {
        new_matrix[i] = (int*)malloc(cols * sizeof(int));
        if (new_matrix[i] == NULL) {
            for (int k = 0; k < i; k++) { free(new_matrix[k]); }
            free(new_matrix);
            return;
        }
        for (int j = 0; j < cols; j++) {
            new_matrix[i][j] = (*pool_count_ptr + 1) * 100 + i * 10 + j + 1;
        }
    }
    (*pool_ptr)[*pool_count_ptr] = new_matrix;
    (*pool_rows_ptr)[*pool_count_ptr] = rows;
    (*pool_cols_ptr)[*pool_count_ptr] = cols;
    (*pool_count_ptr)++;
}
void remove_matrix(int*** pool_ptr, int *pool_capacity_ptr, int *pool_count_ptr, int **pool_rows_ptr, int **pool_cols_ptr, int index) {
    if (index < 0 || index >= *pool_count_ptr) { return; }
    int rows_to_free = (*pool_rows_ptr)[index];
    int **matrix_to_free = (*pool_ptr)[index];
    for (int i = 0; i < rows_to_free; i++) {
        free(matrix_to_free[i]);
    }
    free(matrix_to_free);
    for (int i = index; i < *pool_count_ptr - 1; i++) {
        (*pool_ptr)[i] = (*pool_ptr)[i+1];
        (*pool_rows_ptr)[i] = (*pool_rows_ptr)[i+1];
        (*pool_cols_ptr)[i] = (*pool_cols_ptr)[i+1];
    }
    (*pool_count_ptr)--;
    if (*pool_count_ptr > 0 && *pool_count_ptr < *pool_capacity_ptr / 4) {
        *pool_capacity_ptr /= 2;
        int*** temp_pool = (int***)realloc(*pool_ptr, *pool_capacity_ptr * sizeof(int**));
        if (temp_pool != NULL) { *pool_ptr = temp_pool; }
        int* temp_rows = (int*)realloc(*pool_rows_ptr, *pool_capacity_ptr * sizeof(int));
        if (temp_rows != NULL) { *pool_rows_ptr = temp_rows; }
        int* temp_cols = (int*)realloc(*pool_cols_ptr, *pool_capacity_ptr * sizeof(int));
        if (temp_cols != NULL) { *pool_cols_ptr = temp_cols; }
    } else if (*pool_count_ptr == 0) {
        free(*pool_ptr); *pool_ptr = NULL;
        free(*pool_rows_ptr); *pool_rows_ptr = NULL;
        free(*pool_cols_ptr); *pool_cols_ptr = NULL;
        *pool_capacity_ptr = 0;
    }
}
int** consolidate_matrices(int*** pool_ptr, int *pool_capacity_ptr, int *pool_count_ptr, int **pool_rows_ptr, int **pool_cols_ptr, int *total_rows_ptr, int *total_cols_ptr) {
    if (*pool_count_ptr == 0) {
        *total_rows_ptr = 0;
        *total_cols_ptr = 0;
        return NULL;
    }
    int sum_rows = 0;
    int max_cols = 0;
    for (int i = 0; i < *pool_count_ptr; i++) {
        sum_rows += (*pool_rows_ptr)[i];
        if ((*pool_cols_ptr)[i] > max_cols) {
            max_cols = (*pool_cols_ptr)[i];
        }
    }
    *total_rows_ptr = sum_rows;
    *total_cols_ptr = max_cols;
    int **consolidated_matrix = (int**)malloc(sum_rows * sizeof(int*));
    if (consolidated_matrix == NULL) { return NULL; }
    for (int i = 0; i < sum_rows; i++) {
        consolidated_matrix[i] = (int*)calloc(max_cols, sizeof(int));
        if (consolidated_matrix[i] == NULL) {
            for (int k = 0; k < i; k++) { free(consolidated_matrix[k]); }
            free(consolidated_matrix);
            return NULL;
        }
    }
    int current_row_offset = 0;
    for (int k = 0; k < *pool_count_ptr; k++) {
        int **current_matrix = (*pool_ptr)[k];
        int current_rows = (*pool_rows_ptr)[k];
        int current_cols = (*pool_cols_ptr)[k];
        for (int r = 0; r < current_rows; r++) {
            for (int c = 0; c < current_cols; c++) {
                consolidated_matrix[current_row_offset + r][c] = current_matrix[r][c];
            }
        }
        current_row_offset += current_rows;
        for (int r = 0; r < current_rows; r++) {
            free(current_matrix[r]);
        }
        free(current_matrix);
    }
    free(*pool_ptr); *pool_ptr = NULL;
    free(*pool_rows_ptr); *pool_rows_ptr = NULL;
    free(*pool_cols_ptr); *pool_cols_ptr = NULL;
    *pool_count_ptr = 0;
    *pool_capacity_ptr = 0;
    return consolidated_matrix;
}
void free_matrix(int **matrix, int rows) {
    if (matrix == NULL) { return; }
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
int main() {
    int pool_capacity = 0;
    int pool_count = 0;
    int *matrix_rows = NULL;
    int *matrix_cols = NULL;
    int ***matrix_pool = create_matrix_pool(&pool_capacity, &pool_count, &matrix_rows, &matrix_cols);
    if (matrix_pool == NULL) { printf("Failed to create matrix pool.\n"); return 1; }
    add_matrix(&matrix_pool, &pool_capacity, &pool_count, &matrix_rows, &matrix_cols, 2, 3);
    add_matrix(&matrix_pool, &pool_capacity, &pool_count, &matrix_rows, &matrix_cols, 3, 2);
    add_matrix(&matrix_pool, &pool_capacity, &pool_count, &matrix_rows, &matrix_cols, 4, 4);
    add_matrix(&matrix_pool, &pool_capacity, &pool_count, &matrix_rows, &matrix_cols, 1, 5);
    printf("Initial Pool Status: %d matrices, Capacity: %d\n", pool_count, pool_capacity);
    for (int i = 0; i < pool_count; i++) {
        print_matrix(matrix_pool[i], matrix_rows[i], matrix_cols[i], "Matrix in Pool");
    }
    printf("\nRemoving matrix at index 1...\n");
    remove_matrix(&matrix_pool, &pool_capacity, &pool_count, &matrix_rows, &matrix_cols, 1);
    printf("Pool Status after removal: %d matrices, Capacity: %d\n", pool_count, pool_capacity);
    for (int i = 0; i < pool_count; i++) {
        print_matrix(matrix_pool[i], matrix_rows[i], matrix_cols[i], "Matrix in Pool after removal");
    }
    add_matrix(&matrix_pool, &pool_capacity, &pool_count, &matrix_rows, &matrix_cols, 2, 6);
    printf("\nPool Status after adding another: %d matrices, Capacity: %d\n", pool_count, pool_capacity);
    for (int i = 0; i < pool_count; i++) {
        print_matrix(matrix_pool[i], matrix_rows[i], matrix_cols[i], "Matrix in Pool after re-add");
    }
    printf("\nConsolidating all matrices...\n");
    int consolidated_total_rows = 0;
    int consolidated_total_cols = 0;
    int **consolidated = consolidate_matrices(&matrix_pool, &pool_capacity, &pool_count, &matrix_rows, &matrix_cols, &consolidated_total_rows, &consolidated_total_cols);
    if (consolidated != NULL) {
        print_matrix(consolidated, consolidated_total_rows, consolidated_total_cols, "Consolidated Matrix");
        free_matrix(consolidated, consolidated_total_rows);
    } else {
        printf("Consolidation resulted in a NULL matrix.\n");
    }
    printf("\nFinal Pool Status: %d matrices, Capacity: %d\n", pool_count, pool_capacity);
    if (matrix_pool == NULL && matrix_rows == NULL && matrix_cols == NULL) {
        printf("Matrix pool and dimension arrays successfully freed.\n");
    } else {
        printf("Memory leak or incorrect freeing detected for pool/dimension arrays.\n");
        if (matrix_pool != NULL) { free(matrix_pool); }
        if (matrix_rows != NULL) { free(matrix_rows); }
        if (matrix_cols != NULL) { free(matrix_cols); }
    }
    return 0;
}