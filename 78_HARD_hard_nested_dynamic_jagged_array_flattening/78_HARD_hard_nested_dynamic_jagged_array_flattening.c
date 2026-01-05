#include <stdio.h>
#include <stdlib.h>
int main() {
    int N_SUPER_ROWS = 3;
    int MAX_SUB_ROWS_PER_SUPER_ROW_FACTOR = 5;
    int MAX_ELEMENTS_PER_SUB_ROW_FACTOR = 7;
    int ***data = NULL;
    int *sub_rows_sizes = NULL;
    int **elements_sizes_per_sub_row = NULL;
    long long total_elements_count = 0;
    int *flat_array = NULL;
    data = (int ***)malloc(N_SUPER_ROWS * sizeof(int **));
    if (data == NULL) {
        return 1;
    }
    sub_rows_sizes = (int *)malloc(N_SUPER_ROWS * sizeof(int));
    if (sub_rows_sizes == NULL) {
        free(data);
        return 1;
    }
    elements_sizes_per_sub_row = (int **)malloc(N_SUPER_ROWS * sizeof(int *));
    if (elements_sizes_per_sub_row == NULL) {
        free(sub_rows_sizes);
        free(data);
        return 1;
    }
    for (int i = 0; i < N_SUPER_ROWS; i++) {
        int current_sub_rows = (i % MAX_SUB_ROWS_PER_SUPER_ROW_FACTOR) + 1;
        sub_rows_sizes[i] = current_sub_rows;
        data[i] = (int **)malloc(current_sub_rows * sizeof(int *));
        if (data[i] == NULL) {
            for (int x = 0; x < i; x++) {
                int prev_sub_rows = sub_rows_sizes[x];
                for (int y = 0; y < prev_sub_rows; y++) {
                    free(data[x][y]);
                }
                free(data[x]);
                free(elements_sizes_per_sub_row[x]);
            }
            free(elements_sizes_per_sub_row);
            free(sub_rows_sizes);
            free(data);
            return 1;
        }
        elements_sizes_per_sub_row[i] = (int *)malloc(current_sub_rows * sizeof(int));
        if (elements_sizes_per_sub_row[i] == NULL) {
            for (int x = 0; x <= i; x++) {
                int prev_sub_rows_x = sub_rows_sizes[x];
                for (int y = 0; y < prev_sub_rows_x; y++) {
                    free(data[x][y]);
                }
                free(data[x]);
                if (x < i) {
                   free(elements_sizes_per_sub_row[x]);
                }
            }
            free(elements_sizes_per_sub_row);
            free(sub_rows_sizes);
            free(data);
            return 1;
        }
        for (int j = 0; j < current_sub_rows; j++) {
            int current_elements = ((i + j) % MAX_ELEMENTS_PER_SUB_ROW_FACTOR) + 1;
            elements_sizes_per_sub_row[i][j] = current_elements;
            total_elements_count += current_elements;
            data[i][j] = (int *)malloc(current_elements * sizeof(int));
            if (data[i][j] == NULL) {
                for (int k = 0; k < j; k++) {
                    free(data[i][k]);
                }
                free(data[i]);
                free(elements_sizes_per_sub_row[i]);
                for (int x = 0; x < i; x++) {
                    int prev_sub_rows_x = sub_rows_sizes[x];
                    for (int y = 0; y < prev_sub_rows_x; y++) {
                        free(data[x][y]);
                    }
                    free(data[x]);
                    free(elements_sizes_per_sub_row[x]);
                }
                free(elements_sizes_per_sub_row);
                free(sub_rows_sizes);
                free(data);
                return 1;
            }
            for (int k = 0; k < current_elements; k++) {
                data[i][j][k] = i * 1000 + j * 100 + k;
            }
        }
    }
    flat_array = (int *)malloc(total_elements_count * sizeof(int));
    if (flat_array == NULL) {
        for (int i = 0; i < N_SUPER_ROWS; i++) {
            int current_sub_rows = sub_rows_sizes[i];
            for (int j = 0; j < current_sub_rows; j++) {
                free(data[i][j]);
            }
            free(data[i]);
            free(elements_sizes_per_sub_row[i]);
        }
        free(elements_sizes_per_sub_row);
        free(sub_rows_sizes);
        free(data);
        return 1;
    }
    int flat_idx = 0;
    for (int i = 0; i < N_SUPER_ROWS; i++) {
        int current_sub_rows = sub_rows_sizes[i];
        for (int j = 0; j < current_sub_rows; j++) {
            int current_elements = elements_sizes_per_sub_row[i][j];
            for (int k = 0; k < current_elements; k++) {
                flat_array[flat_idx++] = data[i][j][k];
            }
        }
    }
    for (int i = 0; i < N_SUPER_ROWS; i++) {
        int current_sub_rows = sub_rows_sizes[i];
        for (int j = 0; j < current_sub_rows; j++) {
            free(data[i][j]);
        }
        free(data[i]);
        free(elements_sizes_per_sub_row[i]);
    }
    free(data);
    free(elements_sizes_per_sub_row);
    free(sub_rows_sizes);
    free(flat_array);
    return 0;
}