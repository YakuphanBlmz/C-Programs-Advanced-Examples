#include <stdio.h>
#include <stdlib.h>
int isRowAllEven(int* row, int length) {
    if (length == 0) {
        return 1;
    }
    for (int i = 0; i < length; i++) {
        if (row[i] % 2 != 0) {
            return 0;
        }
    }
    return 1;
}
int cleanJaggedArray(int*** arr_ptr, int** row_lengths_ptr, int* num_rows_ptr) {
    int** arr = *arr_ptr;
    int* row_lengths = *row_lengths_ptr;
    int num_rows = *num_rows_ptr;
    if (num_rows == 0) {
        return 0;
    }
    int write_idx = 0;
    for (int read_idx = 0; read_idx < num_rows; read_idx++) {
        if (isRowAllEven(arr[read_idx], row_lengths[read_idx])) {
            free(arr[read_idx]);
        } else {
            if (read_idx != write_idx) {
                arr[write_idx] = arr[read_idx];
                row_lengths[write_idx] = row_lengths[read_idx];
            }
            write_idx++;
        }
    }
    *num_rows_ptr = write_idx;
    if (write_idx == 0) {
        free(arr);
        *arr_ptr = NULL;
    } else {
        int** new_arr = (int**)realloc(arr, write_idx * sizeof(int*));
        if (new_arr == NULL && write_idx > 0) {
            exit(EXIT_FAILURE);
        }
        *arr_ptr = new_arr;
    }
    if (write_idx == 0) {
        free(row_lengths);
        *row_lengths_ptr = NULL;
    } else {
        int* new_row_lengths = (int*)realloc(row_lengths, write_idx * sizeof(int));
        if (new_row_lengths == NULL && write_idx > 0) {
            exit(EXIT_FAILURE);
        }
        *row_lengths_ptr = new_row_lengths;
    }
    return write_idx;
}