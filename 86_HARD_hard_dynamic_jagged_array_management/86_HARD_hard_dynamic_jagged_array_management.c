#include <stdio.h>
#include <stdlib.h>
void initialize_collection(int*** streams_ptr_to_ptr, int** capacities_ptr_to_ptr, int** sizes_ptr_to_ptr, int* current_streams_ptr, int* max_streams_capacity_ptr, int initial_max_streams) {
    *current_streams_ptr = 0;
    *max_streams_capacity_ptr = initial_max_streams;
    *streams_ptr_to_ptr = (int**)malloc(initial_max_streams * sizeof(int*));
    if (*streams_ptr_to_ptr == NULL) {
        exit(EXIT_FAILURE);
    }
    *capacities_ptr_to_ptr = (int*)malloc(initial_max_streams * sizeof(int));
    if (*capacities_ptr_to_ptr == NULL) {
        free(*streams_ptr_to_ptr);
        *streams_ptr_to_ptr = NULL;
        exit(EXIT_FAILURE);
    }
    *sizes_ptr_to_ptr = (int*)malloc(initial_max_streams * sizeof(int));
    if (*sizes_ptr_to_ptr == NULL) {
        free(*streams_ptr_to_ptr);
        *streams_ptr_to_ptr = NULL;
        free(*capacities_ptr_to_ptr);
        *capacities_ptr_to_ptr = NULL;
        exit(EXIT_FAILURE);
    }
}
void add_stream(int*** streams_ptr_to_ptr, int** capacities_ptr_to_ptr, int** sizes_ptr_to_ptr, int* current_streams_ptr, int* max_streams_capacity_ptr, int initial_row_capacity) {
    if (*current_streams_ptr >= *max_streams_capacity_ptr) {
        *max_streams_capacity_ptr *= 2;
        int** new_streams = (int**)realloc(*streams_ptr_to_ptr, *max_streams_capacity_ptr * sizeof(int*));
        if (new_streams == NULL) {
            exit(EXIT_FAILURE);
        }
        *streams_ptr_to_ptr = new_streams;
        int* new_capacities = (int*)realloc(*capacities_ptr_to_ptr, *max_streams_capacity_ptr * sizeof(int));
        if (new_capacities == NULL) {
            exit(EXIT_FAILURE);
        }
        *capacities_ptr_to_ptr = new_capacities;
        int* new_sizes = (int*)realloc(*sizes_ptr_to_ptr, *max_streams_capacity_ptr * sizeof(int));
        if (new_sizes == NULL) {
            exit(EXIT_FAILURE);
        }
        *sizes_ptr_to_ptr = new_sizes;
    }
    int new_stream_index = *current_streams_ptr;
    (*streams_ptr_to_ptr)[new_stream_index] = (int*)malloc(initial_row_capacity * sizeof(int));
    if ((*streams_ptr_to_ptr)[new_stream_index] == NULL) {
        exit(EXIT_FAILURE);
    }
    (*capacities_ptr_to_ptr)[new_stream_index] = initial_row_capacity;
    (*sizes_ptr_to_ptr)[new_stream_index] = 0;
    (*current_streams_ptr)++;
}
void add_data_to_stream(int** streams, int* capacities, int* sizes, int current_streams, int stream_index, int data_value) {
    if (stream_index < 0 || stream_index >= current_streams) {
        return;
    }
    if (sizes[stream_index] >= capacities[stream_index]) {
        capacities[stream_index] *= 2;
        int* new_stream_row = (int*)realloc(streams[stream_index], capacities[stream_index] * sizeof(int));
        if (new_stream_row == NULL) {
            exit(EXIT_FAILURE);
        }
        streams[stream_index] = new_stream_row;
    }
    streams[stream_index][sizes[stream_index]] = data_value;
    sizes[stream_index]++;
}
void print_collection(int** streams, int* sizes, int current_streams) {
    printf("Current Stream Collection:\n");
    if (current_streams == 0) {
        printf("  (Collection is empty)\n");
        return;
    }
    for (int i = 0; i < current_streams; i++) {
        printf("  Stream %d (Size: %d): [", i, sizes[i]);
        for (int j = 0; j < sizes[i]; j++) {
            printf("%d", streams[i][j]);
            if (j < sizes[i] - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}
void free_collection(int*** streams_ptr_to_ptr, int** capacities_ptr_to_ptr, int** sizes_ptr_to_ptr, int* current_streams_ptr) {
    if (*streams_ptr_to_ptr != NULL) {
        for (int i = 0; i < *current_streams_ptr; i++) {
            free((*streams_ptr_to_ptr)[i]);
        }
        free(*streams_ptr_to_ptr);
        *streams_ptr_to_ptr = NULL;
    }
    if (*capacities_ptr_to_ptr != NULL) {
        free(*capacities_ptr_to_ptr);
        *capacities_ptr_to_ptr = NULL;
    }
    if (*sizes_ptr_to_ptr != NULL) {
        free(*sizes_ptr_to_ptr);
        *sizes_ptr_to_ptr = NULL;
    }
    *current_streams_ptr = 0;
}
int main() {
    int** streams = NULL;
    int* capacities = NULL;
    int* sizes = NULL;
    int current_streams = 0;
    int max_streams_capacity = 0;
    initialize_collection(&streams, &capacities, &sizes, &current_streams, &max_streams_capacity, 2);
    print_collection(streams, sizes, current_streams);
    add_stream(&streams, &capacities, &sizes, &current_streams, &max_streams_capacity, 3);
    add_data_to_stream(streams, capacities, sizes, current_streams, 0, 10);
    add_data_to_stream(streams, capacities, sizes, current_streams, 0, 20);
    add_data_to_stream(streams, capacities, sizes, current_streams, 0, 30);
    add_data_to_stream(streams, capacities, sizes, current_streams, 0, 40);
    print_collection(streams, sizes, current_streams);
    add_stream(&streams, &capacities, &sizes, &current_streams, &max_streams_capacity, 2);
    add_data_to_stream(streams, capacities, sizes, current_streams, 1, 100);
    add_data_to_stream(streams, capacities, sizes, current_streams, 1, 200);
    add_data_to_stream(streams, capacities, sizes, current_streams, 1, 300);
    print_collection(streams, sizes, current_streams);
    add_stream(&streams, &capacities, &sizes, &current_streams, &max_streams_capacity, 5);
    add_data_to_stream(streams, capacities, sizes, current_streams, 2, 5);
    add_data_to_stream(streams, capacities, sizes, current_streams, 2, 10);
    print_collection(streams, sizes, current_streams);
    free_collection(&streams, &capacities, &sizes, &current_streams);
    print_collection(streams, sizes, current_streams);
    return 0;
}