#include <stdio.h>
#include <stdlib.h>
#define INITIAL_MAIN_CAPACITY 2
#define INITIAL_SEQUENCE_CAPACITY 2
int main() {
    int** sequences = NULL;
    int* seq_sizes = NULL;
    int* seq_capacities = NULL;
    int num_sequences = 0;
    int main_capacity = 0;
    int return_code = 0;
    main_capacity = INITIAL_MAIN_CAPACITY;
    sequences = (int**)malloc(main_capacity * sizeof(int*));
    if (sequences == NULL) {
        fprintf(stderr, "Error: Initial memory allocation for sequences failed.\n");
        return_code = 1;
        goto cleanup;
    }
    seq_sizes = (int*)malloc(main_capacity * sizeof(int));
    if (seq_sizes == NULL) {
        fprintf(stderr, "Error: Initial memory allocation for seq_sizes failed.\n");
        return_code = 1;
        goto cleanup;
    }
    seq_capacities = (int*)malloc(main_capacity * sizeof(int));
    if (seq_capacities == NULL) {
        fprintf(stderr, "Error: Initial memory allocation for seq_capacities failed.\n");
        return_code = 1;
        goto cleanup;
    }
    if (num_sequences == main_capacity) {
        int new_main_capacity = main_capacity * 2;
        int** new_sequences = (int**)realloc(sequences, new_main_capacity * sizeof(int*));
        if (new_sequences == NULL) { fprintf(stderr, "Error: Reallocation for sequences failed.\n"); return_code = 1; goto cleanup; }
        sequences = new_sequences;
        int* new_seq_sizes = (int*)realloc(seq_sizes, new_main_capacity * sizeof(int));
        if (new_seq_sizes == NULL) { fprintf(stderr, "Error: Reallocation for seq_sizes failed.\n"); return_code = 1; goto cleanup; }
        seq_sizes = new_seq_sizes;
        int* new_seq_capacities = (int*)realloc(seq_capacities, new_main_capacity * sizeof(int));
        if (new_seq_capacities == NULL) { fprintf(stderr, "Error: Reallocation for seq_capacities failed.\n"); return_code = 1; goto cleanup; }
        seq_capacities = new_seq_capacities;
        main_capacity = new_main_capacity;
    }
    sequences[num_sequences] = (int*)malloc(INITIAL_SEQUENCE_CAPACITY * sizeof(int));
    if (sequences[num_sequences] == NULL) { fprintf(stderr, "Error: Malloc for new sequence 0 failed.\n"); return_code = 1; goto cleanup; }
    sequences[num_sequences][0] = 10;
    seq_sizes[num_sequences] = 1;
    seq_capacities[num_sequences] = INITIAL_SEQUENCE_CAPACITY;
    num_sequences++;
    if (num_sequences == main_capacity) {
        int new_main_capacity = main_capacity * 2;
        int** new_sequences = (int**)realloc(sequences, new_main_capacity * sizeof(int*));
        if (new_sequences == NULL) { fprintf(stderr, "Error: Reallocation for sequences failed.\n"); return_code = 1; goto cleanup; }
        sequences = new_sequences;
        int* new_seq_sizes = (int*)realloc(seq_sizes, new_main_capacity * sizeof(int));
        if (new_seq_sizes == NULL) { fprintf(stderr, "Error: Reallocation for seq_sizes failed.\n"); return_code = 1; goto cleanup; }
        seq_sizes = new_seq_sizes;
        int* new_seq_capacities = (int*)realloc(seq_capacities, new_main_capacity * sizeof(int));
        if (new_seq_capacities == NULL) { fprintf(stderr, "Error: Reallocation for seq_capacities failed.\n"); return_code = 1; goto cleanup; }
        seq_capacities = new_seq_capacities;
        main_capacity = new_main_capacity;
    }
    sequences[num_sequences] = (int*)malloc(INITIAL_SEQUENCE_CAPACITY * sizeof(int));
    if (sequences[num_sequences] == NULL) { fprintf(stderr, "Error: Malloc for new sequence 1 failed.\n"); return_code = 1; goto cleanup; }
    sequences[num_sequences][0] = 20;
    seq_sizes[num_sequences] = 1;
    seq_capacities[num_sequences] = INITIAL_SEQUENCE_CAPACITY;
    num_sequences++;
    int target_seq_idx_0 = 0;
    if (target_seq_idx_0 >= num_sequences) { fprintf(stderr, "Error: Invalid sequence index.\n"); return_code = 1; goto cleanup; }
    if (seq_sizes[target_seq_idx_0] == seq_capacities[target_seq_idx_0]) {
        int new_seq_capacity = seq_capacities[target_seq_idx_0] * 2;
        int* new_inner_seq = (int*)realloc(sequences[target_seq_idx_0], new_seq_capacity * sizeof(int));
        if (new_inner_seq == NULL) { fprintf(stderr, "Error: Reallocation for inner sequence %d failed.\n", target_seq_idx_0); return_code = 1; goto cleanup; }
        sequences[target_seq_idx_0] = new_inner_seq;
        seq_capacities[target_seq_idx_0] = new_seq_capacity;
    }
    sequences[target_seq_idx_0][seq_sizes[target_seq_idx_0]] = 11;
    seq_sizes[target_seq_idx_0]++;
    if (seq_sizes[target_seq_idx_0] == seq_capacities[target_seq_idx_0]) {
        int new_seq_capacity = seq_capacities[target_seq_idx_0] * 2;
        int* new_inner_seq = (int*)realloc(sequences[target_seq_idx_0], new_seq_capacity * sizeof(int));
        if (new_inner_seq == NULL) { fprintf(stderr, "Error: Reallocation for inner sequence %d failed.\n", target_seq_idx_0); return_code = 1; goto cleanup; }
        sequences[target_seq_idx_0] = new_inner_seq;
        seq_capacities[target_seq_idx_0] = new_seq_capacity;
    }
    sequences[target_seq_idx_0][seq_sizes[target_seq_idx_0]] = 12;
    seq_sizes[target_seq_idx_0]++;
    int target_seq_idx_1 = 1;
    if (target_seq_idx_1 >= num_sequences) { fprintf(stderr, "Error: Invalid sequence index.\n"); return_code = 1; goto cleanup; }
    if (seq_sizes[target_seq_idx_1] == seq_capacities[target_seq_idx_1]) {
        int new_seq_capacity = seq_capacities[target_seq_idx_1] * 2;
        int* new_inner_seq = (int*)realloc(sequences[target_seq_idx_1], new_seq_capacity * sizeof(int));
        if (new_inner_seq == NULL) { fprintf(stderr, "Error: Reallocation for inner sequence %d failed.\n", target_seq_idx_1); return_code = 1; goto cleanup; }
        sequences[target_seq_idx_1] = new_inner_seq;
        seq_capacities[target_seq_idx_1] = new_seq_capacity;
    }
    sequences[target_seq_idx_1][seq_sizes[target_seq_idx_1]] = 21;
    seq_sizes[target_seq_idx_1]++;
    if (seq_sizes[target_seq_idx_1] == seq_capacities[target_seq_idx_1]) {
        int new_seq_capacity = seq_capacities[target_seq_idx_1] * 2;
        int* new_inner_seq = (int*)realloc(sequences[target_seq_idx_1], new_seq_capacity * sizeof(int));
        if (new_inner_seq == NULL) { fprintf(stderr, "Error: Reallocation for inner sequence %d failed.\n", target_seq_idx_1); return_code = 1; goto cleanup; }
        sequences[target_seq_idx_1] = new_inner_seq;
        seq_capacities[target_seq_idx_1] = new_seq_capacity;
    }
    sequences[target_seq_idx_1][seq_sizes[target_seq_idx_1]] = 22;
    seq_sizes[target_seq_idx_1]++;
    if (num_sequences == main_capacity) {
        int new_main_capacity = main_capacity * 2;
        int** new_sequences = (int**)realloc(sequences, new_main_capacity * sizeof(int*));
        if (new_sequences == NULL) { fprintf(stderr, "Error: Reallocation for sequences failed.\n"); return_code = 1; goto cleanup; }
        sequences = new_sequences;
        int* new_seq_sizes = (int*)realloc(seq_sizes, new_main_capacity * sizeof(int));
        if (new_seq_sizes == NULL) { fprintf(stderr, "Error: Reallocation for seq_sizes failed.\n"); return_code = 1; goto cleanup; }
        seq_sizes = new_seq_sizes;
        int* new_seq_capacities = (int*)realloc(seq_capacities, new_main_capacity * sizeof(int));
        if (new_seq_capacities == NULL) { fprintf(stderr, "Error: Reallocation for seq_capacities failed.\n"); return_code = 1; goto cleanup; }
        seq_capacities = new_seq_capacities;
        main_capacity = new_main_capacity;
    }
    sequences[num_sequences] = (int*)malloc(INITIAL_SEQUENCE_CAPACITY * sizeof(int));
    if (sequences[num_sequences] == NULL) { fprintf(stderr, "Error: Malloc for new sequence 2 failed.\n"); return_code = 1; goto cleanup; }
    sequences[num_sequences][0] = 30;
    seq_sizes[num_sequences] = 1;
    seq_capacities[num_sequences] = INITIAL_SEQUENCE_CAPACITY;
    num_sequences++;
    printf("State before removal:\n");
    for (int i = 0; i < num_sequences; i++) {
        printf("  Sequence %d (size %d, capacity %d): ", i, seq_sizes[i], seq_capacities[i]);
        for (int j = 0; j < seq_sizes[i]; j++) {
            printf("%d ", sequences[i][j]);
        }
        printf("\n");
    }
    int remove_idx = 0;
    if (remove_idx < 0 || remove_idx >= num_sequences) { 
        fprintf(stderr, "Error: Invalid index for removal.\n"); 
        return_code = 1; 
        goto cleanup; 
    }
    free(sequences[remove_idx]); 
    for (int i = remove_idx; i < num_sequences - 1; i++) {
        sequences[i] = sequences[i+1];
        seq_sizes[i] = seq_sizes[i+1];
        seq_capacities[i] = seq_capacities[i+1];
    }
    num_sequences--;
    if (num_sequences > INITIAL_MAIN_CAPACITY && num_sequences < main_capacity / 2) {
        int new_main_capacity = main_capacity / 2;
        int** new_sequences = (int**)realloc(sequences, new_main_capacity * sizeof(int*));
        if (new_sequences == NULL) { fprintf(stderr, "Error: Shrink reallocation for sequences failed.\n"); return_code = 1; goto cleanup; }
        sequences = new_sequences;
        int* new_seq_sizes = (int*)realloc(seq_sizes, new_main_capacity * sizeof(int));
        if (new_seq_sizes == NULL) { fprintf(stderr, "Error: Shrink reallocation for seq_sizes failed.\n"); return_code = 1; goto cleanup; }
        seq_sizes = new_seq_sizes;
        int* new_seq_capacities = (int*)realloc(seq_capacities, new_main_capacity * sizeof(int));
        if (new_seq_capacities == NULL) { fprintf(stderr, "Error: Shrink reallocation for seq_capacities failed.\n"); return_code = 1; goto cleanup; }
        seq_capacities = new_seq_capacities;
        main_capacity = new_main_capacity;
    }
    printf("\nState after removing sequence %d:\n", remove_idx);
    for (int i = 0; i < num_sequences; i++) {
        printf("  Sequence %d (size %d, capacity %d): ", i, seq_sizes[i], seq_capacities[i]);
        for (int j = 0; j < seq_sizes[i]; j++) {
            printf("%d ", sequences[i][j]);
        }
        printf("\n");
    }
cleanup:
    for (int i = 0; i < num_sequences; i++) {
        if (sequences != NULL && sequences[i] != NULL) {
            free(sequences[i]);
        }
    }
    if (sequences != NULL) free(sequences);
    if (seq_sizes != NULL) free(seq_sizes);
    if (seq_capacities != NULL) free(seq_capacities);
    return return_code;
}