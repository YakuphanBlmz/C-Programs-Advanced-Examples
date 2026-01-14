#include <stdio.h>
#include <stdlib.h>
void add_dynamic_row(int ***collection_ptr, int **row_sizes_ptr, int *num_rows_ptr, int *capacity_rows_ptr, int initial_col_size);
void resize_dynamic_row(int ***collection_ptr, int **row_sizes_ptr, int row_index, int new_col_size, int num_rows_current);
void remove_dynamic_row(int ***collection_ptr, int **row_sizes_ptr, int *num_rows_ptr, int *capacity_rows_ptr, int row_index_to_remove);
void print_dynamic_collection(int **collection, int num_rows, int *row_sizes);
void free_dynamic_collection(int ***collection_ptr, int **row_sizes_ptr, int *num_rows_ptr, int *capacity_rows_ptr);
int main() {
    int **collection_of_arrays = NULL;
    int *row_sizes = NULL;
    int num_rows = 0;
    int capacity_rows = 0;
    add_dynamic_row(&collection_of_arrays, &row_sizes, &num_rows, &capacity_rows, 5);
    add_dynamic_row(&collection_of_arrays, &row_sizes, &num_rows, &capacity_rows, 3);
    add_dynamic_row(&collection_of_arrays, &row_sizes, &num_rows, &capacity_rows, 7);
    printf("-- Initial Collection ---\n");
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < row_sizes[i]; j++) {
            collection_of_arrays[i][j] = (i + 1) * 10 + j;
        }
    }
    print_dynamic_collection(collection_of_arrays, num_rows, row_sizes);
    printf("\n-- Resizing Row 1 to 6 elements ---\n");
    resize_dynamic_row(&collection_of_arrays, &row_sizes, 1, 6, num_rows);
    for (int j = 3; j < row_sizes[1]; j++) {
        collection_of_arrays[1][j] = 200 + j;
    }
    print_dynamic_collection(collection_of_arrays, num_rows, row_sizes);
    printf("\n-- Adding a new row (Row 3) with 4 elements ---\n");
    add_dynamic_row(&collection_of_arrays, &row_sizes, &num_rows, &capacity_rows, 4);
    for (int j = 0; j < row_sizes[3]; j++) {
        collection_of_arrays[3][j] = 400 + j;
    }
    print_dynamic_collection(collection_of_arrays, num_rows, row_sizes);
    printf("\n-- Removing Row 0 ---\n");
    remove_dynamic_row(&collection_of_arrays, &row_sizes, &num_rows, &capacity_rows, 0);
    print_dynamic_collection(collection_of_arrays, num_rows, row_sizes);
    printf("\n-- Adding another row (new Row 3) with 2 elements ---\n");
    add_dynamic_row(&collection_of_arrays, &row_sizes, &num_rows, &capacity_rows, 2);
    for (int j = 0; j < row_sizes[num_rows - 1]; j++) {
        collection_of_arrays[num_rows - 1][j] = 500 + j;
    }
    print_dynamic_collection(collection_of_arrays, num_rows, row_sizes);
    free_dynamic_collection(&collection_of_arrays, &row_sizes, &num_rows, &capacity_rows);
    printf("\n-- After Freeing Memory ---\n");
    if (collection_of_arrays == NULL && row_sizes == NULL && num_rows == 0 && capacity_rows == 0) {
        printf("All memory freed successfully. Collection is empty.\n");
    } else {
        printf("Memory freeing issue detected.\n");
    }
    return 0;
}
void add_dynamic_row(int ***collection_ptr, int **row_sizes_ptr, int *num_rows_ptr, int *capacity_rows_ptr, int initial_col_size) {
    if (*num_rows_ptr >= *capacity_rows_ptr) {
        int new_capacity = (*capacity_rows_ptr == 0) ? 2 : (*capacity_rows_ptr * 2);
        int **temp_collection = (int **)realloc(*collection_ptr, new_capacity * sizeof(int *));
        if (temp_collection == NULL) {
            fprintf(stderr, "Failed to reallocate collection_of_arrays.\n");
            exit(EXIT_FAILURE);
        }
        *collection_ptr = temp_collection;
        int *temp_sizes = (int *)realloc(*row_sizes_ptr, new_capacity * sizeof(int));
        if (temp_sizes == NULL) {
            fprintf(stderr, "Failed to reallocate row_sizes.\n");
            exit(EXIT_FAILURE);
        }
        *row_sizes_ptr = temp_sizes;
        *capacity_rows_ptr = new_capacity;
    }
    (*collection_ptr)[*num_rows_ptr] = (int *)malloc(initial_col_size * sizeof(int));
    if ((*collection_ptr)[*num_rows_ptr] == NULL) {
        fprintf(stderr, "Failed to allocate new row.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < initial_col_size; i++) { (*collection_ptr)[*num_rows_ptr][i] = 0; }
    (*row_sizes_ptr)[*num_rows_ptr] = initial_col_size;
    (*num_rows_ptr)++;
}
void resize_dynamic_row(int ***collection_ptr, int **row_sizes_ptr, int row_index, int new_col_size, int num_rows_current) {
    if (collection_ptr == NULL || *collection_ptr == NULL || row_sizes_ptr == NULL || *row_sizes_ptr == NULL) {
        fprintf(stderr, "Collection or row_sizes not initialized for resize.\n");
        exit(EXIT_FAILURE);
    }
    if (row_index < 0 || row_index >= num_rows_current) {
        fprintf(stderr, "Invalid row index for resize.\n");
        exit(EXIT_FAILURE);
    }
    if (new_col_size < 0) {
        fprintf(stderr, "New column size cannot be negative.\n");
        exit(EXIT_FAILURE);
    }
    int *temp_row = (int *)realloc((*collection_ptr)[row_index], new_col_size * sizeof(int));
    if (temp_row == NULL && new_col_size > 0) {
        fprintf(stderr, "Failed to reallocate row %d.\n", row_index);
        exit(EXIT_FAILURE);
    }
    (*collection_ptr)[row_index] = temp_row;
    (*row_sizes_ptr)[row_index] = new_col_size;
}
void remove_dynamic_row(int ***collection_ptr, int **row_sizes_ptr, int *num_rows_ptr, int *capacity_rows_ptr, int row_index_to_remove) {
    if (collection_ptr == NULL || *collection_ptr == NULL || row_sizes_ptr == NULL || *row_sizes_ptr == NULL || *num_rows_ptr == 0) {
        fprintf(stderr, "Collection is empty or not initialized for remove.\n");
        exit(EXIT_FAILURE);
    }
    if (row_index_to_remove < 0 || row_index_to_remove >= *num_rows_ptr) {
        fprintf(stderr, "Invalid row index for remove.\n");
        exit(EXIT_FAILURE);
    }
    free((*collection_ptr)[row_index_to_remove]);
    (*collection_ptr)[row_index_to_remove] = NULL;
    for (int i = row_index_to_remove; i < *num_rows_ptr - 1; i++) {
        (*collection_ptr)[i] = (*collection_ptr)[i + 1];
        (*row_sizes_ptr)[i] = (*row_sizes_ptr)[i + 1];
    }
    (*num_rows_ptr)--;
    if (*num_rows_ptr > 0 && *num_rows_ptr < *capacity_rows_ptr / 2 && *capacity_rows_ptr > 2) {
        int new_capacity = *capacity_rows_ptr / 2;
        int **temp_collection = (int **)realloc(*collection_ptr, new_capacity * sizeof(int *));
        if (temp_collection != NULL) {
            *collection_ptr = temp_collection;
            *capacity_rows_ptr = new_capacity;
        } else {
             fprintf(stderr, "Warning: Failed to shrink collection_of_arrays capacity.\n");
        }
        int *temp_sizes = (int *)realloc(*row_sizes_ptr, new_capacity * sizeof(int));
        if (temp_sizes != NULL) {
            *row_sizes_ptr = temp_sizes;
        } else {
             fprintf(stderr, "Warning: Failed to shrink row_sizes capacity.\n");
        }
    } else if (*num_rows_ptr == 0) {
        free(*collection_ptr);
        *collection_ptr = NULL;
        free(*row_sizes_ptr);
        *row_sizes_ptr = NULL;
        *capacity_rows_ptr = 0;
    }
}
void print_dynamic_collection(int **collection, int num_rows, int *row_sizes) {
    if (collection == NULL || row_sizes == NULL || num_rows == 0) {
        printf("Collection is empty or not initialized.\n");
        return;
    }
    for (int i = 0; i < num_rows; i++) {
        printf("Row %d (size %d): ", i, row_sizes[i]);
        if (collection[i] == NULL && row_sizes[i] > 0) {
             printf("[ALLOCATION FAILED]\n");
             continue;
        }
        for (int j = 0; j < row_sizes[i]; j++) {
            printf("%d ", collection[i][j]);
        }
        printf("\n");
    }
}
void free_dynamic_collection(int ***collection_ptr, int **row_sizes_ptr, int *num_rows_ptr, int *capacity_rows_ptr) {
    if (collection_ptr != NULL && *collection_ptr != NULL) {
        for (int i = 0; i < *num_rows_ptr; i++) {
            free((*collection_ptr)[i]);
            (*collection_ptr)[i] = NULL;
        }
        free(*collection_ptr);
        *collection_ptr = NULL;
    }
    if (row_sizes_ptr != NULL && *row_sizes_ptr != NULL) {
        free(*row_sizes_ptr);
        *row_sizes_ptr = NULL;
    }
    *num_rows_ptr = 0;
    *capacity_rows_ptr = 0;
}