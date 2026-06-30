#include <stdio.h>
#include <stdlib.h>
void transformJaggedArray(int*** new_jagged_array_ptr, int** new_row_sizes_ptr, int* new_row_count_ptr, int** source_jagged_array, int* source_row_sizes, int source_rows, int sum_threshold) {
    int* temp_selected_original_indices = NULL;
    int current_selected_rows = 0;
    int i, j;
    if (source_rows <= 0) {
        *new_jagged_array_ptr = NULL;
        *new_row_sizes_ptr = NULL;
        *new_row_count_ptr = 0;
        return;
    }
    temp_selected_original_indices = (int*)malloc(source_rows * sizeof(int));
    if (temp_selected_original_indices == NULL) {
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < source_rows; i++) {
        int current_sum = 0;
        for (j = 0; j < source_row_sizes[i]; j++) {
            current_sum += source_jagged_array[i][j];
        }
        if (current_sum > sum_threshold) {
            temp_selected_original_indices[current_selected_rows++] = i;
        }
    }
    *new_row_count_ptr = current_selected_rows;
    if (current_selected_rows == 0) {
        free(temp_selected_original_indices);
        *new_jagged_array_ptr = NULL;
        *new_row_sizes_ptr = NULL;
        return;
    }
    *new_jagged_array_ptr = (int**)malloc(current_selected_rows * sizeof(int*));
    if (*new_jagged_array_ptr == NULL) {
        free(temp_selected_original_indices);
        exit(EXIT_FAILURE);
    }
    *new_row_sizes_ptr = (int*)malloc(current_selected_rows * sizeof(int));
    if (*new_row_sizes_ptr == NULL) {
        free(temp_selected_original_indices);
        free(*new_jagged_array_ptr);
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < current_selected_rows; i++) {
        int original_idx = temp_selected_original_indices[i];
        int original_row_len = source_row_sizes[original_idx];
        int even_count = 0;
        int current_even_pos = 0;
        for (j = 0; j < original_row_len; j++) {
            if (source_jagged_array[original_idx][j] % 2 == 0) {
                even_count++;
            }
        }
        (*new_row_sizes_ptr)[i] = even_count;
        if (even_count > 0) {
            (*new_jagged_array_ptr)[i] = (int*)malloc(even_count * sizeof(int));
            if ((*new_jagged_array_ptr)[i] == NULL) {
                for (j = 0; j < i; j++) {
                    free((*new_jagged_array_ptr)[j]);
                }
                free(*new_jagged_array_ptr);
                free(*new_row_sizes_ptr);
                free(temp_selected_original_indices);
                exit(EXIT_FAILURE);
            }
            for (j = 0; j < original_row_len; j++) {
                if (source_jagged_array[original_idx][j] % 2 == 0) {
                    (*new_jagged_array_ptr)[i][current_even_pos++] = source_jagged_array[original_idx][j];
                }
            }
        } else {
            (*new_jagged_array_ptr)[i] = NULL;
        }
    }
    free(temp_selected_original_indices);
}
void printJaggedArray(const char* name, int** arr, int* sizes, int rows) {
    int i, j;
    printf("%s (Rows: %d):\n", name, rows);
    if (arr == NULL || rows == 0) {
        printf("  (Empty)\n");
        return;
    }
    for (i = 0; i < rows; i++) {
        printf("  Row %d (Size: %d): ", i, sizes[i]);
        if (arr[i] == NULL || sizes[i] == 0) {
            printf("(empty row)\n");
            continue;
        }
        for (j = 0; j < sizes[i]; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}
void freeJaggedArray(int*** arr_ptr, int** sizes_ptr, int* rows_ptr) {
    int i;
    if (*arr_ptr == NULL) {
        return;
    }
    for (i = 0; i < *rows_ptr; i++) {
        free((*arr_ptr)[i]);
        (*arr_ptr)[i] = NULL;
    }
    free(*arr_ptr);
    *arr_ptr = NULL;
    free(*sizes_ptr);
    *sizes_ptr = NULL;
    *rows_ptr = 0;
}
int main() {
    int** source_jagged_array = NULL;
    int* source_row_sizes = NULL;
    int source_rows = 5;
    int sum_threshold = 20;
    int** new_jagged_array = NULL;
    int* new_row_sizes = NULL;
    int new_row_count = 0;
    int i, j;
    source_row_sizes = (int*)malloc(source_rows * sizeof(int));
    if (source_row_sizes == NULL) {
        return 1;
    }
    source_jagged_array = (int**)malloc(source_rows * sizeof(int*));
    if (source_jagged_array == NULL) {
        free(source_row_sizes);
        return 1;
    }
    source_row_sizes[0] = 4;
    source_jagged_array[0] = (int*)malloc(4 * sizeof(int));
    if (source_jagged_array[0] == NULL) { free(source_row_sizes); free(source_jagged_array); return 1; }
    source_jagged_array[0][0] = 5; source_jagged_array[0][1] = 10; source_jagged_array[0][2] = 15; source_jagged_array[0][3] = 20; 
    source_row_sizes[1] = 3;
    source_jagged_array[1] = (int*)malloc(3 * sizeof(int));
    if (source_jagged_array[1] == NULL) { free(source_row_sizes); free(source_jagged_array[0]); free(source_jagged_array); return 1; }
    source_jagged_array[1][0] = 2; source_jagged_array[1][1] = 4; source_jagged_array[1][2] = 6; 
    source_row_sizes[2] = 5;
    source_jagged_array[2] = (int*)malloc(5 * sizeof(int));
    if (source_jagged_array[2] == NULL) { free(source_row_sizes); free(source_jagged_array[0]); free(source_jagged_array[1]); free(source_jagged_array); return 1; }
    source_jagged_array[2][0] = 1; source_jagged_array[2][1] = 3; source_jagged_array[2][2] = 5; source_jagged_array[2][3] = 7; source_jagged_array[2][4] = 9;
    source_row_sizes[3] = 2;
    source_jagged_array[3] = (int*)malloc(2 * sizeof(int));
    if (source_jagged_array[3] == NULL) { free(source_row_sizes); free(source_jagged_array[0]); free(source_jagged_array[1]); free(source_jagged_array[2]); free(source_jagged_array); return 1; }
    source_jagged_array[3][0] = 100; source_jagged_array[3][1] = 200; 
    source_row_sizes[4] = 0;
    source_jagged_array[4] = NULL;
    printJaggedArray("Original Jagged Array", source_jagged_array, source_row_sizes, source_rows);
    transformJaggedArray(&new_jagged_array, &new_row_sizes, &new_row_count, 
                         source_jagged_array, source_row_sizes, source_rows, sum_threshold);
    printJaggedArray("Transformed Jagged Array", new_jagged_array, new_row_sizes, new_row_count);
    for (i = 0; i < source_rows; i++) {
        free(source_jagged_array[i]);
    }
    free(source_jagged_array);
    free(source_row_sizes);
    freeJaggedArray(&new_jagged_array, &new_row_sizes, &new_row_count);
    return 0;
}