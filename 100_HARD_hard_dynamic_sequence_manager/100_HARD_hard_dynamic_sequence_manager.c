#include <stdio.h>
#include <stdlib.h>
int main() {
    int **sequences = NULL;
    int *sequence_current_counts = NULL;
    int *sequence_capacities = NULL;
    int num_sequences = 0;
    int initial_num_sequences_to_create = 3;
    sequences = (int**)malloc(initial_num_sequences_to_create * sizeof(int*));
    sequence_current_counts = (int*)malloc(initial_num_sequences_to_create * sizeof(int));
    sequence_capacities = (int*)malloc(initial_num_sequences_to_create * sizeof(int));
    num_sequences = initial_num_sequences_to_create;
    for (int i = 0; i < num_sequences; i++) {
        int initial_capacity = (i + 1) * 3; 
        sequences[i] = (int*)malloc(initial_capacity * sizeof(int));
        sequence_current_counts[i] = 0; 
        sequence_capacities[i] = initial_capacity;
        for (int j = 0; j < initial_capacity / 2; j++) {
            sequences[i][j] = (i * 100) + j + 1;
            sequence_current_counts[i]++;
        }
    }
    int new_num_sequences_after_add = num_sequences + 1;
    sequences = (int**)realloc(sequences, new_num_sequences_after_add * sizeof(int*));
    sequence_current_counts = (int*)realloc(sequence_current_counts, new_num_sequences_after_add * sizeof(int));
    sequence_capacities = (int*)realloc(sequence_capacities, new_num_sequences_after_add * sizeof(int));
    int new_sequence_idx = num_sequences;
    int new_sequence_initial_capacity = 6;
    sequences[new_sequence_idx] = (int*)malloc(new_sequence_initial_capacity * sizeof(int));
    sequence_current_counts[new_sequence_idx] = 0;
    sequence_capacities[new_sequence_idx] = new_sequence_initial_capacity;
    for (int j = 0; j < new_sequence_initial_capacity - 2; j++) {
        sequences[new_sequence_idx][j] = (new_sequence_idx * 1000) + j + 50;
        sequence_current_counts[new_sequence_idx]++;
    }
    num_sequences = new_num_sequences_after_add;
    int target_sequence_to_expand_idx = 0;
    int new_expanded_capacity = sequence_capacities[target_sequence_to_expand_idx] * 2;
    sequences[target_sequence_to_expand_idx] = (int*)realloc(sequences[target_sequence_to_expand_idx], new_expanded_capacity * sizeof(int));
    sequence_capacities[target_sequence_to_expand_idx] = new_expanded_capacity;
    for (int j = sequence_current_counts[target_sequence_to_expand_idx]; j < new_expanded_capacity - 1; j++) {
        sequences[target_sequence_to_expand_idx][j] = (target_sequence_to_expand_idx * 10000) + j + 777;
        sequence_current_counts[target_sequence_to_expand_idx]++;
    }
    int total_elements_for_consolidation = 0;
    for (int i = 0; i < num_sequences; i++) {
        total_elements_for_consolidation += sequence_current_counts[i];
    }
    int *consolidated_sequence = (int*)malloc(total_elements_for_consolidation * sizeof(int));
    int current_consolidated_idx = 0;
    for (int i = 0; i < num_sequences; i++) {
        for (int j = 0; j < sequence_current_counts[i]; j++) {
            consolidated_sequence[current_consolidated_idx++] = sequences[i][j];
        }
    }
    for (int i = 0; i < num_sequences; i++) {
        free(sequences[i]);
    }
    free(sequences);
    free(sequence_current_counts);
    free(sequence_capacities);
    printf("Consolidated Sequence (%d elements):\n", total_elements_for_consolidation);
    for (int i = 0; i < total_elements_for_consolidation; i++) {
        printf("%d ", consolidated_sequence[i]);
    }
    printf("\n");
    free(consolidated_sequence);
    return 0;
}