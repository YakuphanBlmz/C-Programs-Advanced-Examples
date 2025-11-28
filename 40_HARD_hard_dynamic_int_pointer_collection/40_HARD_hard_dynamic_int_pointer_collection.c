#include <stdio.h>
#include <stdlib.h>
int main() {
    int **collection = NULL;
    int current_size = 0;
    int capacity = 0;
    printf("Adding elements...\n");
    for (int i = 0; i < 5; ++i) {
        int *new_val = (int *)malloc(sizeof(int));
        if (new_val == NULL) {
            fprintf(stderr, "Memory allocation failed for new_val\n");
            for (int k = 0; k < current_size; ++k) {
                free(collection[k]);
            }
            free(collection);
            return 1;
        }
        *new_val = (i + 1) * 10;
        if (current_size == capacity) {
            int new_capacity = (capacity == 0) ? 1 : capacity * 2;
            int **temp = (int **)realloc(collection, new_capacity * sizeof(int *));
            if (temp == NULL) {
                fprintf(stderr, "Memory reallocation failed for collection\n");
                free(new_val);
                for (int k = 0; k < current_size; ++k) {
                    free(collection[k]);
                }
                free(collection);
                return 1;
            }
            collection = temp;
            capacity = new_capacity;
        }
        collection[current_size] = new_val;
        current_size++;
    }
    printf("Current collection elements:\n");
    for (int i = 0; i < current_size; ++i) {
        printf("Element %d: %d (Address: %p)\n", i, *(collection[i]), (void *)collection[i]);
    }
    printf("\n");
    int index_to_remove = 2;
    if (current_size > 0 && index_to_remove >= 0 && index_to_remove < current_size) {
        printf("Removing element at index %d (value: %d)...\n", index_to_remove, *(collection[index_to_remove]));
        free(collection[index_to_remove]);
        for (int i = index_to_remove; i < current_size - 1; ++i) {
            collection[i] = collection[i+1];
        }
        current_size--;
        if (current_size > 0 && current_size * 4 < capacity && capacity > 1) {
            int new_capacity = capacity / 2;
            int **temp = (int **)realloc(collection, new_capacity * sizeof(int *));
            if (temp != NULL) {
                collection = temp;
                capacity = new_capacity;
            }
        } else if (current_size == 0) {
             free(collection);
             collection = NULL;
             capacity = 0;
        }
    } else {
        printf("Invalid index to remove or collection is empty.\n");
    }
    printf("Collection elements after removal:\n");
    if (current_size == 0) {
        printf("Collection is empty.\n");
    } else {
        for (int i = 0; i < current_size; ++i) {
            printf("Element %d: %d (Address: %p)\n", i, *(collection[i]), (void *)collection[i]);
        }
    }
    printf("\n");
    printf("Adding another element...\n");
    int *new_val_after_remove = (int *)malloc(sizeof(int));
    if (new_val_after_remove == NULL) {
        fprintf(stderr, "Memory allocation failed for new_val_after_remove\n");
        for (int k = 0; k < current_size; ++k) {
            free(collection[k]);
        }
        free(collection);
        return 1;
    }
    *new_val_after_remove = 99;
    if (current_size == capacity) {
        int new_capacity = (capacity == 0) ? 1 : capacity * 2;
        int **temp = (int **)realloc(collection, new_capacity * sizeof(int *));
        if (temp == NULL) {
            fprintf(stderr, "Memory reallocation failed for collection\n");
            free(new_val_after_remove);
            for (int k = 0; k < current_size; ++k) {
                free(collection[k]);
            }
            free(collection);
            return 1;
        }
        collection = temp;
        capacity = new_capacity;
    }
    collection[current_size] = new_val_after_remove;
    current_size++;
    printf("Collection elements after adding one more:\n");
    for (int i = 0; i < current_size; ++i) {
        printf("Element %d: %d (Address: %p)\n", i, *(collection[i]), (void *)collection[i]);
    }
    printf("\n");
    printf("Cleaning up memory...\n");
    for (int i = 0; i < current_size; ++i) {
        free(collection[i]);
        collection[i] = NULL;
    }
    free(collection);
    collection = NULL;
    printf("Memory cleaned successfully.\n");
    return 0;
}