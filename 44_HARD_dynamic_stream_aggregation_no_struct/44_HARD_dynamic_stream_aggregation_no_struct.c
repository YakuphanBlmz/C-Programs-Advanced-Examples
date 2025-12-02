#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void aggregate_and_transform_streams(int*** streams_collection_ptr, int* current_num_streams_ptr, int filter_value) {
    int* streams_collection = *streams_collection_ptr;
    int current_num_streams = *current_num_streams_ptr;
    if (current_num_streams == 0) {
        return;
    }
    int*  aggregated_stream_data = NULL;
    int   aggregated_stream_count = 0;
    int   num_to_aggregate = 0;
    int*  streams_to_remove_indices = (int*)malloc(current_num_streams * sizeof(int));
    if (!streams_to_remove_indices) exit(EXIT_FAILURE);
    for (int i = 0; i < current_num_streams; ++i) {
        int* current_stream = streams_collection[i];
        int count = current_stream[0];
        if (count > 0 && current_stream[1] < filter_value) {
            aggregated_stream_count += count;
            streams_to_remove_indices[num_to_aggregate++] = i;
        }
    }
    if (num_to_aggregate == 0) {
        free(streams_to_remove_indices);
        return;
    }
    aggregated_stream_data = (int*)malloc((1 + aggregated_stream_count) * sizeof(int));
    if (!aggregated_stream_data) exit(EXIT_FAILURE);
    aggregated_stream_data[0] = aggregated_stream_count;
    int current_copy_pos = 1;
    for (int i = 0; i < num_to_aggregate; ++i) {
        int stream_idx = streams_to_remove_indices[i];
        int* stream_to_copy = streams_collection[stream_idx];
        int count_to_copy = stream_to_copy[0];
        memcpy(aggregated_stream_data + current_copy_pos, stream_to_copy + 1, count_to_copy * sizeof(int));
        current_copy_pos += count_to_copy;
        free(stream_to_copy);
    }
    free(streams_to_remove_indices);
    int new_num_streams = current_num_streams - num_to_aggregate + 1; 
    int** new_streams_collection = (int**)malloc(new_num_streams * sizeof(int*));
    if (!new_streams_collection) exit(EXIT_FAILURE);
    int new_collection_idx = 0;
    for (int i = 0; i < current_num_streams; ++i) {
        int is_removed = 0;
        for (int j = 0; j < num_to_aggregate; ++j) {
            if (i == streams_to_remove_indices[j]) {
                is_removed = 1;
                break;
            }
        }
        if (!is_removed) {
            new_streams_collection[new_collection_idx++] = streams_collection[i];
        }
    }
    new_streams_collection[new_collection_idx] = aggregated_stream_data;
    free(streams_collection);
    *streams_collection_ptr = new_streams_collection;
    *current_num_streams_ptr = new_num_streams;
}
void print_streams(int** streams, int num_streams) {
    printf("Current Streams (%d):\n", num_streams);
    for (int i = 0; i < num_streams; ++i) {
        printf("  Stream %d: ", i);
        int count = streams[i][0];
        if (count == 0) {
            printf("[Empty]\n");
        } else {
            for (int j = 0; j < count; ++j) {
                printf("%d ", streams[i][j+1]);
            }
            printf(" (Count: %d)\n", count);
        }
    }
}
void free_all_streams(int*** streams_collection_ptr, int* num_streams_ptr) {
    int* streams_collection = *streams_collection_ptr;
    int num_streams = *num_streams_ptr;
    for (int i = 0; i < num_streams; ++i) {
        free(streams_collection[i]);
    }
    free(streams_collection);
    *streams_collection_ptr = NULL;
    *num_streams_ptr = 0;
}
int main() {
    int** streams = NULL;
    int num_streams = 0;
    int stream1_data[] = {3, 10, 20, 30};
    int* stream1 = (int*)malloc(sizeof(stream1_data));
    if (!stream1) exit(EXIT_FAILURE);
    memcpy(stream1, stream1_data, sizeof(stream1_data));
    int stream2_data[] = {2, 5, 15};
    int* stream2 = (int*)malloc(sizeof(stream2_data));
    if (!stream2) exit(EXIT_FAILURE);
    memcpy(stream2, stream2_data, sizeof(stream2_data));
    int stream3_data[] = {4, 100, 110, 120, 130};
    int* stream3 = (int*)malloc(sizeof(stream3_data));
    if (!stream3) exit(EXIT_FAILURE);
    memcpy(stream3, stream3_data, sizeof(stream3_data));
    int stream4_data[] = {1, 3};
    int* stream4 = (int*)malloc(sizeof(stream4_data));
    if (!stream4) exit(EXIT_FAILURE);
    memcpy(stream4, stream4_data, sizeof(stream4_data));
    int stream5_data[] = {0};
    int* stream5 = (int*)malloc(sizeof(stream5_data));
    if (!stream5) exit(EXIT_FAILURE);
    memcpy(stream5, stream5_data, sizeof(stream5_data));
    streams = (int**)malloc(5 * sizeof(int*));
    if (!streams) exit(EXIT_FAILURE);
    num_streams = 5;
    streams[0] = stream1;
    streams[1] = stream2;
    streams[2] = stream3;
    streams[3] = stream4;
    streams[4] = stream5;
    print_streams(streams, num_streams);
    printf("\nAggregating streams with first data element < 10... (Streams 2, 4 are expected to be aggregated, stream 5 is empty and not checked for value)");
    aggregate_and_transform_streams(&streams, &num_streams, 10);
    print_streams(streams, num_streams);
    printf("\nAggregating streams with first data element < 50... (Remaining stream 1, and the new aggregated stream from Test 1 are expected to be aggregated)");
    aggregate_and_transform_streams(&streams, &num_streams, 50);
    print_streams(streams, num_streams);
    printf("\nAggregating streams with first data element < 50... (No change expected)");
    aggregate_and_transform_streams(&streams, &num_streams, 50);
    print_streams(streams, num_streams);
    printf("\nAggregating streams with first data element < 200... (All remaining streams should be aggregated)");
    aggregate_and_transform_streams(&streams, &num_streams, 200);
    print_streams(streams, num_streams);
    free_all_streams(&streams, &num_streams);
    printf("\nAll memory freed. Exiting.\n");
    return 0;
}