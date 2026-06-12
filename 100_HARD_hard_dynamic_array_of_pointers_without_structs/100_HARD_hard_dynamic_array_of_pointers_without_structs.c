#include <stdio.h>
#include <stdlib.h>
void add_sequence(int*** manager_ptr, int** sizes_ptr, int* current_count_ptr, int* capacity_ptr) {
    if (*current_count_ptr == *capacity_ptr) {
        int new_capacity = (*capacity_ptr == 0) ? 2 : (*capacity_ptr * 2);
        int** new_manager = (int**)realloc(*manager_ptr, new_capacity * sizeof(int*));
        if (!new_manager) {
            fprintf(stderr, "Failed to reallocate sequence_manager.\n");
            exit(EXIT_FAILURE);
        }
        *manager_ptr = new_manager;
        int* new_sizes = (int*)realloc(*sizes_ptr, new_capacity * sizeof(int));
        if (!new_sizes) {
            fprintf(stderr, "Failed to reallocate sequence_sizes.\n");
            exit(EXIT_FAILURE);
        }
        *sizes_ptr = new_sizes;
        *capacity_ptr = new_capacity;
    }
    (*manager_ptr)[*current_count_ptr] = NULL;
    (*sizes_ptr)[*current_count_ptr] = 0;
    (*current_count_ptr)++;
}
void append_to_sequence(int*** manager_ptr, int** sizes_ptr, int sequence_idx, int value, int current_count) {
    if (sequence_idx < 0 || sequence_idx >= current_count) {
        fprintf(stderr, "Invalid sequence index for append.\n");
        return;
    }
    int current_size = (*sizes_ptr)[sequence_idx];
    int* current_sequence = (*manager_ptr)[sequence_idx];
    int* new_sequence = (int*)realloc(current_sequence, (current_size + 1) * sizeof(int));
    if (!new_sequence) {
        fprintf(stderr, "Failed to reallocate individual sequence.\n");
        exit(EXIT_FAILURE);
    }
    new_sequence[current_size] = value;
    (*manager_ptr)[sequence_idx] = new_sequence;
    (*sizes_ptr)[sequence_idx]++;
}
void remove_sequence(int*** manager_ptr, int** sizes_ptr, int* current_count_ptr, int* capacity_ptr, int sequence_idx) {
    if (sequence_idx < 0 || sequence_idx >= *current_count_ptr) {
        fprintf(stderr, "Invalid sequence index for removal.\n");
        return;
    }
    free((*manager_ptr)[sequence_idx]);
    for (int i = sequence_idx; i < *current_count_ptr - 1; i++) {
        (*manager_ptr)[i] = (*manager_ptr)[i + 1];
        (*sizes_ptr)[i] = (*sizes_ptr)[i + 1];
    }
    (*current_count_ptr)--;
    if (*current_count_ptr == 0) {
        free(*manager_ptr);
        *manager_ptr = NULL;
        free(*sizes_ptr);
        *sizes_ptr = NULL;
        *capacity_ptr = 0;
    } else if (*current_count_ptr > 0 && *current_count_ptr <= *capacity_ptr / 4) {
        int new_capacity = *capacity_ptr / 2;
        if (new_capacity < 2) new_capacity = 2;
        int** new_manager = (int**)realloc(*manager_ptr, new_capacity * sizeof(int*));
        if (!new_manager) {
            fprintf(stderr, "Failed to shrink sequence_manager.\n");
            exit(EXIT_FAILURE);
        }
        *manager_ptr = new_manager;
        int* new_sizes = (int*)realloc(*sizes_ptr, new_capacity * sizeof(int));
        if (!new_sizes) {
            fprintf(stderr, "Failed to shrink sequence_sizes.\n");
            exit(EXIT_FAILURE);
        }
        *sizes_ptr = new_sizes;
        *capacity_ptr = new_capacity;
    }
}
int main() {
    int** sequence_manager = NULL;
    int* sequence_sizes = NULL;
    int current_num_sequences = 0;
    int capacity_num_sequences = 0;
    add_sequence(&sequence_manager, &sequence_sizes, &current_num_sequences, &capacity_num_sequences);
    add_sequence(&sequence_manager, &sequence_sizes, &current_num_sequences, &capacity_num_sequences);
    add_sequence(&sequence_manager, &sequence_sizes, &current_num_sequences, &capacity_num_sequences);
    append_to_sequence(&sequence_manager, &sequence_sizes, 0, 10, current_num_sequences);
    append_to_sequence(&sequence_manager, &sequence_sizes, 0, 20, current_num_sequences);
    append_to_sequence(&sequence_manager, &sequence_sizes, 1, 30, current_num_sequences);
    append_to_sequence(&sequence_manager, &sequence_sizes, 0, 40, current_num_sequences);
    append_to_sequence(&sequence_manager, &sequence_sizes, 2, 50, current_num_sequences);
    append_to_sequence(&sequence_manager, &sequence_sizes, 1, 60, current_num_sequences);
    printf("Sequences after additions:\n");
    for (int i = 0; i < current_num_sequences; i++) {
        printf("  Sequence %d (size %d): ", i, sequence_sizes[i]);
        for (int j = 0; j < sequence_sizes[i]; j++) {
            printf("%d ", sequence_manager[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    remove_sequence(&sequence_manager, &sequence_sizes, &current_num_sequences, &capacity_num_sequences, 1);
    printf("Sequences after removing index 1:\n");
    for (int i = 0; i < current_num_sequences; i++) {
        printf("  Sequence %d (size %d): ", i, sequence_sizes[i]);
        for (int j = 0; j < sequence_sizes[i]; j++) {
            printf("%d ", sequence_manager[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    add_sequence(&sequence_manager, &sequence_sizes, &current_num_sequences, &capacity_num_sequences);
    append_to_sequence(&sequence_manager, &sequence_sizes, 2, 70, current_num_sequences);
    append_to_sequence(&sequence_manager, &sequence_sizes, 2, 80, current_num_sequences);
    printf("Sequences after adding another and appending:\n");
    for (int i = 0; i < current_num_sequences; i++) {
        printf("  Sequence %d (size %d): ", i, sequence_sizes[i]);
        for (int j = 0; j < sequence_sizes[i]; j++) {
            printf("%d ", sequence_manager[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < current_num_sequences; i++) {
        free(sequence_manager[i]);
    }
    free(sequence_manager);
    free(sequence_sizes);
    return 0;
}