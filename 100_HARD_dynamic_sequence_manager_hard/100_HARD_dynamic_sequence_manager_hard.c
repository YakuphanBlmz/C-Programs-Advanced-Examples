#include <stdio.h>
#include <stdlib.h>
void reverse_sequence(int** sequences, int sequence_idx, int* lengths) {
    if (sequences == NULL || lengths == NULL) return;
    int* seq = sequences[sequence_idx];
    int len = lengths[sequence_idx];
    int start = 0;
    int end = len - 1;
    while (start < end) {
        int temp = seq[start];
        seq[start] = seq[end];
        seq[end] = temp;
        start++;
        end--;
    }
}
int merge_and_add_sequence(int*** sequences_ptr, int** lengths_ptr, int* num_sequences_ptr, int idx1, int idx2) {
    if (*sequences_ptr == NULL || *lengths_ptr == NULL || num_sequences_ptr == NULL) return -1;
    if (idx1 < 0 || idx1 >= *num_sequences_ptr || idx2 < 0 || idx2 >= *num_sequences_ptr) return -1;
    int* seq1 = (*sequences_ptr)[idx1];
    int len1 = (*lengths_ptr)[idx1];
    int* seq2 = (*sequences_ptr)[idx2];
    int len2 = (*lengths_ptr)[idx2];
    int new_len = len1 + len2;
    int* new_seq = (int*)malloc(new_len * sizeof(int));
    if (new_seq == NULL) return -1;
    for (int i = 0; i < len1; i++) {
        new_seq[i] = seq1[i];
    }
    for (int i = 0; i < len2; i++) {
        new_seq[len1 + i] = seq2[i];
    }
    int new_num_sequences = *num_sequences_ptr + 1;
    int** temp_sequences = (int**)realloc(*sequences_ptr, new_num_sequences * sizeof(int*));
    if (temp_sequences == NULL) {
        free(new_seq);
        return -1;
    }
    *sequences_ptr = temp_sequences;
    int* temp_lengths = (int*)realloc(*lengths_ptr, new_num_sequences * sizeof(int));
    if (temp_lengths == NULL) {
        free(new_seq);
        return -1;
    }
    *lengths_ptr = temp_lengths;
    (*sequences_ptr)[new_num_sequences - 1] = new_seq;
    (*lengths_ptr)[new_num_sequences - 1] = new_len;
    *num_sequences_ptr = new_num_sequences;
    return new_num_sequences;
}
int main() {
    int initial_capacity = 3;
    int current_num_sequences = 0;
    int** sequences = (int**)malloc(initial_capacity * sizeof(int*));
    int* lengths = (int*)malloc(initial_capacity * sizeof(int));
    if (sequences == NULL || lengths == NULL) {
        free(sequences);
        free(lengths);
        return 1;
    }
    int len0 = 3;
    sequences[current_num_sequences] = (int*)malloc(len0 * sizeof(int));
    if (sequences[current_num_sequences] == NULL) {  return 1; }
    lengths[current_num_sequences] = len0;
    sequences[current_num_sequences][0] = 1; sequences[current_num_sequences][1] = 2; sequences[current_num_sequences][2] = 3;
    current_num_sequences++;
    int len1 = 4;
    sequences[current_num_sequences] = (int*)malloc(len1 * sizeof(int));
    if (sequences[current_num_sequences] == NULL) {  return 1; }
    lengths[current_num_sequences] = len1;
    sequences[current_num_sequences][0] = 10; sequences[current_num_sequences][1] = 20; sequences[current_num_sequences][2] = 30; sequences[current_num_sequences][3] = 40;
    current_num_sequences++;
    int len2 = 2;
    sequences[current_num_sequences] = (int*)malloc(len2 * sizeof(int));
    if (sequences[current_num_sequences] == NULL) {  return 1; }
    lengths[current_num_sequences] = len2;
    sequences[current_num_sequences][0] = 5; sequences[current_num_sequences][1] = 6;
    current_num_sequences++;
    reverse_sequence(sequences, 0, lengths);
    int new_total_sequences = merge_and_add_sequence(&sequences, &lengths, &current_num_sequences, 0, 2);
    if (new_total_sequences == -1) {
        for (int i = 0; i < current_num_sequences; i++) {
            free(sequences[i]);
        }
        free(sequences);
        free(lengths);
        return 1;
    }
    for (int i = 0; i < current_num_sequences; i++) {
        free(sequences[i]);
        sequences[i] = NULL;
    }
    free(sequences);
    sequences = NULL;
    free(lengths);
    lengths = NULL;
    return 0;
}