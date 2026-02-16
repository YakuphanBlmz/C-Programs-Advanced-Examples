#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    srand(time(NULL));
    int num_arrays = 5;
    int min_row_size = 5;
    int max_row_size = 10;
    int realloc_add_size = 3;
    int **collection_of_arrays = (int **)malloc(num_arrays * sizeof(int *));
    int *array_sizes = (int *)malloc(num_arrays * sizeof(int));
    if (collection_of_arrays == NULL || array_sizes == NULL) {
        printf("Memory allocation failed for primary arrays.\n");
        if (collection_of_arrays != NULL) free(collection_of_arrays);
        if (array_sizes != NULL) free(array_sizes);
        return 1;
    }
    for (int i = 0; i < num_arrays; i++) {
        int current_row_size = (rand() % (max_row_size - min_row_size + 1)) + min_row_size;
        collection_of_arrays[i] = (int *)malloc(current_row_size * sizeof(int));
        if (collection_of_arrays[i] == NULL) {
            printf("Memory allocation failed for secondary array %d.\n", i);
            for (int k = 0; k < i; k++) {
                free(collection_of_arrays[k]);
            }
            free(collection_of_arrays);
            free(array_sizes);
            return 1;
        }
        array_sizes[i] = current_row_size;
        for (int j = 0; j < current_row_size; j++) {
            collection_of_arrays[i][j] = i * 10 + j;
        }
    }
    for (int i = 0; i < num_arrays; i++) {
        printf("Original Array %d (%d elements): ", i, array_sizes[i]);
        for (int j = 0; j < array_sizes[i]; j++) {
            printf("%d ", collection_of_arrays[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < num_arrays; i++) {
        int start = 0;
        int end = array_sizes[i] - 1;
        while (start < end) {
            int temp = collection_of_arrays[i][start];
            collection_of_arrays[i][start] = collection_of_arrays[i][end];
            collection_of_arrays[i][end] = temp;
            start++;
            end--;
        }
    }
    for (int i = 0; i < num_arrays; i++) {
        printf("Reversed Array %d (%d elements): ", i, array_sizes[i]);
        for (int j = 0; j < array_sizes[i]; j++) {
            printf("%d ", collection_of_arrays[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    long max_sum = -1;
    int max_sum_idx = -1;
    for (int i = 0; i < num_arrays; i++) {
        long current_sum = 0;
        for (int j = 0; j < array_sizes[i]; j++) {
            current_sum += collection_of_arrays[i][j];
        }
        if (current_sum > max_sum) {
            max_sum = current_sum;
            max_sum_idx = i;
        }
    }
    if (max_sum_idx != -1) {
        int old_size = array_sizes[max_sum_idx];
        int new_size = old_size + realloc_add_size;
        int *temp_ptr = (int *)realloc(collection_of_arrays[max_sum_idx], new_size * sizeof(int));
        if (temp_ptr == NULL) {
            printf("Memory re-allocation failed for array %d.\n", max_sum_idx);
            for (int k = 0; k < num_arrays; k++) {
                free(collection_of_arrays[k]);
            }
            free(collection_of_arrays);
            free(array_sizes);
            return 1;
        }
        collection_of_arrays[max_sum_idx] = temp_ptr;
        array_sizes[max_sum_idx] = new_size;
        for (int j = old_size; j < new_size; j++) {
            collection_of_arrays[max_sum_idx][j] = 0;
        }
        printf("Array %d (sum %ld) reallocated. New size: %d\n\n", max_sum_idx, max_sum, new_size);
    }
    for (int i = 0; i < num_arrays; i++) {
        printf("Final Array %d (%d elements): ", i, array_sizes[i]);
        for (int j = 0; j < array_sizes[i]; j++) {
            printf("%d ", collection_of_arrays[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < num_arrays; i++) {
        free(collection_of_arrays[i]);
    }
    free(collection_of_arrays);
    free(array_sizes);
    return 0;
}