#include <stdio.h>
#include <stdlib.h>
void ensureOuterCapacity(int*** collections_ptr, int** sizes_ptr, int** capacities_ptr, int* num_collections_ptr, int* max_collections_capacity_ptr, int target_index) {
    if (target_index >= *max_collections_capacity_ptr) {
        int new_capacity = (*max_collections_capacity_ptr == 0) ? 4 : *max_collections_capacity_ptr * 2;
        int** new_collections = (int**)realloc(*collections_ptr, new_capacity * sizeof(int*));
        if (new_collections == NULL) exit(EXIT_FAILURE);
        *collections_ptr = new_collections;
        int* new_sizes = (int*)realloc(*sizes_ptr, new_capacity * sizeof(int));
        if (new_sizes == NULL) exit(EXIT_FAILURE);
        *sizes_ptr = new_sizes;
        int* new_capacities = (int*)realloc(*capacities_ptr, new_capacity * sizeof(int));
        if (new_capacities == NULL) exit(EXIT_FAILURE);
        *capacities_ptr = new_capacities;
        for (int i = *max_collections_capacity_ptr; i < new_capacity; i++) {
            (*collections_ptr)[i] = NULL;
            (*sizes_ptr)[i] = 0;
            (*capacities_ptr)[i] = 0;
        }
        *max_collections_capacity_ptr = new_capacity;
    }
    if (target_index >= *num_collections_ptr) {
        *num_collections_ptr = target_index + 1;
    }
}
void addElementToCollection(int*** collections_ptr, int** sizes_ptr, int** capacities_ptr, int* num_collections_ptr, int* max_collections_capacity_ptr, int collection_index, int value) {
    ensureOuterCapacity(collections_ptr, sizes_ptr, capacities_ptr, num_collections_ptr, max_collections_capacity_ptr, collection_index);
    if ((*collections_ptr)[collection_index] == NULL) {
        int initial_inner_capacity = 2;
        (*collections_ptr)[collection_index] = (int*)malloc(initial_inner_capacity * sizeof(int));
        if ((*collections_ptr)[collection_index] == NULL) exit(EXIT_FAILURE);
        (*sizes_ptr)[collection_index] = 0;
        (*capacities_ptr)[collection_index] = initial_inner_capacity;
    }
    if ((*sizes_ptr)[collection_index] == (*capacities_ptr)[collection_index]) {
        int new_inner_capacity = (*capacities_ptr)[collection_index] * 2;
        if (new_inner_capacity == 0) new_inner_capacity = 2;
        int* new_inner_array = (int*)realloc((*collections_ptr)[collection_index], new_inner_capacity * sizeof(int));
        if (new_inner_array == NULL) exit(EXIT_FAILURE);
        (*collections_ptr)[collection_index] = new_inner_array;
        (*capacities_ptr)[collection_index] = new_inner_capacity;
    }
    (*collections_ptr)[collection_index][(*sizes_ptr)[collection_index]] = value;
    (*sizes_ptr)[collection_index]++;
}
void printCollections(int** collections, int* sizes, int num_collections) {
    printf("Current Collections:\n");
    if (num_collections == 0) {
        printf("  No collections.\n");
        return;
    }
    for (int i = 0; i < num_collections; i++) {
        printf("  Collection %d (size %d): [", i, sizes[i]);
        for (int j = 0; j < sizes[i]; j++) {
            printf("%d", collections[i][j]);
            if (j < sizes[i] - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}
void freeAllCollections(int*** collections_ptr, int** sizes_ptr, int** capacities_ptr, int* max_collections_capacity_ptr) {
    if (*collections_ptr != NULL) {
        for (int i = 0; i < *max_collections_capacity_ptr; i++) {
            if ((*collections_ptr)[i] != NULL) {
                free((*collections_ptr)[i]);
                (*collections_ptr)[i] = NULL;
            }
        }
        free(*collections_ptr);
        *collections_ptr = NULL;
    }
    if (*sizes_ptr != NULL) {
        free(*sizes_ptr);
        *sizes_ptr = NULL;
    }
    if (*capacities_ptr != NULL) {
        free(*capacities_ptr);
        *capacities_ptr = NULL;
    }
    *max_collections_capacity_ptr = 0;
}
int main() {
    int** collections = NULL;
    int* sizes = NULL;
    int* capacities = NULL;
    int num_collections = 0;
    int max_collections_capacity = 0;
    addElementToCollection(&collections, &sizes, &capacities, &num_collections, &max_collections_capacity, 0, 10);
    addElementToCollection(&collections, &sizes, &capacities, &num_collections, &max_collections_capacity, 0, 20);
    addElementToCollection(&collections, &sizes, &capacities, &num_collections, &max_collections_capacity, 1, 100);
    addElementToCollection(&collections, &sizes, &capacities, &num_collections, &max_collections_capacity, 0, 30);
    addElementToCollection(&collections, &sizes, &capacities, &num_collections, &max_collections_capacity, 2, 200);
    addElementToCollection(&collections, &sizes, &capacities, &num_collections, &max_collections_capacity, 4, 400);
    addElementToCollection(&collections, &sizes, &capacities, &num_collections, &max_collections_capacity, 1, 110);
    addElementToCollection(&collections, &sizes, &capacities, &num_collections, &max_collections_capacity, 4, 410);
    addElementToCollection(&collections, &sizes, &capacities, &num_collections, &max_collections_capacity, 0, 40);
    addElementToCollection(&collections, &sizes, &capacities, &num_collections, &max_collections_capacity, 3, 300);
    printCollections(collections, sizes, num_collections);
    freeAllCollections(&collections, &sizes, &capacities, &max_collections_capacity);
    printf("\nMemory freed. Collections pointer: %p, sizes pointer: %p, capacities pointer: %p\n", (void*)collections, (void*)sizes, (void*)capacities);
    return 0;
}