#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void create_ragged_array(int ***matrix_ptr, int *num_rows_ptr, int seed)
{
    srand(seed);
    int num_rows = (rand() % 5) + 3;
    *num_rows_ptr = num_rows;
    int **matrix = (int **)malloc(num_rows * sizeof(int *));
    if (matrix == NULL) {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < num_rows; i++) {
        int row_data_length = (rand() % 5) + 2;
        matrix[i] = (int *)malloc((row_data_length + 1) * sizeof(int));
        if (matrix[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(matrix[k]);
            }
            free(matrix);
            exit(EXIT_FAILURE);
        }
        matrix[i][0] = row_data_length;
        for (int j = 1; j <= row_data_length; j++) {
            matrix[i][j] = (i * 100) + j;
        }
    }
    *matrix_ptr = matrix;
}
int *flatten_ragged_array(int **matrix, int num_rows, int *total_elements_ptr)
{
    int total_data_elements = 0;
    for (int i = 0; i < num_rows; i++) {
        if (matrix[i] != NULL) {
            total_data_elements += matrix[i][0];
        }
    }
    *total_elements_ptr = total_data_elements;
    if (total_data_elements == 0) {
        return NULL;
    }
    int *flat_array = (int *)malloc(total_data_elements * sizeof(int));
    if (flat_array == NULL) {
        exit(EXIT_FAILURE);
    }
    int current_index = 0;
    for (int i = 0; i < num_rows; i++) {
        if (matrix[i] != NULL) {
            int row_data_length = matrix[i][0];
            for (int j = 1; j <= row_data_length; j++) {
                flat_array[current_index++] = matrix[i][j];
            }
        }
    }
    return flat_array;
}
int **expand_flattened_array(int *flat_array, int total_elements, int *new_num_rows_ptr)
{
    if (total_elements == 0) {
        *new_num_rows_ptr = 0;
        return NULL;
    }
    int new_num_rows = (total_elements / 3) + 1;
    if (new_num_rows > total_elements && total_elements > 0) new_num_rows = total_elements;
    if (new_num_rows == 0 && total_elements > 0) new_num_rows = 1;
    *new_num_rows_ptr = new_num_rows;
    int **new_matrix = (int **)malloc(new_num_rows * sizeof(int *));
    if (new_matrix == NULL) {
        exit(EXIT_FAILURE);
    }
    int current_flat_index = 0;
    for (int i = 0; i < new_num_rows; i++) {
        int row_data_length;
        if (i == new_num_rows - 1) {
            row_data_length = total_elements - current_flat_index;
        } else {
            row_data_length = (total_elements - current_flat_index) / (new_num_rows - i);
            if (row_data_length == 0 && (total_elements - current_flat_index) > 0) {
                row_data_length = 1;
            }
        }
        if (row_data_length == 0) {
            new_matrix[i] = (int *)malloc(sizeof(int));
            if (new_matrix[i] == NULL) {
                for (int k = 0; k < i; k++) {
                    free(new_matrix[k]);
                }
                free(new_matrix);
                exit(EXIT_FAILURE);
            }
            new_matrix[i][0] = 0;
        } else {
            new_matrix[i] = (int *)malloc((row_data_length + 1) * sizeof(int));
            if (new_matrix[i] == NULL) {
                for (int k = 0; k < i; k++) {
                    free(new_matrix[k]);
                }
                free(new_matrix);
                exit(EXIT_FAILURE);
            }
            new_matrix[i][0] = row_data_length;
            for (int j = 1; j <= row_data_length; j++) {
                new_matrix[i][j] = flat_array[current_flat_index++];
            }
        }
    }
    return new_matrix;
}
void print_ragged_array(int **matrix, int num_rows, const char *title)
{
    printf("%s:\n", title);
    if (matrix == NULL || num_rows == 0) {
        printf("  (Empty)\n");
        return;
    }
    for (int i = 0; i < num_rows; i++) {
        printf("  Row %d (len: %d): ", i, matrix[i][0]);
        for (int j = 1; j <= matrix[i][0]; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
void free_ragged_array(int **matrix, int num_rows)
{
    if (matrix == NULL) return;
    for (int i = 0; i < num_rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
int main() {
    int **original_ragged_array = NULL;
    int original_num_rows = 0;
    int *flattened_array = NULL;
    int total_elements_in_flat = 0;
    int **expanded_ragged_array = NULL;
    int expanded_num_rows = 0;
    create_ragged_array(&original_ragged_array, &original_num_rows, (int)time(NULL));
    print_ragged_array(original_ragged_array, original_num_rows, "Original Ragged Array");
    flattened_array = flatten_ragged_array(original_ragged_array, original_num_rows, &total_elements_in_flat);
    printf("\nFlattened Array (%d elements): ", total_elements_in_flat);
    if (flattened_array == NULL) {
        printf("(Empty)\n");
    } else {
        for (int i = 0; i < total_elements_in_flat; i++) {
            printf("%d ", flattened_array[i]);
        }
        printf("\n");
    }
    expanded_ragged_array = expand_flattened_array(flattened_array, total_elements_in_flat, &expanded_num_rows);
    print_ragged_array(expanded_ragged_array, expanded_num_rows, "\nExpanded Ragged Array");
    free_ragged_array(original_ragged_array, original_num_rows);
    free_ragged_array(expanded_ragged_array, expanded_num_rows);
    free(flattened_array);
    return 0;
}