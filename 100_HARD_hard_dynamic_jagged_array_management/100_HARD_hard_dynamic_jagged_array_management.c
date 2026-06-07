#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void addSequence(int*** collection_ptr, int** lengths_ptr, int* size_ptr, int* capacity_ptr, const int* new_sequence_data, int new_sequence_length) {
    if (*size_ptr == *capacity_ptr) {
        int new_capacity = (*capacity_ptr == 0) ? 4 : (*capacity_ptr * 2);
        int** new_collection = (int**)realloc(*collection_ptr, new_capacity * sizeof(int*));
        if (new_collection == NULL) {
            fprintf(stderr, "Failed to reallocate collection\n");
            exit(EXIT_FAILURE);
        }
        *collection_ptr = new_collection;
        int* new_lengths = (int*)realloc(*lengths_ptr, new_capacity * sizeof(int));
        if (new_lengths == NULL) {
            fprintf(stderr, "Failed to reallocate lengths\n");
            exit(EXIT_FAILURE);
        }
        *lengths_ptr = new_lengths;
        *capacity_ptr = new_capacity;
    }
    int* sequence_copy = (int*)malloc(new_sequence_length * sizeof(int));
    if (sequence_copy == NULL) {
        fprintf(stderr, "Failed to allocate memory for new sequence\n");
        exit(EXIT_FAILURE);
    }
    memcpy(sequence_copy, new_sequence_data, new_sequence_length * sizeof(int));
    (*collection_ptr)[*size_ptr] = sequence_copy;
    (*lengths_ptr)[*size_ptr] = new_sequence_length;
    (*size_ptr)++;
}
int* flattenCollection(int** collection, int* lengths, int size, int* total_length_ptr) {
    int total_len = 0;
    for (int i = 0; i < size; i++) {
        total_len += lengths[i];
    }
    *total_length_ptr = total_len;
    int* flattened_array = (int*)malloc(total_len * sizeof(int));
    if (flattened_array == NULL) {
        fprintf(stderr, "Failed to allocate memory for flattened array\n");
        exit(EXIT_FAILURE);
    }
    int current_pos = 0;
    for (int i = 0; i < size; i++) {
        memcpy(flattened_array + current_pos, collection[i], lengths[i] * sizeof(int));
        current_pos += lengths[i];
    }
    return flattened_array;
}
void freeCollection(int*** collection_ptr, int** lengths_ptr, int* size_ptr) {
    if (*collection_ptr != NULL) {
        for (int i = 0; i < *size_ptr; i++) {
            free((*collection_ptr)[i]);
        }
        free(*collection_ptr);
        *collection_ptr = NULL;
    }
    if (*lengths_ptr != NULL) {
        free(*lengths_ptr);
        *lengths_ptr = NULL;
    }
    *size_ptr = 0;
}
int main() {
    int** dynamic_collection = NULL;
    int* sequence_lengths = NULL;
    int collection_size = 0;
    int collection_capacity = 0;
    int s1[] = {10, 20, 30};
    addSequence(&dynamic_collection, &sequence_lengths, &collection_size, &collection_capacity, s1, 3);
    int s2[] = {5, 15};
    addSequence(&dynamic_collection, &sequence_lengths, &collection_size, &collection_capacity, s2, 2);
    int s3[] = {100};
    addSequence(&dynamic_collection, &sequence_lengths, &collection_size, &collection_capacity, s3, 1);
    int s4[] = {1, 2, 3, 4, 5, 6};
    addSequence(&dynamic_collection, &sequence_lengths, &collection_size, &collection_capacity, s4, 6);
    printf("Collection content:\n");
    for (int i = 0; i < collection_size; i++) {
        printf("  Sequence %d (length %d): ", i, sequence_lengths[i]);
        for (int j = 0; j < sequence_lengths[i]; j++) {
            printf("%d ", dynamic_collection[i][j]);
        }
        printf("\n");
    }
    int total_flattened_length = 0;
    int* flattened_data = flattenCollection(dynamic_collection, sequence_lengths, collection_size, &total_flattened_length);
    printf("\nFlattened collection (total length %d):\n", total_flattened_length);
    for (int i = 0; i < total_flattened_length; i++) {
        printf("%d ", flattened_data[i]);
    }
    printf("\n");
    free(flattened_data);
    flattened_data = NULL;
    freeCollection(&dynamic_collection, &sequence_lengths, &collection_size);
    return 0;
}