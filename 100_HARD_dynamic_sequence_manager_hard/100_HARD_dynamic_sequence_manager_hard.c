#include <stdio.h>
#include <stdlib.h>
void initializeCollection(int*** collection_ptr_ptr, int* num_seq_ptr, int* coll_cap_ptr, int** seq_lengths_ptr_ptr, int** seq_caps_ptr_ptr) {
    *num_seq_ptr = 0;
    *coll_cap_ptr = 4;
    *collection_ptr_ptr = (int**)malloc(*coll_cap_ptr * sizeof(int*));
    *seq_lengths_ptr_ptr = (int*)malloc(*coll_cap_ptr * sizeof(int));
    *seq_caps_ptr_ptr = (int*)malloc(*coll_cap_ptr * sizeof(int));
    if (*collection_ptr_ptr == NULL || *seq_lengths_ptr_ptr == NULL || *seq_caps_ptr_ptr == NULL) {
        exit(EXIT_FAILURE);
    }
}
void addSequence(int*** collection_ptr_ptr, int* num_seq_ptr, int* coll_cap_ptr, int** seq_lengths_ptr_ptr, int** seq_caps_ptr_ptr) {
    if (*num_seq_ptr == *coll_cap_ptr) {
        *coll_cap_ptr *= 2;
        *collection_ptr_ptr = (int**)realloc(*collection_ptr_ptr, *coll_cap_ptr * sizeof(int*));
        *seq_lengths_ptr_ptr = (int*)realloc(*seq_lengths_ptr_ptr, *coll_cap_ptr * sizeof(int));
        *seq_caps_ptr_ptr = (int*)realloc(*seq_caps_ptr_ptr, *coll_cap_ptr * sizeof(int));
        if (*collection_ptr_ptr == NULL || *seq_lengths_ptr_ptr == NULL || *seq_caps_ptr_ptr == NULL) {
            exit(EXIT_FAILURE);
        }
    }
    (*collection_ptr_ptr)[*num_seq_ptr] = NULL;
    (*seq_lengths_ptr_ptr)[*num_seq_ptr] = 0;
    (*seq_caps_ptr_ptr)[*num_seq_ptr] = 0;
    (*num_seq_ptr)++;
}
void addElementToSequence(int*** collection_ptr_ptr, int* num_seq_ptr, int** seq_lengths_ptr_ptr, int** seq_caps_ptr_ptr, int sequence_index, int value) {
    if (sequence_index < 0 || sequence_index >= *num_seq_ptr) {
        return;
    }
    if ((*seq_lengths_ptr_ptr)[sequence_index] == (*seq_caps_ptr_ptr)[sequence_index]) {
        int new_cap = ((*seq_caps_ptr_ptr)[sequence_index] == 0) ? 4 : (*seq_caps_ptr_ptr)[sequence_index] * 2;
        (*collection_ptr_ptr)[sequence_index] = (int*)realloc((*collection_ptr_ptr)[sequence_index], new_cap * sizeof(int));
        if ((*collection_ptr_ptr)[sequence_index] == NULL) {
            exit(EXIT_FAILURE);
        }
        (*seq_caps_ptr_ptr)[sequence_index] = new_cap;
    }
    (*collection_ptr_ptr)[sequence_index][(*seq_lengths_ptr_ptr)[sequence_index]] = value;
    (*seq_lengths_ptr_ptr)[sequence_index]++;
}
void removeSequence(int*** collection_ptr_ptr, int* num_seq_ptr, int* coll_cap_ptr, int** seq_lengths_ptr_ptr, int** seq_caps_ptr_ptr, int sequence_index) {
    if (sequence_index < 0 || sequence_index >= *num_seq_ptr) {
        return;
    }
    free((*collection_ptr_ptr)[sequence_index]);
    for (int i = sequence_index; i < *num_seq_ptr - 1; i++) {
        (*collection_ptr_ptr)[i] = (*collection_ptr_ptr)[i+1];
        (*seq_lengths_ptr_ptr)[i] = (*seq_lengths_ptr_ptr)[i+1];
        (*seq_caps_ptr_ptr)[i] = (*seq_caps_ptr_ptr)[i+1];
    }
    (*num_seq_ptr)--;
}
void printAllSequences(int** collection_ptr, int num_seq, int* seq_lengths_ptr) {
    printf("--- All Sequences ---\n");
    for (int i = 0; i < num_seq; i++) {
        printf("Sequence %d (length %d): ", i, seq_lengths_ptr[i]);
        if (seq_lengths_ptr[i] == 0) {
            printf("[Empty]\n");
        } else {
            for (int j = 0; j < seq_lengths_ptr[i]; j++) {
                printf("%d ", collection_ptr[i][j]);
            }
            printf("\n");
        }
    }
    printf("---------------------\n");
}
void freeAllMemory(int*** collection_ptr_ptr, int* num_seq_ptr, int** seq_lengths_ptr_ptr, int** seq_caps_ptr_ptr) {
    for (int i = 0; i < *num_seq_ptr; i++) {
        free((*collection_ptr_ptr)[i]);
    }
    free(*collection_ptr_ptr);
    free(*seq_lengths_ptr_ptr);
    free(*seq_caps_ptr_ptr);
    *collection_ptr_ptr = NULL;
    *seq_lengths_ptr_ptr = NULL;
    *seq_caps_ptr_ptr = NULL;
    *num_seq_ptr = 0;
}
int main() {
    int** dynamicCollection = NULL;
    int numSequences = 0;
    int collectionCapacity = 0;
    int* sequenceLengths = NULL;
    int* sequenceCapacities = NULL;
    initializeCollection(&dynamicCollection, &numSequences, &collectionCapacity, &sequenceLengths, &sequenceCapacities);
    addSequence(&dynamicCollection, &numSequences, &collectionCapacity, &sequenceLengths, &sequenceCapacities);
    addElementToSequence(&dynamicCollection, &numSequences, &sequenceLengths, &sequenceCapacities, 0, 10);
    addElementToSequence(&dynamicCollection, &numSequences, &sequenceLengths, &sequenceCapacities, 0, 20);
    addSequence(&dynamicCollection, &numSequences, &collectionCapacity, &sequenceLengths, &sequenceCapacities);
    addElementToSequence(&dynamicCollection, &numSequences, &sequenceLengths, &sequenceCapacities, 1, 30);
    addElementToSequence(&dynamicCollection, &numSequences, &sequenceLengths, &sequenceCapacities, 1, 40);
    addElementToSequence(&dynamicCollection, &numSequences, &sequenceLengths, &sequenceCapacities, 1, 50);
    addSequence(&dynamicCollection, &numSequences, &collectionCapacity, &sequenceLengths, &sequenceCapacities);
    addElementToSequence(&dynamicCollection, &numSequences, &sequenceLengths, &sequenceCapacities, 2, 60);
    printAllSequences(dynamicCollection, numSequences, sequenceLengths);
    removeSequence(&dynamicCollection, &numSequences, &collectionCapacity, &sequenceLengths, &sequenceCapacities, 0);
    printAllSequences(dynamicCollection, numSequences, sequenceLengths);
    addSequence(&dynamicCollection, &numSequences, &collectionCapacity, &sequenceLengths, &sequenceCapacities);
    addElementToSequence(&dynamicCollection, &numSequences, &sequenceLengths, &sequenceCapacities, 2, 70);
    addElementToSequence(&dynamicCollection, &numSequences, &sequenceLengths, &sequenceCapacities, 2, 80);
    addElementToSequence(&dynamicCollection, &numSequences, &sequenceLengths, &sequenceCapacities, 2, 90);
    addElementToSequence(&dynamicCollection, &numSequences, &sequenceLengths, &sequenceCapacities, 2, 100);
    printAllSequences(dynamicCollection, numSequences, sequenceLengths);
    freeAllMemory(&dynamicCollection, &numSequences, &sequenceLengths, &sequenceCapacities);
    return 0;
}