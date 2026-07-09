#include <stdio.h>
#include <stdlib.h>
int main() {
    int num_outer_arrays = 3;
    int num_inner_arrays_per_outer_array = 4;
    int*** dynamic_3d_array = (int***)malloc(num_outer_arrays * sizeof(int**));
    if (dynamic_3d_array == NULL) return 1;
    for (int i = 0; i < num_outer_arrays; i++) {
        dynamic_3d_array[i] = (int**)malloc(num_inner_arrays_per_outer_array * sizeof(int*));
        if (dynamic_3d_array[i] == NULL) {
            for (int k = 0; k < i; k++) {
                for (int l = 0; l < num_inner_arrays_per_outer_array; l++) {
                    if (dynamic_3d_array[k][l] != NULL) free(dynamic_3d_array[k][l]);
                }
                free(dynamic_3d_array[k]);
            }
            free(dynamic_3d_array);
            return 1;
        }
        for (int j = 0; j < num_inner_arrays_per_outer_array; j++) {
            dynamic_3d_array[i][j] = (int*)malloc(sizeof(int));
            if (dynamic_3d_array[i][j] == NULL) {
                for (int k = 0; k < j; k++) {
                    free(dynamic_3d_array[i][k]);
                }
                free(dynamic_3d_array[i]);
                for (int k = 0; k < i; k++) {
                    for (int l = 0; l < num_inner_arrays_per_outer_array; l++) {
                        if (dynamic_3d_array[k][l] != NULL) free(dynamic_3d_array[k][l]);
                    }
                    free(dynamic_3d_array[k]);
                }
                free(dynamic_3d_array);
                return 1;
            }
            *dynamic_3d_array[i][j] = i * 100 + j;
        }
    }
    int total_elements = num_outer_arrays * num_inner_arrays_per_outer_array;
    int* flattened_array = (int*)malloc(total_elements * sizeof(int));
    if (flattened_array == NULL) {
        for (int i = 0; i < num_outer_arrays; i++) {
            for (int j = 0; j < num_inner_arrays_per_outer_array; j++) {
                free(dynamic_3d_array[i][j]);
            }
            free(dynamic_3d_array[i]);
        }
        free(dynamic_3d_array);
        return 1;
    }
    int k = 0;
    for (int i = 0; i < num_outer_arrays; i++) {
        for (int j = 0; j < num_inner_arrays_per_outer_array; j++) {
            flattened_array[k++] = *dynamic_3d_array[i][j];
        }
    }
    for (int i = 0; i < num_outer_arrays; i++) {
        for (int j = 0; j < num_inner_arrays_per_outer_array; j++) {
            free(dynamic_3d_array[i][j]);
        }
        free(dynamic_3d_array[i]);
    }
    free(dynamic_3d_array);
    for (int i = 0; i < total_elements; i++) {
        printf("%d ", flattened_array[i]);
    }
    printf("\n");
    free(flattened_array);
    return 0;
}