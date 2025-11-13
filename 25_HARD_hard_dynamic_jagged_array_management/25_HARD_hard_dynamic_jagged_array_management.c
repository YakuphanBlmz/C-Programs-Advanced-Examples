#include <stdio.h>
#include <stdlib.h>
int main() {
    int **streams = NULL;
    int *stream_sizes = NULL;
    int *stream_capacities = NULL;
    int num_streams = 0;
    int max_streams_capacity = 0;
    max_streams_capacity = 2;
    streams = (int **)malloc(max_streams_capacity * sizeof(int *));
    if (streams == NULL) {
        printf("Memory allocation failed for streams.\n");
        return 1;
    }
    stream_sizes = (int *)malloc(max_streams_capacity * sizeof(int));
    if (stream_sizes == NULL) {
        printf("Memory allocation failed for stream_sizes.\n");
        free(streams);
        return 1;
    }
    stream_capacities = (int *)malloc(max_streams_capacity * sizeof(int));
    if (stream_capacities == NULL) {
        printf("Memory allocation failed for stream_capacities.\n");
        free(streams);
        free(stream_sizes);
        return 1;
    }
    for (int i = 0; i < 3; i++) {
        if (num_streams == max_streams_capacity) {
            int new_capacity = max_streams_capacity * 2;
            int **temp_streams = (int **)realloc(streams, new_capacity * sizeof(int *));
            if (temp_streams == NULL) {
                printf("Reallocation failed for streams.\n");
                for (int j = 0; j < num_streams; j++) {
                    free(streams[j]);
                }
                free(streams);
                free(stream_sizes);
                free(stream_capacities);
                return 1;
            }
            streams = temp_streams;
            int *temp_sizes = (int *)realloc(stream_sizes, new_capacity * sizeof(int));
            if (temp_sizes == NULL) {
                printf("Reallocation failed for stream_sizes.\n");
                for (int j = 0; j < num_streams; j++) {
                    free(streams[j]);
                }
                free(streams);
                free(stream_sizes);
                free(stream_capacities);
                return 1;
            }
            stream_sizes = temp_sizes;
            int *temp_capacities = (int *)realloc(stream_capacities, new_capacity * sizeof(int));
            if (temp_capacities == NULL) {
                printf("Reallocation failed for stream_capacities.\n");
                for (int j = 0; j < num_streams; j++) {
                    free(streams[j]);
                }
                free(streams);
                free(stream_sizes);
                free(stream_capacities);
                return 1;
            }
            stream_capacities = temp_capacities;
            max_streams_capacity = new_capacity;
        }
        int initial_stream_capacity = 2;
        streams[num_streams] = (int *)malloc(initial_stream_capacity * sizeof(int));
        if (streams[num_streams] == NULL) {
            printf("Memory allocation failed for individual stream %d.\n", num_streams);
            for (int j = 0; j < num_streams; j++) {
                free(streams[j]);
            }
            free(streams);
            free(stream_sizes);
            free(stream_capacities);
            return 1;
        }
        stream_sizes[num_streams] = 0;
        stream_capacities[num_streams] = initial_stream_capacity;
        num_streams++;
    }
    int target_stream_idx = 0;
    int values_to_add[] = {10, 20, 30};
    for (int i = 0; i < 3; i++) {
        if (stream_sizes[target_stream_idx] == stream_capacities[target_stream_idx]) {
            int new_stream_capacity = stream_capacities[target_stream_idx] * 2;
            int *temp_stream = (int *)realloc(streams[target_stream_idx], new_stream_capacity * sizeof(int));
            if (temp_stream == NULL) {
                printf("Reallocation failed for stream %d.\n", target_stream_idx);
                for (int j = 0; j < num_streams; j++) {
                    free(streams[j]);
                }
                free(streams);
                free(stream_sizes);
                free(stream_capacities);
                return 1;
            }
            streams[target_stream_idx] = temp_stream;
            stream_capacities[target_stream_idx] = new_stream_capacity;
        }
        streams[target_stream_idx][stream_sizes[target_stream_idx]++] = values_to_add[i];
    }
    target_stream_idx = 1;
    int more_values_to_add[] = {100, 200};
    for (int i = 0; i < 2; i++) {
        if (stream_sizes[target_stream_idx] == stream_capacities[target_stream_idx]) {
            int new_stream_capacity = stream_capacities[target_stream_idx] * 2;
            int *temp_stream = (int *)realloc(streams[target_stream_idx], new_stream_capacity * sizeof(int));
            if (temp_stream == NULL) {
                printf("Reallocation failed for stream %d.\n", target_stream_idx);
                for (int j = 0; j < num_streams; j++) {
                    free(streams[j]);
                }
                free(streams);
                free(stream_sizes);
                free(stream_capacities);
                return 1;
            }
            streams[target_stream_idx] = temp_stream;
            stream_capacities[target_stream_idx] = new_stream_capacity;
        }
        streams[target_stream_idx][stream_sizes[target_stream_idx]++] = more_values_to_add[i];
    }
    target_stream_idx = 2;
    int final_values_to_add[] = {500};
    for (int i = 0; i < 1; i++) {
        if (stream_sizes[target_stream_idx] == stream_capacities[target_stream_idx]) {
            int new_stream_capacity = stream_capacities[target_stream_idx] * 2;
            int *temp_stream = (int *)realloc(streams[target_stream_idx], new_stream_capacity * sizeof(int));
            if (temp_stream == NULL) {
                printf("Reallocation failed for stream %d.\n", target_stream_idx);
                for (int j = 0; j < num_streams; j++) {
                    free(streams[j]);
                }
                free(streams);
                free(stream_sizes);
                free(stream_capacities);
                return 1;
            }
            streams[target_stream_idx] = temp_stream;
            stream_capacities[target_stream_idx] = new_stream_capacity;
        }
        streams[target_stream_idx][stream_sizes[target_stream_idx]++] = final_values_to_add[i];
    }
    printf("--- After initial stream creation and element additions ---\n");
    for (int i = 0; i < num_streams; i++) {
        printf("Stream %d (size %d, capacity %d): ", i, stream_sizes[i], stream_capacities[i]);
        for (int j = 0; j < stream_sizes[i]; j++) {
            printf("%d ", streams[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    target_stream_idx = 0;
    int value_to_remove = 20;
    int found_idx = -1;
    for (int j = 0; j < stream_sizes[target_stream_idx]; j++) {
        if (streams[target_stream_idx][j] == value_to_remove) {
            found_idx = j;
            break;
        }
    }
    if (found_idx != -1) {
        for (int j = found_idx; j < stream_sizes[target_stream_idx] - 1; j++) {
            streams[target_stream_idx][j] = streams[target_stream_idx][j + 1];
        }
        stream_sizes[target_stream_idx]--;
    }
    printf("--- After removing %d from Stream %d ---\n", value_to_remove, target_stream_idx);
    for (int i = 0; i < num_streams; i++) {
        printf("Stream %d (size %d, capacity %d): ", i, stream_sizes[i], stream_capacities[i]);
        for (int j = 0; j < stream_sizes[i]; j++) {
            printf("%d ", streams[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    int stream_to_remove = 1;
    if (stream_to_remove >= 0 && stream_to_remove < num_streams) {
        free(streams[stream_to_remove]);
        for (int i = stream_to_remove; i < num_streams - 1; i++) {
            streams[i] = streams[i + 1];
            stream_sizes[i] = stream_sizes[i + 1];
            stream_capacities[i] = stream_capacities[i + 1];
        }
        num_streams--;
    }
    printf("--- After removing Stream %d ---\n", stream_to_remove);
    for (int i = 0; i < num_streams; i++) {
        printf("Stream %d (size %d, capacity %d): ", i, stream_sizes[i], stream_capacities[i]);
        for (int j = 0; j < stream_sizes[i]; j++) {
            printf("%d ", streams[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < num_streams; i++) {
        free(streams[i]);
    }
    free(streams);
    free(stream_sizes);
    free(stream_capacities);
    return 0;
}