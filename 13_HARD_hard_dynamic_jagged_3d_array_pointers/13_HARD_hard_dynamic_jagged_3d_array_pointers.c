#include <stdio.h>
#include <stdlib.h>
#include <time.h>
long long calculateSumOfJaggedArray(int **jagged_array, int num_rows, int *cols_per_row) {
    long long total_sum = 0;
    if (jagged_array == NULL) {
        return 0;
    }
    for (int r = 0; r < num_rows; r++) {
        if (jagged_array[r] == NULL) {
            continue;
        }
        for (int c = 0; c < cols_per_row[r]; c++) {
            total_sum += jagged_array[r][c];
        }
    }
    return total_sum;
}
int main() {
    srand(time(NULL));
    int num_top_collections = 3 + rand() % 3;
    int ***collection_of_jagged_arrays;
    int *jagged_array_row_counts;
    int **jagged_array_col_counts;
    collection_of_jagged_arrays = (int ***)malloc(num_top_collections * sizeof(int **));
    if (collection_of_jagged_arrays == NULL) {
        return 1;
    }
    jagged_array_row_counts = (int *)malloc(num_top_collections * sizeof(int));
    if (jagged_array_row_counts == NULL) {
        free(collection_of_jagged_arrays);
        return 1;
    }
    jagged_array_col_counts = (int **)malloc(num_top_collections * sizeof(int *));
    if (jagged_array_col_counts == NULL) {
        free(collection_of_jagged_arrays);
        free(jagged_array_row_counts);
        return 1;
    }
    for (int i = 0; i < num_top_collections; i++) {
        int num_rows_in_current_jagged_array = 2 + rand() % 4;
        jagged_array_row_counts[i] = num_rows_in_current_jagged_array;
        collection_of_jagged_arrays[i] = (int **)malloc(num_rows_in_current_jagged_array * sizeof(int *));
        if (collection_of_jagged_arrays[i] == NULL) {
            return 1;
        }
        jagged_array_col_counts[i] = (int *)malloc(num_rows_in_current_jagged_array * sizeof(int));
        if (jagged_array_col_counts[i] == NULL) {
            return 1;
        }
        for (int j = 0; j < num_rows_in_current_jagged_array; j++) {
            int num_cols_in_current_row = 3 + rand() % 5;
            jagged_array_col_counts[i][j] = num_cols_in_current_row;
            collection_of_jagged_arrays[i][j] = (int *)malloc(num_cols_in_current_row * sizeof(int));
            if (collection_of_jagged_arrays[i][j] == NULL) {
                return 1;
            }
            for (int k = 0; k < num_cols_in_current_row; k++) {
                collection_of_jagged_arrays[i][j][k] = (i * 100 + j * 10 + k) + rand() % 10;
            }
        }
    }
    printf("--- Dynamically Allocated 3D Jagged Structure ---\n");
    for (int i = 0; i < num_top_collections; i++) {
        printf("\nJagged Array %d:\n", i);
        long long current_jagged_sum = calculateSumOfJaggedArray(
            collection_of_jagged_arrays[i],
            jagged_array_row_counts[i],
            jagged_array_col_counts[i]
        );
        for (int j = 0; j < jagged_array_row_counts[i]; j++) {
            printf("  Row %d (%d elements): ", j, jagged_array_col_counts[i][j]);
            for (int k = 0; k < jagged_array_col_counts[i][j]; k++) {
                printf("%d ", collection_of_jagged_arrays[i][j][k]);
            }
            printf("\n");
        }
        printf("  Sum of elements in Jagged Array %d: %lld\n", i, current_jagged_sum);
    }
    printf("\n-------------------------------------------------\n");
    for (int i = 0; i < num_top_collections; i++) {
        for (int j = 0; j < jagged_array_row_counts[i]; j++) {
            free(collection_of_jagged_arrays[i][j]);
        }
        free(collection_of_jagged_arrays[i]);
        free(jagged_array_col_counts[i]);
    }
    free(collection_of_jagged_arrays);
    free(jagged_array_row_counts);
    free(jagged_array_col_counts);
    return 0;
}