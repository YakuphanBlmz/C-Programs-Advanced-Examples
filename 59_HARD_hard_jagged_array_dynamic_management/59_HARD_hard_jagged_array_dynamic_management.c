#include <stdio.h>
#include <stdlib.h>
int main() {
    int initial_rows = 3;
    int *initial_row_sizes = (int *)malloc(initial_rows * sizeof(int));
    if (initial_row_sizes == NULL) {
        return 1;
    }
    initial_row_sizes[0] = 2;
    initial_row_sizes[1] = 4;
    initial_row_sizes[2] = 3;
    int **jagged_array = (int **)malloc(initial_rows * sizeof(int *));
    if (jagged_array == NULL) {
        free(initial_row_sizes);
        return 1;
    }
    for (int i = 0; i < initial_rows; i++) {
        jagged_array[i] = (int *)malloc(initial_row_sizes[i] * sizeof(int));
        if (jagged_array[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(jagged_array[j]);
            }
            free(jagged_array);
            free(initial_row_sizes);
            return 1;
        }
        for (int j = 0; j < initial_row_sizes[i]; j++) {
            jagged_array[i][j] = i * 10 + j;
        }
    }
    int current_rows = initial_rows;
    int *row_dimensions = initial_row_sizes;
    printf("Initial Jagged Array:\n");
    for (int i = 0; i < current_rows; i++) {
        printf("Row %d (size %d): ", i, row_dimensions[i]);
        for (int j = 0; j < row_dimensions[i]; j++) {
            printf("%d ", jagged_array[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    int insert_index = 1;
    int new_row_cols = 5;
    current_rows++;
    int **temp_jagged = (int **)realloc(jagged_array, current_rows * sizeof(int *));
    if (temp_jagged == NULL) {
        for (int i = 0; i < current_rows - 1; i++) {
            free(jagged_array[i]);
        }
        free(jagged_array);
        free(row_dimensions);
        return 1;
    }
    jagged_array = temp_jagged;
    int *temp_dimensions = (int *)realloc(row_dimensions, current_rows * sizeof(int));
    if (temp_dimensions == NULL) {
        for (int i = 0; i < current_rows - 1; i++) {
            free(jagged_array[i]);
        }
        free(jagged_array);
        free(row_dimensions);
        return 1;
    }
    row_dimensions = temp_dimensions;
    for (int i = current_rows - 1; i > insert_index; i--) {
        jagged_array[i] = jagged_array[i - 1];
        row_dimensions[i] = row_dimensions[i - 1];
    }
    jagged_array[insert_index] = (int *)malloc(new_row_cols * sizeof(int));
    if (jagged_array[insert_index] == NULL) {
        for (int i = 0; i < current_rows - 1; i++) {
            if (i != insert_index) free(jagged_array[i]);
        }
        free(jagged_array[insert_index]);
        free(jagged_array);
        free(row_dimensions);
        return 1;
    }
    row_dimensions[insert_index] = new_row_cols;
    for (int j = 0; j < new_row_cols; j++) {
        jagged_array[insert_index][j] = 100 + j;
    }
    printf("Jagged Array after inserting new row at index %d:\n", insert_index);
    for (int i = 0; i < current_rows; i++) {
        printf("Row %d (size %d): ", i, row_dimensions[i]);
        for (int j = 0; j < row_dimensions[i]; j++) {
            printf("%d ", jagged_array[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    int remove_index = 2;
    free(jagged_array[remove_index]);
    for (int i = remove_index; i < current_rows - 1; i++) {
        jagged_array[i] = jagged_array[i + 1];
        row_dimensions[i] = row_dimensions[i + 1];
    }
    current_rows--;
    temp_jagged = (int **)realloc(jagged_array, current_rows * sizeof(int *));
    if (temp_jagged == NULL && current_rows > 0) {
        for (int i = 0; i < current_rows + 1; i++) {
             if (i != remove_index) free(jagged_array[i]);
        }
        free(jagged_array);
        free(row_dimensions);
        return 1;
    }
    jagged_array = temp_jagged;
    temp_dimensions = (int *)realloc(row_dimensions, current_rows * sizeof(int));
    if (temp_dimensions == NULL && current_rows > 0) {
        for (int i = 0; i < current_rows + 1; i++) {
             if (i != remove_index) free(jagged_array[i]);
        }
        free(jagged_array);
        free(row_dimensions);
        return 1;
    }
    row_dimensions = temp_dimensions;
    printf("Jagged Array after removing row at index %d:\n", remove_index);
    for (int i = 0; i < current_rows; i++) {
        printf("Row %d (size %d): ", i, row_dimensions[i]);
        for (int j = 0; j < row_dimensions[i]; j++) {
            printf("%d ", jagged_array[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < current_rows; i++) {
        free(jagged_array[i]);
    }
    free(jagged_array);
    free(row_dimensions);
    return 0;
}