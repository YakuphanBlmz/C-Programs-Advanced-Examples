#include <stdio.h>
#include <stdlib.h>
int processAndClean(int*** master_arr_ptr, int** sizes_arr_ptr, int* num_sub_arrays_ptr, int target) {
    int current_total_subarrays = *num_sub_arrays_ptr;
    int** master_arr = *master_arr_ptr;
    int* sizes_arr = *sizes_arr_ptr;
    for (int i = 0; i < current_total_subarrays; ++i) {
        int* current_sub_array = master_arr[i];
        int current_size = sizes_arr[i];
        int write_idx = 0;
        for (int read_idx = 0; read_idx < current_size; ++read_idx) {
            if (current_sub_array[read_idx] != target) {
                current_sub_array[write_idx++] = current_sub_array[read_idx];
            }
        }
        if (write_idx == 0) {
            free(current_sub_array);
            master_arr[i] = NULL;
            sizes_arr[i] = 0;
        } else if (write_idx < current_size) {
            int* new_ptr = (int*)realloc(current_sub_array, write_idx * sizeof(int));
            if (new_ptr == NULL) {
                free(current_sub_array);
                master_arr[i] = NULL;
                sizes_arr[i] = 0;
            } else {
                master_arr[i] = new_ptr;
                sizes_arr[i] = write_idx;
            }
        }
    }
    int new_total_subarrays = 0;
    for (int i = 0; i < current_total_subarrays; ++i) {
        if (master_arr[i] != NULL) {
            master_arr[new_total_subarrays] = master_arr[i];
            sizes_arr[new_total_subarrays] = sizes_arr[i];
            new_total_subarrays++;
        }
    }
    if (new_total_subarrays < current_total_subarrays) {
        if (new_total_subarrays == 0) {
            if (master_arr != NULL) free(master_arr);
            if (sizes_arr != NULL) free(sizes_arr);
            *master_arr_ptr = NULL;
            *sizes_arr_ptr = NULL;
        } else {
            int** new_master_arr = (int**)realloc(master_arr, new_total_subarrays * sizeof(int*));
            int* new_sizes_arr = (int*)realloc(sizes_arr, new_total_subarrays * sizeof(int));
            if (new_master_arr != NULL) {
                *master_arr_ptr = new_master_arr;
            }
            if (new_sizes_arr != NULL) {
                *sizes_arr_ptr = new_sizes_arr;
            }
        }
    }
    *num_sub_arrays_ptr = new_total_subarrays;
    return new_total_subarrays;
}
int main() {
    int initial_num_subarrays = 3;
    int** master_array = (int**)malloc(initial_num_subarrays * sizeof(int*));
    int* sizes_array = (int*)malloc(initial_num_subarrays * sizeof(int));
    sizes_array[0] = 5;
    master_array[0] = (int*)malloc(sizes_array[0] * sizeof(int));
    master_array[0][0] = 1; master_array[0][1] = 2; master_array[0][2] = 3; master_array[0][3] = 2; master_array[0][4] = 4;
    sizes_array[1] = 6;
    master_array[1] = (int*)malloc(sizes_array[1] * sizeof(int));
    master_array[1][0] = 5; master_array[1][1] = 2; master_array[1][2] = 6; master_array[1][3] = 7; master_array[1][4] = 2; master_array[1][5] = 8;
    sizes_array[2] = 3;
    master_array[2] = (int*)malloc(sizes_array[2] * sizeof(int));
    master_array[2][0] = 2; master_array[2][1] = 9; master_array[2][2] = 2;
    int target_value = 2;
    printf("Original arrays:\n");
    for (int i = 0; i < initial_num_subarrays; ++i) {
        printf("Sub-array %d (size %d): ", i, sizes_array[i]);
        for (int j = 0; j < sizes_array[i]; ++j) {
            printf("%d ", master_array[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    int current_num_subarrays = initial_num_subarrays;
    current_num_subarrays = processAndClean(&master_array, &sizes_array, &current_num_subarrays, target_value);
    printf("After processing (target = %d):\n", target_value);
    if (master_array == NULL || current_num_subarrays == 0) {
        printf("All sub-arrays were removed.\n");
    } else {
        for (int i = 0; i < current_num_subarrays; ++i) {
            printf("Sub-array %d (size %d): ", i, sizes_array[i]);
            for (int j = 0; j < sizes_array[i]; ++j) {
                printf("%d ", master_array[i][j]);
            }
            printf("\n");
        }
    }
    if (master_array != NULL) {
        for (int i = 0; i < current_num_subarrays; ++i) {
            free(master_array[i]);
        }
        free(master_array);
    }
    if (sizes_array != NULL) {
        free(sizes_array);
    }
    return 0;
}