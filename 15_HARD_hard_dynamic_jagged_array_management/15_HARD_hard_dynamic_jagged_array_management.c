#include <stdio.h>
#include <stdlib.h>
int main() {
    int **collection = NULL;
    int *list_sizes = NULL;
    int collection_capacity = 0;
    int collection_size = 0;
    int initial_capacity = 2;
    collection = (int **)malloc(initial_capacity * sizeof(int *));
    list_sizes = (int *)malloc(initial_capacity * sizeof(int));
    if (collection == NULL || list_sizes == NULL) {
        fprintf(stderr, "Initial allocation failed.\n");
        if (collection) free(collection);
        if (list_sizes) free(list_sizes);
        return 1;
    }
    collection_capacity = initial_capacity;
    printf("--- Initializing Collection ---\n");
    printf("Capacity: %d, Size: %d\n", collection_capacity, collection_size);
    int list_data_index = 0;
    int new_list_size_1 = 3;
    if (collection_size == collection_capacity) {
        collection_capacity *= 2;
        int **temp_collection = (int **)realloc(collection, collection_capacity * sizeof(int *));
        int *temp_list_sizes = (int *)realloc(list_sizes, collection_capacity * sizeof(int));
        if (temp_collection == NULL || temp_list_sizes == NULL) {
            fprintf(stderr, "Reallocation for collection expansion failed.\n");
            for (int i = 0; i < collection_size; i++) {
                free(collection[i]);
            }
            free(collection);
            free(list_sizes);
            return 1;
        }
        collection = temp_collection;
        list_sizes = temp_list_sizes;
        printf("Collection capacity expanded to %d\n", collection_capacity);
    }
    collection[collection_size] = (int *)malloc(new_list_size_1 * sizeof(int));
    if (collection[collection_size] == NULL) {
        fprintf(stderr, "List 1 allocation failed.\n");
        for (int i = 0; i < collection_size; i++) {
            free(collection[i]);
        }
        free(collection);
        free(list_sizes);
        return 1;
    }
    list_sizes[collection_size] = new_list_size_1;
    for (int i = 0; i < new_list_size_1; i++) {
        collection[collection_size][i] = list_data_index++;
    }
    collection_size++;
    int new_list_size_2 = 4;
    if (collection_size == collection_capacity) {
        collection_capacity *= 2;
        int **temp_collection = (int **)realloc(collection, collection_capacity * sizeof(int *));
        int *temp_list_sizes = (int *)realloc(list_sizes, collection_capacity * sizeof(int));
        if (temp_collection == NULL || temp_list_sizes == NULL) {
            fprintf(stderr, "Reallocation for collection expansion failed.\n");
            for (int i = 0; i < collection_size; i++) {
                free(collection[i]);
            }
            free(collection);
            free(list_sizes);
            return 1;
        }
        collection = temp_collection;
        list_sizes = temp_list_sizes;
        printf("Collection capacity expanded to %d\n", collection_capacity);
    }
    collection[collection_size] = (int *)malloc(new_list_size_2 * sizeof(int));
    if (collection[collection_size] == NULL) {
        fprintf(stderr, "List 2 allocation failed.\n");
        for (int i = 0; i < collection_size; i++) {
            free(collection[i]);
        }
        free(collection);
        free(list_sizes);
        return 1;
    }
    list_sizes[collection_size] = new_list_size_2;
    for (int i = 0; i < new_list_size_2; i++) {
        collection[collection_size][i] = list_data_index++;
    }
    collection_size++;
    int new_list_size_3 = 2;
    if (collection_size == collection_capacity) {
        collection_capacity *= 2;
        int **temp_collection = (int **)realloc(collection, collection_capacity * sizeof(int *));
        int *temp_list_sizes = (int *)realloc(list_sizes, collection_capacity * sizeof(int));
        if (temp_collection == NULL || temp_list_sizes == NULL) {
            fprintf(stderr, "Reallocation for collection expansion failed.\n");
            for (int i = 0; i < collection_size; i++) {
                free(collection[i]);
            }
            free(collection);
            free(list_sizes);
            return 1;
        }
        collection = temp_collection;
        list_sizes = temp_list_sizes;
        printf("Collection capacity expanded to %d\n", collection_capacity);
    }
    collection[collection_size] = (int *)malloc(new_list_size_3 * sizeof(int));
    if (collection[collection_size] == NULL) {
        fprintf(stderr, "List 3 allocation failed.\n");
        for (int i = 0; i < collection_size; i++) {
            free(collection[i]);
        }
        free(collection);
        free(list_sizes);
        return 1;
    }
    list_sizes[collection_size] = new_list_size_3;
    for (int i = 0; i < new_list_size_3; i++) {
        collection[collection_size][i] = list_data_index++;
    }
    collection_size++;
    printf("\n--- After Adding 3 Lists ---\n");
    printf("Capacity: %d, Size: %d\n", collection_capacity, collection_size);
    for (int i = 0; i < collection_size; i++) {
        printf("List %d (size %d): ", i, list_sizes[i]);
        for (int j = 0; j < list_sizes[i]; j++) {
            printf("%d ", collection[i][j]);
        }
        printf("\n");
    }
    int list_to_resize_index = 0;
    int new_resized_list_size = 5;
    if (list_to_resize_index < collection_size) {
        int *temp_list = (int *)realloc(collection[list_to_resize_index], new_resized_list_size * sizeof(int));
        if (temp_list == NULL) {
            fprintf(stderr, "Reallocation for list %d resize failed. Original list preserved.\n", list_to_resize_index);
        } else {
            collection[list_to_resize_index] = temp_list;
            for (int i = list_sizes[list_to_resize_index]; i < new_resized_list_size; i++) {
                collection[list_to_resize_index][i] = 99;
            }
            list_sizes[list_to_resize_index] = new_resized_list_size;
            printf("\nList %d resized to %d elements.\n", list_to_resize_index, new_resized_list_size);
        }
    }
    printf("\n--- After Resizing List %d ---\n", list_to_resize_index);
    printf("Capacity: %d, Size: %d\n", collection_capacity, collection_size);
    for (int i = 0; i < collection_size; i++) {
        printf("List %d (size %d): ", i, list_sizes[i]);
        for (int j = 0; j < list_sizes[i]; j++) {
            printf("%d ", collection[i][j]);
        }
        printf("\n");
    }
    int list_to_remove_index = 1;
    if (list_to_remove_index < collection_size) {
        free(collection[list_to_remove_index]);
        for (int i = list_to_remove_index; i < collection_size - 1; i++) {
            collection[i] = collection[i+1];
            list_sizes[i] = list_sizes[i+1];
        }
        collection_size--;
        if (collection_capacity > initial_capacity && collection_size * 4 < collection_capacity) {
            collection_capacity /= 2;
            int **temp_collection = (int **)realloc(collection, collection_capacity * sizeof(int *));
            int *temp_list_sizes = (int *)realloc(list_sizes, collection_capacity * sizeof(int));
            if (temp_collection == NULL || temp_list_sizes == NULL) {
                fprintf(stderr, "Reallocation for collection shrinking failed. Keeping larger capacity.\n");
            } else {
                collection = temp_collection;
                list_sizes = temp_list_sizes;
                printf("Collection capacity shrunk to %d\n", collection_capacity);
            }
        }
        printf("\nList %d removed.\n", list_to_remove_index);
    }
    printf("\n--- After Removing List %d ---\n", list_to_remove_index);
    printf("Capacity: %d, Size: %d\n", collection_capacity, collection_size);
    for (int i = 0; i < collection_size; i++) {
        printf("List %d (size %d): ", i, list_sizes[i]);
        for (int j = 0; j < list_sizes[i]; j++) {
            printf("%d ", collection[i][j]);
        }
        printf("\n");
    }
    printf("\n--- Cleaning up memory ---\n");
    for (int i = 0; i < collection_size; i++) {
        free(collection[i]);
    }
    free(collection);
    free(list_sizes);
    collection = NULL;
    list_sizes = NULL;
    printf("All memory freed.\n");
    return 0;
}