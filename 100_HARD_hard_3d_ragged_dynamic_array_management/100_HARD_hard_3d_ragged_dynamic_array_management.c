#include <stdio.h>
#include <stdlib.h>
int main() {
    int num_slabs = 3;
    int **slab_dimensions_storage = (int **)malloc(num_slabs * sizeof(int *));
    int ***data_cube = (int ***)malloc(num_slabs * sizeof(int **));
    int initial_rows_per_slab[] = {2, 4, 3};
    int initial_cols_slab0[] = {5, 2};
    int initial_cols_slab1[] = {3, 6, 1, 4};
    int initial_cols_slab2[] = {7, 2, 5};
    int *initial_cols_per_row_in_slab[] = {initial_cols_slab0, initial_cols_slab1, initial_cols_slab2};
    for (int i = 0; i < num_slabs; i++) {
        int current_slab_rows = initial_rows_per_slab[i];
        slab_dimensions_storage[i] = (int *)malloc(current_slab_rows * sizeof(int));
        data_cube[i] = (int **)malloc(current_slab_rows * sizeof(int *));
        for (int j = 0; j < current_slab_rows; j++) {
            int current_row_cols = initial_cols_per_row_in_slab[i][j];
            slab_dimensions_storage[i][j] = current_row_cols;
            data_cube[i][j] = (int *)malloc(current_row_cols * sizeof(int));
            for (int k = 0; k < current_row_cols; k++) {
                data_cube[i][j][k] = i * 100 + j * 10 + k;
            }
        }
    }
    long long total_sum = 0;
    for (int i = 0; i < num_slabs; i++) {
        int current_slab_rows = initial_rows_per_slab[i];
        for (int j = 0; j < current_slab_rows; j++) {
            int current_row_cols = slab_dimensions_storage[i][j];
            for (int k = 0; k < current_row_cols; k++) {
                total_sum += data_cube[i][j][k];
            }
        }
    }
    printf("Total sum of elements: %lld\n", total_sum);
    for (int i = 0; i < num_slabs; i++) {
        int current_slab_rows = initial_rows_per_slab[i];
        for (int j = 0; j < current_slab_rows; j++) {
            free(data_cube[i][j]);
        }
        free(data_cube[i]);
        free(slab_dimensions_storage[i]);
    }
    free(data_cube);
    free(slab_dimensions_storage);
    return 0;
}