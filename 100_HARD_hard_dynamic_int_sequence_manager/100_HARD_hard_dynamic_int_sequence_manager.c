#include <stdio.h>
#include <stdlib.h>
void initialize_collection(int ***collection_ptr, int **lengths_ptr, int *num_sequences_ptr, int *capacity_ptr) {
    int initial_capacity = 2;
    *collection_ptr = (int **)malloc(initial_capacity * sizeof(int *));
    *lengths_ptr = (int *)malloc(initial_capacity * sizeof(int));
    *num_sequences_ptr = 0;
    *capacity_ptr = initial_capacity;
}
void add_sequence(int ***collection_ptr, int **lengths_ptr, int *num_sequences_ptr, int *capacity_ptr, const int *data, int data_len) {
    if (*num_sequences_ptr == *capacity_ptr) {
        *capacity_ptr *= 2;
        *collection_ptr = (int **)realloc(*collection_ptr, *capacity_ptr * sizeof(int *));
        *lengths_ptr = (int *)realloc(*lengths_ptr, *capacity_ptr * sizeof(int));
    }
    (*collection_ptr)[*num_sequences_ptr] = (int *)malloc(data_len * sizeof(int));
    for (int i = 0; i < data_len; i++) {
        (*collection_ptr)[*num_sequences_ptr][i] = data[i];
    }
    (*lengths_ptr)[*num_sequences_ptr] = data_len;
    (*num_sequences_ptr)++;
}
void extend_sequence(int **collection, int *lengths, int index, const int *new_data, int new_data_len) {
    int current_len = lengths[index];
    int new_total_len = current_len + new_data_len;
    collection[index] = (int *)realloc(collection[index], new_total_len * sizeof(int));
    for (int i = 0; i < new_data_len; i++) {
        collection[index][current_len + i] = new_data[i];
    }
    lengths[index] = new_total_len;
}
void remove_sequence(int ***collection_ptr, int **lengths_ptr, int *num_sequences_ptr, int *capacity_ptr, int index) {
    if (index < 0 || index >= *num_sequences_ptr) {
        return;
    }
    free((*collection_ptr)[index]);
    for (int i = index; i < *num_sequences_ptr - 1; i++) {
        (*collection_ptr)[i] = (*collection_ptr)[i+1];
        (*lengths_ptr)[i] = (*lengths_ptr)[i+1];
    }
    (*num_sequences_ptr)--;
    if (*num_sequences_ptr > 0 && *num_sequences_ptr < *capacity_ptr / 4 && *capacity_ptr > 2) {
        *capacity_ptr /= 2;
        *collection_ptr = (int **)realloc(*collection_ptr, *capacity_ptr * sizeof(int *));
        *lengths_ptr = (int *)realloc(*lengths_ptr, *capacity_ptr * sizeof(int));
    } else if (*num_sequences_ptr == 0 && *capacity_ptr > 0) {
        free(*collection_ptr);
        free(*lengths_ptr);
        *collection_ptr = NULL;
        *lengths_ptr = NULL;
        *capacity_ptr = 0;
    }
}
void print_collection(int **collection, int *lengths, int num_sequences) {
    printf("--- Current Collection (%d sequences) ---\n", num_sequences);
    for (int i = 0; i < num_sequences; i++) {
        printf("Sequence %d (length %d): [", i, lengths[i]);
        for (int j = 0; j < lengths[i]; j++) {
            printf("%d%s", collection[i][j], (j == lengths[i] - 1) ? "" : ", ");
        }
        printf("]\n");
    }
    printf("----------------------------------------\n");
}
void free_collection(int ***collection_ptr, int **lengths_ptr, int *num_sequences_ptr, int *capacity_ptr) {
    for (int i = 0; i < *num_sequences_ptr; i++) {
        free((*collection_ptr)[i]);
    }
    free(*collection_ptr);
    free(*lengths_ptr);
    *collection_ptr = NULL;
    *lengths_ptr = NULL;
    *num_sequences_ptr = 0;
    *capacity_ptr = 0;
}
int main() {
    int **sequences = NULL;
    int *sequence_lengths = NULL;
    int num_sequences = 0;
    int collection_capacity = 0;
    initialize_collection(&sequences, &sequence_lengths, &num_sequences, &collection_capacity);
    int data1[] = {10, 20, 30};
    int data2[] = {5, 15};
    int data3[] = {100, 200, 300, 400};
    int data4[] = {1, 2, 3, 4, 5};
    add_sequence(&sequences, &sequence_lengths, &num_sequences, &collection_capacity, data1, 3);
    print_collection(sequences, sequence_lengths, num_sequences);
    add_sequence(&sequences, &sequence_lengths, &num_sequences, &collection_capacity, data2, 2);
    print_collection(sequences, sequence_lengths, num_sequences);
    int new_data_seq0[] = {35, 40};
    extend_sequence(sequences, sequence_lengths, 0, new_data_seq0, 2);
    print_collection(sequences, sequence_lengths, num_sequences);
    add_sequence(&sequences, &sequence_lengths, &num_sequences, &collection_capacity, data3, 4);
    print_collection(sequences, sequence_lengths, num_sequences);
    remove_sequence(&sequences, &sequence_lengths, &num_sequences, &collection_capacity, 1); 
    print_collection(sequences, sequence_lengths, num_sequences);
    add_sequence(&sequences, &sequence_lengths, &num_sequences, &collection_capacity, data4, 5);
    print_collection(sequences, sequence_lengths, num_sequences);
    remove_sequence(&sequences, &sequence_lengths, &num_sequences, &collection_capacity, 0); 
    print_collection(sequences, sequence_lengths, num_sequences);
    remove_sequence(&sequences, &sequence_lengths, &num_sequences, &collection_capacity, 0); 
    print_collection(sequences, sequence_lengths, num_sequences);
    remove_sequence(&sequences, &sequence_lengths, &num_sequences, &collection_capacity, 0); 
    print_collection(sequences, sequence_lengths, num_sequences);
    free_collection(&sequences, &sequence_lengths, &num_sequences, &collection_capacity);
    return 0;
}