#include <stdio.h>
#include <stdlib.h>
int main() {
    int flat_data_size = 10;
    int* flat_source_data = (int*)malloc(flat_data_size * sizeof(int));
    for (int i = 0; i < flat_data_size; i++) {
        flat_source_data[i] = i + 1;
    }
    int initial_num_rows = 3;
    int* initial_row_lengths = (int*)malloc(initial_num_rows * sizeof(int));
    initial_row_lengths[0] = 3;
    initial_row_lengths[1] = 2;
    initial_row_lengths[2] = 5;
    int** jagged_array = (int**)malloc(initial_num_rows * sizeof(int*));
    int current_flat_index = 0;
    for (int i = 0; i < initial_num_rows; i++) {
        int row_len = initial_row_lengths[i];
        jagged_array[i] = (int*)malloc(row_len * sizeof(int));
        for (int j = 0; j < row_len; j++) {
            jagged_array[i][j] = flat_source_data[current_flat_index++];
        }
    }
    int num_new_rows = 2;
    int new_row_length = 4;
    int total_rows = initial_num_rows + num_new_rows;
    jagged_array = (int**)realloc(jagged_array, total_rows * sizeof(int*));
    for (int i = initial_num_rows; i < total_rows; i++) {
        jagged_array[i] = (int*)malloc(new_row_length * sizeof(int));
        for (int j = 0; j < new_row_length; j++) {
            jagged_array[i][j] = j + 1;
        }
    }
    printf("Final Jagged Array:\n");
    for (int i = 0; i < total_rows; i++) {
        int current_row_len;
        if (i < initial_num_rows) {
            current_row_len = initial_row_lengths[i];
        } else {
            current_row_len = new_row_length;
        }
        printf("Row %d: ", i);
        for (int j = 0; j < current_row_len; j++) {
            printf("%d ", jagged_array[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < total_rows; i++) {
        free(jagged_array[i]);
    }
    free(jagged_array);
    free(flat_source_data);
    free(initial_row_lengths);
    return 0;
}