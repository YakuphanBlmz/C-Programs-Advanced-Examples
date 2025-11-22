#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITIAL_CAPACITY 2
#define RESIZE_FACTOR 2
#define SHRINK_THRESHOLD 4
int** create_jagged_array_container(int* rows_capacity_ptr, int* current_rows_count_ptr) {
    *rows_capacity_ptr = INITIAL_CAPACITY;
    *current_rows_count_ptr = 0;
    int** arr = (int**)malloc(*rows_capacity_ptr * sizeof(int*));
    if (arr == NULL) return NULL;
    for (int i = 0; i < *rows_capacity_ptr; i++) {
        arr[i] = NULL;
    }
    return arr;
}
void add_row(int*** array_ptr, int* rows_capacity_ptr, int* current_rows_count_ptr, int* row_data, int data_size) {
    if (*current_rows_count_ptr == *rows_capacity_ptr) {
        *rows_capacity_ptr *= RESIZE_FACTOR;
        int** new_arr = (int**)realloc(*array_ptr, *rows_capacity_ptr * sizeof(int*));
        if (new_arr == NULL) {
            return;
        }
        *array_ptr = new_arr;
        for (int i = *current_rows_count_ptr; i < *rows_capacity_ptr; i++) {
            (*array_ptr)[i] = NULL;
        }
    }
    int* new_row_block = (int*)malloc(sizeof(int) + data_size * sizeof(int));
    if (new_row_block == NULL) {
        return;
    }
    *new_row_block = data_size;
    memcpy((char*)new_row_block + sizeof(int), row_data, data_size * sizeof(int));
    (*array_ptr)[*current_rows_count_ptr] = new_row_block;
    (*current_rows_count_ptr)++;
}
void remove_row(int*** array_ptr, int* rows_capacity_ptr, int* current_rows_count_ptr, int row_index_to_remove) {
    if (row_index_to_remove < 0 || row_index_to_remove >= *current_rows_count_ptr) {
        return;
    }
    free((*array_ptr)[row_index_to_remove]);
    (*array_ptr)[row_index_to_remove] = NULL;
    for (int i = row_index_to_remove; i < *current_rows_count_ptr - 1; i++) {
        (*array_ptr)[i] = (*array_ptr)[i + 1];
    }
    (*array_ptr)[*current_rows_count_ptr - 1] = NULL;
    (*current_rows_count_ptr)--;
    if (*current_rows_count_ptr > 0 && *current_rows_count_ptr * SHRINK_THRESHOLD < *rows_capacity_ptr && *rows_capacity_ptr > INITIAL_CAPACITY) {
        int new_capacity = *rows_capacity_ptr / RESIZE_FACTOR;
        if (new_capacity < INITIAL_CAPACITY) new_capacity = INITIAL_CAPACITY;
        int** new_arr = (int**)realloc(*array_ptr, new_capacity * sizeof(int*));
        if (new_arr != NULL) {
            *array_ptr = new_arr;
            *rows_capacity_ptr = new_capacity;
        }
    }
}
void print_jagged_array(int** array, int current_rows_count) {
    printf("Jagged Array Content:\n");
    for (int i = 0; i < current_rows_count; i++) {
        printf("Row %d: [", i);
        int* row_block = array[i];
        if (row_block == NULL) {
            printf("NULL]\n");
            continue;
        }
        int row_size = *row_block;
        int* row_data_ptr = (int*)((char*)row_block + sizeof(int));
        for (int j = 0; j < row_size; j++) {
            printf("%d", row_data_ptr[j]);
            if (j < row_size - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}
void free_jagged_array(int*** array_ptr, int* current_rows_count_ptr) {
    if (*array_ptr == NULL) return;
    for (int i = 0; i < *current_rows_count_ptr; i++) {
        free((*array_ptr)[i]);
        (*array_ptr)[i] = NULL;
    }
    free(*array_ptr);
    *array_ptr = NULL;
    *current_rows_count_ptr = 0;
}
int main() {
    int** my_jagged_array = NULL;
    int current_capacity = 0;
    int active_rows = 0;
    my_jagged_array = create_jagged_array_container(&current_capacity, &active_rows);
    if (my_jagged_array == NULL) {
        return 1;
    }
    int r1[] = {10, 20, 30};
    add_row(&my_jagged_array, &current_capacity, &active_rows, r1, 3);
    int r2[] = {1, 2};
    add_row(&my_jagged_array, &current_capacity, &active_rows, r2, 2);
    int r3[] = {100};
    add_row(&my_jagged_array, &current_capacity, &active_rows, r3, 1);
    int r4[] = {5, 6, 7, 8};
    add_row(&my_jagged_array, &current_capacity, &active_rows, r4, 4);
    print_jagged_array(my_jagged_array, active_rows);
    printf("Capacity: %d, Active Rows: %d\n", current_capacity, active_rows);
    remove_row(&my_jagged_array, &current_capacity, &active_rows, 1);
    printf("After removing row at index 1:\n");
    print_jagged_array(my_jagged_array, active_rows);
    printf("Capacity: %d, Active Rows: %d\n", current_capacity, active_rows);
    int r5[] = {99, 98, 97};
    add_row(&my_jagged_array, &current_capacity, &active_rows, r5, 3);
    printf("After adding new row:\n");
    print_jagged_array(my_jagged_array, active_rows);
    printf("Capacity: %d, Active Rows: %d\n", current_capacity, active_rows);
    remove_row(&my_jagged_array, &current_capacity, &active_rows, 0);
    remove_row(&my_jagged_array, &current_capacity, &active_rows, 0);
    remove_row(&my_jagged_array, &current_capacity, &active_rows, 0);
    remove_row(&my_jagged_array, &current_capacity, &active_rows, 0);
    printf("After removing all rows:\n");
    print_jagged_array(my_jagged_array, active_rows);
    printf("Capacity: %d, Active Rows: %d\n", current_capacity, active_rows);
    free_jagged_array(&my_jagged_array, &active_rows);
    printf("After freeing: array_ptr is %p, active_rows is %d\n", (void*)my_jagged_array, active_rows);
    return 0;
}