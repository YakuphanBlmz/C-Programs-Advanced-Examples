#include <stdio.h>
#include <stdlib.h>
int main() {
    int num_rows = 5;
    int **jagged_array;
    jagged_array = (int **)malloc(num_rows * sizeof(int *));
    if (jagged_array == NULL) {
        return 1;
    }
    int initial_col_sizes[] = {3, 5, 2, 6, 4};
    for (int i = 0; i < num_rows; i++) {
        int current_cols = initial_col_sizes[i];
        jagged_array[i] = (int *)malloc(current_cols * sizeof(int));
        if (jagged_array[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(jagged_array[j]);
            }
            free(jagged_array);
            return 1;
        }
        for (int j = 0; j < current_cols; j++) {
            jagged_array[i][j] = (i + 1) * 10 + j;
        }
    }
    printf("Initial Jagged Array:\n");
    for (int i = 0; i < num_rows; i++) {
        printf("Row %d (size %d): ", i, initial_col_sizes[i]);
        for (int j = 0; j < initial_col_sizes[i]; j++) {
            printf("%d ", jagged_array[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    int row_to_reallocate = 2;
    int new_col_size = 7;
    printf("Reallocating Row %d from size %d to size %d...\n", row_to_reallocate, initial_col_sizes[row_to_reallocate], new_col_size);
    int *temp_row_ptr = (int *)realloc(jagged_array[row_to_reallocate], new_col_size * sizeof(int));
    if (temp_row_ptr == NULL) {
        printf("Reallocation failed for Row %d. Original row remains intact.\n", row_to_reallocate);
        for (int i = 0; i < num_rows; i++) {
            free(jagged_array[i]);
        }
        free(jagged_array);
        return 1;
    } else {
        jagged_array[row_to_reallocate] = temp_row_ptr;
        if (new_col_size > initial_col_sizes[row_to_reallocate]) {
            for (int j = initial_col_sizes[row_to_reallocate]; j < new_col_size; j++) {
                jagged_array[row_to_reallocate][j] = (row_to_reallocate + 1) * 100 + j;
            }
        }
        initial_col_sizes[row_to_reallocate] = new_col_size;
    }
    printf("\nJagged Array After Reallocation:\n");
    for (int i = 0; i < num_rows; i++) {
        printf("Row %d (size %d): ", i, initial_col_sizes[i]);
        for (int j = 0; j < initial_col_sizes[i]; j++) {
            printf("%d ", jagged_array[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < num_rows; i++) {
        free(jagged_array[i]);
    }
    free(jagged_array);
    return 0;
}