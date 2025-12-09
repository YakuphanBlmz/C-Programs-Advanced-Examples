#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void printJaggedArray(int** arr, int* lengths, int rows) {
    printf("Jagged Array Contents (%d rows):\n", rows);
    for (int i = 0; i < rows; i++) {
        printf("  Row %d (length %d): [", i, lengths[i]);
        for (int j = 0; j < lengths[i]; j++) {
            printf("%d%s", arr[i][j], (j == lengths[i] - 1) ? "" : ", ");
        }
        printf("]\n");
    }
}
void insertRowAtBeginning(int*** jagged_array_ptr, int** row_lengths_ptr, int* num_rows_ptr, int* new_row_data, int new_row_length) {
    int current_rows = *num_rows_ptr;
    int** current_jagged_array = *jagged_array_ptr;
    int* current_row_lengths = *row_lengths_ptr;
    (*num_rows_ptr)++;
    current_jagged_array = (int**)realloc(current_jagged_array, (*num_rows_ptr) * sizeof(int*));
    if (current_jagged_array == NULL) {
        exit(EXIT_FAILURE);
    }
    *jagged_array_ptr = current_jagged_array;
    current_row_lengths = (int*)realloc(current_row_lengths, (*num_rows_ptr) * sizeof(int));
    if (current_row_lengths == NULL) {
        exit(EXIT_FAILURE);
    }
    *row_lengths_ptr = current_row_lengths;
    for (int i = current_rows; i > 0; i--) {
        current_jagged_array[i] = current_jagged_array[i-1];
        current_row_lengths[i] = current_row_lengths[i-1];
    }
    int* new_row_mem = (int*)malloc(new_row_length * sizeof(int));
    if (new_row_mem == NULL) {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < new_row_length; i++) {
        new_row_mem[i] = new_row_data[i];
    }
    current_jagged_array[0] = new_row_mem;
    current_row_lengths[0] = new_row_length;
}
int main() {
    srand(time(NULL));
    int num_rows = 3;
    int** jagged_array = NULL;
    int* row_lengths = NULL;
    jagged_array = (int**)malloc(num_rows * sizeof(int*));
    if (jagged_array == NULL) {
        return 1;
    }
    row_lengths = (int*)malloc(num_rows * sizeof(int));
    if (row_lengths == NULL) {
        free(jagged_array);
        return 1;
    }
    for (int i = 0; i < num_rows; i++) {
        row_lengths[i] = 2 + (rand() % 4);
        jagged_array[i] = (int*)malloc(row_lengths[i] * sizeof(int));
        if (jagged_array[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(jagged_array[k]);
            }
            free(jagged_array);
            free(row_lengths);
            return 1;
        }
        for (int j = 0; j < row_lengths[i]; j++) {
            jagged_array[i][j] = (i + 1) * 10 + j + 1;
        }
    }
    printJaggedArray(jagged_array, row_lengths, num_rows);
    int new_data_to_insert[] = {100, 200, 300, 400, 500};
    int new_length_to_insert = 5;
    insertRowAtBeginning(&jagged_array, &row_lengths, &num_rows, new_data_to_insert, new_length_to_insert);
    printf("\nAfter inserting new row at beginning:\n");
    printJaggedArray(jagged_array, row_lengths, num_rows);
    for (int i = 0; i < num_rows; i++) {
        free(jagged_array[i]);
    }
    free(jagged_array);
    free(row_lengths);
    return 0;
}