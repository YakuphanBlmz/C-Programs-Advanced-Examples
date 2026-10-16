#include <stdio.h>
#include <stdlib.h>
int main() {
    int **sequences = NULL;
    int *sequence_lengths = NULL;
    int *sequence_capacities = NULL;
    int num_sequences = 0;
    int manager_capacity = 0;
    int i, j;
    for (i = 0; i < 3; i++) {
        if (num_sequences == manager_capacity) {
            manager_capacity = (manager_capacity == 0) ? 1 : manager_capacity * 2;
            sequences = (int **)realloc(sequences, manager_capacity * sizeof(int *));
            sequence_lengths = (int *)realloc(sequence_lengths, manager_capacity * sizeof(int));
            sequence_capacities = (int *)realloc(sequence_capacities, manager_capacity * sizeof(int));
            if (!sequences || !sequence_lengths || !sequence_capacities) {
                fprintf(stderr, "Manager realloc failed\n");
                return 1;
            }
        }
        sequences[num_sequences] = NULL;
        sequence_lengths[num_sequences] = 0;
        sequence_capacities[num_sequences] = 0;
        for (j = 0; j <= i + 1; j++) {
            int current_seq_idx = num_sequences;
            if (sequence_lengths[current_seq_idx] == sequence_capacities[current_seq_idx]) {
                sequence_capacities[current_seq_idx] = (sequence_capacities[current_seq_idx] == 0) ? 2 : sequence_capacities[current_seq_idx] * 2;
                sequences[current_seq_idx] = (int *)realloc(sequences[current_seq_idx], sequence_capacities[current_seq_idx] * sizeof(int));
                if (!sequences[current_seq_idx]) {
                    fprintf(stderr, "Sequence realloc failed\n");
                    return 1;
                }
            }
            sequences[current_seq_idx][sequence_lengths[current_seq_idx]++] = (i * 10) + j;
        }
        num_sequences++;
    }
    for (i = 0; i < 2; i++) {
        if (num_sequences == manager_capacity) {
            manager_capacity *= 2;
            sequences = (int **)realloc(sequences, manager_capacity * sizeof(int *));
            sequence_lengths = (int *)realloc(sequence_lengths, manager_capacity * sizeof(int));
            sequence_capacities = (int *)realloc(sequence_capacities, manager_capacity * sizeof(int));
            if (!sequences || !sequence_lengths || !sequence_capacities) {
                fprintf(stderr, "Manager realloc failed during expansion\n");
                return 1;
            }
        }
        sequences[num_sequences] = NULL;
        sequence_lengths[num_sequences] = 0;
        sequence_capacities[num_sequences] = 0;
        for (j = 0; j < 3; j++) {
            int current_seq_idx = num_sequences;
            if (sequence_lengths[current_seq_idx] == sequence_capacities[current_seq_idx]) {
                sequence_capacities[current_seq_idx] = (sequence_capacities[current_seq_idx] == 0) ? 2 : sequence_capacities[current_seq_idx] * 2;
                sequences[current_seq_idx] = (int *)realloc(sequences[current_seq_idx], sequence_capacities[current_seq_idx] * sizeof(int));
                if (!sequences[current_seq_idx]) {
                    fprintf(stderr, "Sequence realloc failed\n");
                    return 1;
                }
            }
            sequences[current_seq_idx][sequence_lengths[current_seq_idx]++] = 100 + (num_sequences * 10) + j;
        }
        num_sequences++;
    }
    printf("\n--- Managed Sequences ---\n");
    for (i = 0; i < num_sequences; i++) {
        printf("Sequence %d (Length: %d, Capacity: %d): ", i, sequence_lengths[i], sequence_capacities[i]);
        for (j = 0; j < sequence_lengths[i]; j++) {
            printf("%d ", sequences[i][j]);
        }
        printf("\n");
    }
    for (i = 0; i < num_sequences; i++) {
        free(sequences[i]);
        sequences[i] = NULL;
    }
    free(sequences);
    free(sequence_lengths);
    free(sequence_capacities);
    sequences = NULL;
    sequence_lengths = NULL;
    sequence_capacities = NULL;
    printf("\nAll memory freed successfully.\n");
    return 0;
}