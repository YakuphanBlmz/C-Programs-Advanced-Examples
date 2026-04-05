#include <stdio.h>
#include <stdlib.h>
void init_collection(int*** master_collection_ptr, int* master_size_ptr, int* master_capacity_ptr,
                     int** subcollection_sizes_ptr, int** subcollection_capacities_ptr,
                     int*** dynamic_array_lengths_ptr, int initial_master_capacity) {
    *master_collection_ptr = (int***)calloc(initial_master_capacity, sizeof(int**));
    *subcollection_sizes_ptr = (int*)calloc(initial_master_capacity, sizeof(int));
    *subcollection_capacities_ptr = (int*)calloc(initial_master_capacity, sizeof(int));
    *dynamic_array_lengths_ptr = (int**)calloc(initial_master_capacity, sizeof(int*));
    *master_size_ptr = 0;
    *master_capacity_ptr = initial_master_capacity;
}
void add_subcollection(int*** master_collection_ptr, int* master_size_ptr, int* master_capacity_ptr,
                       int** subcollection_sizes_ptr, int** subcollection_capacities_ptr,
                       int*** dynamic_array_lengths_ptr, int initial_sub_capacity) {
    if (*master_size_ptr >= *master_capacity_ptr) {
        *master_capacity_ptr *= 2;
        *master_collection_ptr = (int***)realloc(*master_collection_ptr, *master_capacity_ptr * sizeof(int**));
        *subcollection_sizes_ptr = (int*)realloc(*subcollection_sizes_ptr, *master_capacity_ptr * sizeof(int));
        *subcollection_capacities_ptr = (int*)realloc(*subcollection_capacities_ptr, *master_capacity_ptr * sizeof(int));
        *dynamic_array_lengths_ptr = (int**)realloc(*dynamic_array_lengths_ptr, *master_capacity_ptr * sizeof(int*));
        for (int i = *master_size_ptr; i < *master_capacity_ptr; i++) {
            (*master_collection_ptr)[i] = NULL;
            (*subcollection_sizes_ptr)[i] = 0;
            (*subcollection_capacities_ptr)[i] = 0;
            (*dynamic_array_lengths_ptr)[i] = NULL;
        }
    }
    int master_idx = *master_size_ptr;
    (*master_collection_ptr)[master_idx] = (int**)calloc(initial_sub_capacity, sizeof(int*));
    (*subcollection_sizes_ptr)[master_idx] = 0;
    (*subcollection_capacities_ptr)[master_idx] = initial_sub_capacity;
    (*dynamic_array_lengths_ptr)[master_idx] = (int*)calloc(initial_sub_capacity, sizeof(int));
    (*master_size_ptr)++;
}
void add_dynamic_array_to_subcollection(int*** master_collection_ptr, int subcollection_index,
                                        int** subcollection_sizes_ptr, int** subcollection_capacities_ptr,
                                        int*** dynamic_array_lengths_ptr, int initial_array_length) {
    if (subcollection_index >= *master_size_ptr || subcollection_index < 0) {
        return;
    }
    int current_sub_size = (*subcollection_sizes_ptr)[subcollection_index];
    int current_sub_capacity = (*subcollection_capacities_ptr)[subcollection_index];
    if (current_sub_size >= current_sub_capacity) {
        current_sub_capacity *= 2;
        (*master_collection_ptr)[subcollection_index] = (int**)realloc((*master_collection_ptr)[subcollection_index], current_sub_capacity * sizeof(int*));
        (*dynamic_array_lengths_ptr)[subcollection_index] = (int*)realloc((*dynamic_array_lengths_ptr)[subcollection_index], current_sub_capacity * sizeof(int));
        for (int i = current_sub_size; i < current_sub_capacity; i++) {
            (*master_collection_ptr)[subcollection_index][i] = NULL;
            (*dynamic_array_lengths_ptr)[subcollection_index][i] = 0;
        }
        (*subcollection_capacities_ptr)[subcollection_index] = current_sub_capacity;
    }
    int array_idx = current_sub_size;
    (*master_collection_ptr)[subcollection_index][array_idx] = (int*)malloc(initial_array_length * sizeof(int));
    for (int i = 0; i < initial_array_length; i++) {
        (*master_collection_ptr)[subcollection_index][array_idx][i] = i + (subcollection_index * 100) + (array_idx * 10);
    }
    (*dynamic_array_lengths_ptr)[subcollection_index][array_idx] = initial_array_length;
    (*subcollection_sizes_ptr)[subcollection_index]++;
}
void resize_dynamic_array(int*** master_collection_ptr, int subcollection_index, int array_index,
                          int*** dynamic_array_lengths_ptr, int new_length) {
    if (subcollection_index >= *master_size_ptr || subcollection_index < 0 ||
        array_index >= (*subcollection_sizes_ptr)[subcollection_index] || array_index < 0) {
        return;
    }
    int old_length = (*dynamic_array_lengths_ptr)[subcollection_index][array_index];
    (*master_collection_ptr)[subcollection_index][array_index] = (int*)realloc(
        (*master_collection_ptr)[subcollection_index][array_index], new_length * sizeof(int));
    if (new_length > old_length) {
        for (int i = old_length; i < new_length; i++) {
            (*master_collection_ptr)[subcollection_index][array_index][i] = i + (subcollection_index * 100) + (array_index * 10);
        }
    }
    (*dynamic_array_lengths_ptr)[subcollection_index][array_index] = new_length;
}
void print_collection(int*** master_collection, int master_size,
                      int* subcollection_sizes, int** dynamic_array_lengths) {
    printf("Master Collection Contents:\n");
    for (int i = 0; i < master_size; i++) {
        printf("  SubCollection %d (size: %d):\n", i, subcollection_sizes[i]);
        for (int j = 0; j < subcollection_sizes[i]; j++) {
            printf("    Dynamic Array %d (length: %d): [", j, dynamic_array_lengths[i][j]);
            for (int k = 0; k < dynamic_array_lengths[i][j]; k++) {
                printf("%d%s", master_collection[i][j][k], k == dynamic_array_lengths[i][j] - 1 ? "" : ", ");
            }
            printf("]\n");
        }
    }
}
void free_collection(int*** master_collection_ptr, int* master_size_ptr, int* master_capacity_ptr,
                     int** subcollection_sizes_ptr, int** subcollection_capacities_ptr,
                     int*** dynamic_array_lengths_ptr) {
    for (int i = 0; i < *master_size_ptr; i++) {
        for (int j = 0; j < (*subcollection_sizes_ptr)[i]; j++) {
            free((*master_collection_ptr)[i][j]);
            (*master_collection_ptr)[i][j] = NULL;
        }
        free((*master_collection_ptr)[i]);
        (*master_collection_ptr)[i] = NULL;
        free((*dynamic_array_lengths_ptr)[i]);
        (*dynamic_array_lengths_ptr)[i] = NULL;
    }
    free(*master_collection_ptr);
    *master_collection_ptr = NULL;
    free(*subcollection_sizes_ptr);
    *subcollection_sizes_ptr = NULL;
    free(*subcollection_capacities_ptr);
    *subcollection_capacities_ptr = NULL;
    free(*dynamic_array_lengths_ptr);
    *dynamic_array_lengths_ptr = NULL;
    *master_size_ptr = 0;
    *master_capacity_ptr = 0;
}
int main() {
    int*** master_collection = NULL;
    int master_collection_current_size = 0;
    int master_collection_capacity = 0;
    int* subcollection_current_sizes = NULL;
    int* subcollection_capacities = NULL;
    int** dynamic_array_current_lengths = NULL;
    init_collection(&master_collection, &master_collection_current_size, &master_collection_capacity,
                    &subcollection_current_sizes, &subcollection_capacities,
                    &dynamic_array_current_lengths, 2);
    add_subcollection(&master_collection, &master_collection_current_size, &master_collection_capacity,
                      &subcollection_current_sizes, &subcollection_capacities,
                      &dynamic_array_current_lengths, 3);
    add_dynamic_array_to_subcollection(&master_collection, 0, &subcollection_current_sizes,
                                       &subcollection_capacities, &dynamic_array_current_lengths, 5);
    add_dynamic_array_to_subcollection(&master_collection, 0, &subcollection_current_sizes,
                                       &subcollection_capacities, &dynamic_array_current_lengths, 3);
    add_subcollection(&master_collection, &master_collection_current_size, &master_collection_capacity,
                      &subcollection_current_sizes, &subcollection_capacities,
                      &dynamic_array_current_lengths, 2);
    add_dynamic_array_to_subcollection(&master_collection, 1, &subcollection_current_sizes,
                                       &subcollection_capacities, &dynamic_array_current_lengths, 4);
    printf("--- After Initial Setup ---\n");
    print_collection(master_collection, master_collection_current_size,
                     subcollection_current_sizes, dynamic_array_current_lengths);
    printf("\n");
    add_dynamic_array_to_subcollection(&master_collection, 0, &subcollection_current_sizes,
                                       &subcollection_capacities, &dynamic_array_current_lengths, 2);
    add_dynamic_array_to_subcollection(&master_collection, 0, &subcollection_current_sizes,
                                       &subcollection_capacities, &dynamic_array_current_lengths, 6);
    resize_dynamic_array(&master_collection, 0, 0, &dynamic_array_current_lengths, 7);
    resize_dynamic_array(&master_collection, 1, 0, &dynamic_array_current_lengths, 2);
    printf("--- After Additions and Resizes ---\n");
    print_collection(master_collection, master_collection_current_size,
                     subcollection_current_sizes, dynamic_array_current_lengths);
    printf("\n");
    free_collection(&master_collection, &master_collection_current_size, &master_collection_capacity,
                    &subcollection_current_sizes, &subcollection_capacities,
                    &dynamic_array_current_lengths);
    printf("--- After Freeing ---\n");
    if (master_collection == NULL && subcollection_current_sizes == NULL &&
        subcollection_capacities == NULL && dynamic_array_current_lengths == NULL) {
        printf("All memory successfully freed and pointers nulled.\n");
    } else {
        printf("Memory freeing failed or pointers not nulled.\n");
    }
    return 0;
}