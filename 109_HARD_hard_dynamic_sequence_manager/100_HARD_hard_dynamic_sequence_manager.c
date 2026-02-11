#include <stdio.h>
#include <stdlib.h>
#define INITIAL_MANAGER_CAPACITY 2
#define INITIAL_SEQUENCE_CAPACITY 4
#define RESIZE_FACTOR 2
int main() {
    int **sequences = NULL;
    int *sequence_sizes = NULL;
    int *sequence_capacities = NULL;
    int num_active_sequences = 0;
    int manager_capacity = INITIAL_MANAGER_CAPACITY;
    sequences = (int **)malloc(manager_capacity * sizeof(int *));
    sequence_sizes = (int *)malloc(manager_capacity * sizeof(int));
    sequence_capacities = (int *)malloc(manager_capacity * sizeof(int));
    if (!sequences || !sequence_sizes || !sequence_capacities) {
        fprintf(stderr, "Initial manager allocation failed\n");
        if (sequences) free(sequences);
        if (sequence_sizes) free(sequence_sizes);
        if (sequence_capacities) free(sequence_capacities);
        return 1;
    }
    printf("Manager initialized with capacity %d.\n", manager_capacity);
    for (int k = 0; k < 3; k++) {
        if (num_active_sequences == manager_capacity) {
            int new_manager_capacity = manager_capacity * RESIZE_FACTOR;
            int **temp_seq = (int **)realloc(sequences, new_manager_capacity * sizeof(int *));
            int *temp_sizes = (int *)realloc(sequence_sizes, new_manager_capacity * sizeof(int));
            int *temp_caps = (int *)realloc(sequence_capacities, new_manager_capacity * sizeof(int));
            if (!temp_seq || !temp_sizes || !temp_caps) {
                fprintf(stderr, "Manager realloc failed for adding sequence %d\n", k);
                for (int i = 0; i < num_active_sequences; i++) free(sequences[i]);
                free(sequences);
                free(sequence_sizes);
                free(sequence_capacities);
                return 1;
            }
            sequences = temp_seq;
            sequence_sizes = temp_sizes;
            sequence_capacities = temp_caps;
            manager_capacity = new_manager_capacity;
            printf("Manager reallocated to capacity %d.\n", manager_capacity);
        }
        sequences[num_active_sequences] = (int *)malloc(INITIAL_SEQUENCE_CAPACITY * sizeof(int));
        if (!sequences[num_active_sequences]) {
            fprintf(stderr, "Sequence %d initial allocation failed\n", num_active_sequences);
            for (int i = 0; i < num_active_sequences; i++) free(sequences[i]);
            free(sequences);
            free(sequence_sizes);
            free(sequence_capacities);
            return 1;
        }
        sequence_sizes[num_active_sequences] = 0;
        sequence_capacities[num_active_sequences] = INITIAL_SEQUENCE_CAPACITY;
        printf("Added sequence %d with initial capacity %d.\n", num_active_sequences, INITIAL_SEQUENCE_CAPACITY);
        num_active_sequences++;
    }
    for (int k = 0; k < num_active_sequences; k++) {
        int num_elements_to_add = 5 + k * 2;
        for (int val = 0; val < num_elements_to_add; val++) {
            int seq_idx = k;
            if (sequence_sizes[seq_idx] == sequence_capacities[seq_idx]) {
                int new_capacity = sequence_capacities[seq_idx] * RESIZE_FACTOR;
                int *temp = (int *)realloc(sequences[seq_idx], new_capacity * sizeof(int));
                if (!temp) {
                    fprintf(stderr, "Sequence %d realloc failed when adding %d\n", seq_idx, val);
                    for (int i = 0; i < num_active_sequences; i++) free(sequences[i]);
                    free(sequences);
                    free(sequence_sizes);
                    free(sequence_capacities);
                    return 1;
                }
                sequences[seq_idx] = temp;
                sequence_capacities[seq_idx] = new_capacity;
                printf("Sequence %d reallocated to capacity %d.\n", seq_idx, new_capacity);
            }
            sequences[seq_idx][sequence_sizes[seq_idx]] = val + (seq_idx * 100);
            sequence_sizes[seq_idx]++;
        }
    }
    printf("\nCurrent Sequences:\n");
    for (int i = 0; i < num_active_sequences; i++) {
        printf("Seq %d (size %d, cap %d): ", i, sequence_sizes[i], sequence_capacities[i]);
        for (int j = 0; j < sequence_sizes[i]; j++) {
            printf("%d ", sequences[i][j]);
        }
        printf("\n");
    }
    int merge_target_idx = 0;
    int merge_source_idx = 1;
    if (num_active_sequences > 1 && merge_target_idx != merge_source_idx &&
        merge_target_idx >= 0 && merge_target_idx < num_active_sequences &&
        merge_source_idx >= 0 && merge_source_idx < num_active_sequences) {
        printf("\nMerging sequence %d into sequence %d...\n", merge_source_idx, merge_target_idx);
        int new_total_size = sequence_sizes[merge_target_idx] + sequence_sizes[merge_source_idx];
        int new_target_capacity = sequence_capacities[merge_target_idx];
        while (new_target_capacity < new_total_size) {
            new_target_capacity *= RESIZE_FACTOR;
        }
        int *temp_new_sequence = (int *)realloc(sequences[merge_target_idx], new_target_capacity * sizeof(int));
        if (!temp_new_sequence) {
            fprintf(stderr, "Merge realloc for target sequence %d failed\n", merge_target_idx);
            for (int i = 0; i < num_active_sequences; i++) free(sequences[i]);
            free(sequences);
            free(sequence_sizes);
            free(sequence_capacities);
            return 1;
        }
        sequences[merge_target_idx] = temp_new_sequence;
        for (int i = 0; i < sequence_sizes[merge_source_idx]; i++) {
            sequences[merge_target_idx][sequence_sizes[merge_target_idx] + i] = sequences[merge_source_idx][i];
        }
        sequence_sizes[merge_target_idx] = new_total_size;
        sequence_capacities[merge_target_idx] = new_target_capacity;
        printf("Sequence %d merged into %d.\n", merge_source_idx, merge_target_idx);
        free(sequences[merge_source_idx]);
        printf("Freed original sequence %d data.\n", merge_source_idx);
        for (int i = merge_source_idx; i < num_active_sequences - 1; i++) {
            sequences[i] = sequences[i + 1];
            sequence_sizes[i] = sequence_sizes[i + 1];
            sequence_capacities[i] = sequence_capacities[i + 1];
        }
        num_active_sequences--;
        printf("Shifted remaining sequences. Num active sequences: %d.\n", num_active_sequences);
        if (num_active_sequences < manager_capacity / RESIZE_FACTOR && manager_capacity > INITIAL_MANAGER_CAPACITY) {
            int new_manager_capacity = manager_capacity / RESIZE_FACTOR;
            int **temp_seq = (int **)realloc(sequences, new_manager_capacity * sizeof(int *));
            int *temp_sizes = (int *)realloc(sequence_sizes, new_manager_capacity * sizeof(int));
            int *temp_caps = (int *)realloc(sequence_capacities, new_manager_capacity * sizeof(int));
            if (!temp_seq || !temp_sizes || !temp_caps) {
                fprintf(stderr, "Manager realloc (shrink) failed.\n");
                for (int i = 0; i < num_active_sequences; i++) free(sequences[i]);
                free(sequences);
                free(sequence_sizes);
                free(sequence_capacities);
                return 1;
            }
            sequences = temp_seq;
            sequence_sizes = temp_sizes;
            sequence_capacities = temp_caps;
            manager_capacity = new_manager_capacity;
            printf("Manager reallocated (shrunk) to capacity %d.\n", manager_capacity);
        }
    } else {
        printf("Merge operation skipped. Conditions not met or indices invalid.\n");
    }
    printf("\nFinal Sequences:\n");
    for (int i = 0; i < num_active_sequences; i++) {
        printf("Seq %d (size %d, cap %d): ", i, sequence_sizes[i], sequence_capacities[i]);
        for (int j = 0; j < sequence_sizes[i]; j++) {
            printf("%d ", sequences[i][j]);
        }
        printf("\n");
    }
    printf("\nCleaning up all dynamically allocated memory...\n");
    for (int i = 0; i < num_active_sequences; i++) {
        free(sequences[i]);
    }
    free(sequences);
    free(sequence_sizes);
    free(sequence_capacities);
    printf("Cleanup complete.\n");
    return 0;
}