#include <stdio.h>
#include <stdlib.h>
#define INITIAL_COLLECTION_CAPACITY 2
#define INITIAL_SET_CAPACITY 4
#define REALLOC_FACTOR 2
void initialize_collection(int*** sets_ptr, int** set_capacities_ptr, int** set_counts_ptr, int* num_sets_ptr, int* collection_capacity_ptr, int initial_collection_capacity) {
    *sets_ptr = (int**)malloc(initial_collection_capacity * sizeof(int*));
    if (*sets_ptr == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for sets_ptr.\n");
        exit(EXIT_FAILURE);
    }
    *set_capacities_ptr = (int*)malloc(initial_collection_capacity * sizeof(int));
    if (*set_capacities_ptr == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for set_capacities_ptr.\n");
        free(*sets_ptr);
        exit(EXIT_FAILURE);
    }
    *set_counts_ptr = (int*)malloc(initial_collection_capacity * sizeof(int));
    if (*set_counts_ptr == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for set_counts_ptr.\n");
        free(*sets_ptr);
        free(*set_capacities_ptr);
        exit(EXIT_FAILURE);
    }
    *num_sets_ptr = 0;
    *collection_capacity_ptr = initial_collection_capacity;
}
void add_new_set(int*** sets_ptr, int** set_capacities_ptr, int** set_counts_ptr, int* num_sets_ptr, int* collection_capacity_ptr, int initial_set_capacity) {
    if (*num_sets_ptr == *collection_capacity_ptr) {
        int new_collection_capacity = (*collection_capacity_ptr == 0) ? INITIAL_COLLECTION_CAPACITY : *collection_capacity_ptr * REALLOC_FACTOR;
        int** new_sets = (int**)realloc(*sets_ptr, new_collection_capacity * sizeof(int*));
        if (new_sets == NULL) {
            fprintf(stderr, "Error: Failed to reallocate memory for sets.\n");
            return;
        }
        *sets_ptr = new_sets;
        int* new_set_capacities = (int*)realloc(*set_capacities_ptr, new_collection_capacity * sizeof(int));
        if (new_set_capacities == NULL) {
            fprintf(stderr, "Error: Failed to reallocate memory for set_capacities.\n");
            return;
        }
        *set_capacities_ptr = new_set_capacities;
        int* new_set_counts = (int*)realloc(*set_counts_ptr, new_collection_capacity * sizeof(int));
        if (new_set_counts == NULL) {
            fprintf(stderr, "Error: Failed to reallocate memory for set_counts.\n");
            return;
        }
        *set_counts_ptr = new_set_counts;
        *collection_capacity_ptr = new_collection_capacity;
    }
    (*sets_ptr)[*num_sets_ptr] = (int*)malloc(initial_set_capacity * sizeof(int));
    if ((*sets_ptr)[*num_sets_ptr] == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for new set.\n");
        return;
    }
    (*set_capacities_ptr)[*num_sets_ptr] = initial_set_capacity;
    (*set_counts_ptr)[*num_sets_ptr] = 0;
    (*num_sets_ptr)++;
}
void add_element_to_set(int*** sets_ptr, int** set_capacities_ptr, int** set_counts_ptr, int set_index, int value) {
    if (set_index < 0 || set_index >= *set_counts_ptr) {
        fprintf(stderr, "Error: Invalid set_index for adding element.\n");
        return;
    }
    if ((*set_counts_ptr)[set_index] == (*set_capacities_ptr)[set_index]) {
        int new_set_capacity = ((*set_capacities_ptr)[set_index] == 0) ? INITIAL_SET_CAPACITY : (*set_capacities_ptr)[set_index] * REALLOC_FACTOR;
        int* new_set = (int*)realloc((*sets_ptr)[set_index], new_set_capacity * sizeof(int));
        if (new_set == NULL) {
            fprintf(stderr, "Error: Failed to reallocate memory for set %d.\n", set_index);
            return;
        }
        (*sets_ptr)[set_index] = new_set;
        (*set_capacities_ptr)[set_index] = new_set_capacity;
    }
    (*sets_ptr)[set_index][(*set_counts_ptr)[set_index]] = value;
    (*set_counts_ptr)[set_index]++;
}
void remove_set(int*** sets_ptr, int** set_capacities_ptr, int** set_counts_ptr, int* num_sets_ptr, int* collection_capacity_ptr, int set_index) {
    if (set_index < 0 || set_index >= *num_sets_ptr) {
        fprintf(stderr, "Error: Invalid set_index for removing set.\n");
        return;
    }
    free((*sets_ptr)[set_index]);
    for (int i = set_index; i < *num_sets_ptr - 1; i++) {
        (*sets_ptr)[i] = (*sets_ptr)[i + 1];
        (*set_capacities_ptr)[i] = (*set_capacities_ptr)[i + 1];
        (*set_counts_ptr)[i] = (*set_counts_ptr)[i + 1];
    }
    (*num_sets_ptr)--;
    if (*num_sets_ptr > 0 && *num_sets_ptr < *collection_capacity_ptr / (REALLOC_FACTOR * REALLOC_FACTOR)) {
        int new_collection_capacity = *collection_capacity_ptr / REALLOC_FACTOR;
        int** new_sets = (int**)realloc(*sets_ptr, new_collection_capacity * sizeof(int*));
        if (new_sets != NULL) {
            *sets_ptr = new_sets;
        } else {
            fprintf(stderr, "Warning: Failed to shrink sets memory, keeping original capacity.\n");
        }
        int* new_set_capacities = (int*)realloc(*set_capacities_ptr, new_collection_capacity * sizeof(int));
        if (new_set_capacities != NULL) {
            *set_capacities_ptr = new_set_capacities;
        } else {
            fprintf(stderr, "Warning: Failed to shrink set_capacities memory, keeping original capacity.\n");
        }
        int* new_set_counts = (int*)realloc(*set_counts_ptr, new_collection_capacity * sizeof(int));
        if (new_set_counts != NULL) {
            *set_counts_ptr = new_set_counts;
        } else {
            fprintf(stderr, "Warning: Failed to shrink set_counts memory, keeping original capacity.\n");
        }
        *collection_capacity_ptr = new_collection_capacity;
    }
}
void print_collection(int** sets, int* set_counts, int num_sets) {
    if (sets == NULL || num_sets == 0) {
        printf("Collection is empty.\n");
        return;
    }
    for (int i = 0; i < num_sets; i++) {
        printf("Set %d (%d elements): [", i, set_counts[i]);
        for (int j = 0; j < set_counts[i]; j++) {
            printf("%d", sets[i][j]);
            if (j < set_counts[i] - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}
void cleanup_collection(int*** sets_ptr, int** set_capacities_ptr, int** set_counts_ptr, int* num_sets_ptr, int* collection_capacity_ptr) {
    if (*sets_ptr != NULL) {
        for (int i = 0; i < *num_sets_ptr; i++) {
            free((*sets_ptr)[i]);
            (*sets_ptr)[i] = NULL;
        }
        free(*sets_ptr);
        *sets_ptr = NULL;
    }
    if (*set_capacities_ptr != NULL) {
        free(*set_capacities_ptr);
        *set_capacities_ptr = NULL;
    }
    if (*set_counts_ptr != NULL) {
        free(*set_counts_ptr);
        *set_counts_ptr = NULL;
    }
    *num_sets_ptr = 0;
    *collection_capacity_ptr = 0;
}
int main() {
    int** sets = NULL;
    int* set_capacities = NULL;
    int* set_counts = NULL;
    int num_sets = 0;
    int collection_capacity = 0;
    initialize_collection(&sets, &set_capacities, &set_counts, &num_sets, &collection_capacity, INITIAL_COLLECTION_CAPACITY);
    printf("Initial collection:\n");
    print_collection(sets, set_counts, num_sets);
    printf("\n--- Adding first set and elements ---\n");
    add_new_set(&sets, &set_capacities, &set_counts, &num_sets, &collection_capacity, INITIAL_SET_CAPACITY);
    add_element_to_set(&sets, &set_capacities, &set_counts, 0, 10);
    add_element_to_set(&sets, &set_capacities, &set_counts, 0, 20);
    add_element_to_set(&sets, &set_capacities, &set_counts, 0, 30);
    print_collection(sets, set_counts, num_sets);
    printf("\n--- Adding second set and elements ---\n");
    add_new_set(&sets, &set_capacities, &set_counts, &num_sets, &collection_capacity, INITIAL_SET_CAPACITY);
    add_element_to_set(&sets, &set_capacities, &set_counts, 1, 100);
    add_element_to_set(&sets, &set_capacities, &set_counts, 1, 110);
    print_collection(sets, set_counts, num_sets);
    printf("\n--- Adding third set (triggering collection realloc) and exceeding its capacity ---\n");
    add_new_set(&sets, &set_capacities, &set_counts, &num_sets, &collection_capacity, INITIAL_SET_CAPACITY); 
    add_element_to_set(&sets, &set_capacities, &set_counts, 2, 5);
    add_element_to_set(&sets, &set_capacities, &set_counts, 2, 15);
    add_element_to_set(&sets, &set_capacities, &set_counts, 2, 25);
    add_element_to_set(&sets, &set_capacities, &set_counts, 2, 35);
    add_element_to_set(&sets, &set_capacities, &set_counts, 2, 45); 
    print_collection(sets, set_counts, num_sets);
    printf("\n--- Removing set 0 (first set) ---\n");
    remove_set(&sets, &set_capacities, &set_counts, &num_sets, &collection_capacity, 0);
    print_collection(sets, set_counts, num_sets);
    printf("\n--- Removing set 0 (now the original second set) ---\n");
    remove_set(&sets, &set_capacities, &set_counts, &num_sets, &collection_capacity, 0);
    print_collection(sets, set_counts, num_sets);
    printf("\n--- Cleaning up collection ---\n");
    cleanup_collection(&sets, &set_capacities, &set_counts, &num_sets, &collection_capacity);
    print_collection(sets, set_counts, num_sets); 
    return 0;
}