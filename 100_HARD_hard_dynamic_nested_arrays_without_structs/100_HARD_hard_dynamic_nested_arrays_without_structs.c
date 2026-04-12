#include <stdio.h>
#include <stdlib.h>
int main() {
    int** collection = NULL;
    int* container_sizes = NULL;
    int* container_capacities = NULL;
    int total_containers = 0;
    int collection_capacity = 0;
    int initial_container_capacity = 4;
    int collection_resize_factor = 2;
    int container_resize_factor = 2;
    printf("Adding containers...\n");
    for (int i = 0; i < 3; ++i) {
        if (total_containers == collection_capacity) {
            int new_capacity = (collection_capacity == 0) ? 1 : collection_capacity * collection_resize_factor;
            collection = (int**)realloc(collection, new_capacity * sizeof(int*));
            container_sizes = (int*)realloc(container_sizes, new_capacity * sizeof(int));
            container_capacities = (int*)realloc(container_capacities, new_capacity * sizeof(int));
            collection_capacity = new_capacity;
        }
        collection[total_containers] = (int*)malloc(initial_container_capacity * sizeof(int));
        container_sizes[total_containers] = 0;
        container_capacities[total_containers] = initial_container_capacity;
        printf("Container %d added. Initial capacity: %d\n", total_containers, initial_container_capacity);
        total_containers++;
    }
    printf("\nAdding elements...\n");
    for (int i = 0; i < 5; ++i) {
        int container_idx = 0;
        if (container_sizes[container_idx] == container_capacities[container_idx]) {
            int new_container_capacity = container_capacities[container_idx] * container_resize_factor;
            collection[container_idx] = (int*)realloc(collection[container_idx], new_container_capacity * sizeof(int));
            container_capacities[container_idx] = new_container_capacity;
            printf("Container %d resized to capacity %d\n", container_idx, new_container_capacity);
        }
        collection[container_idx][container_sizes[container_idx]] = i * 10;
        container_sizes[container_idx]++;
    }
    for (int i = 0; i < 2; ++i) {
        int container_idx = 1;
        if (container_sizes[container_idx] == container_capacities[container_idx]) {
            int new_container_capacity = container_capacities[container_idx] * container_resize_factor;
            collection[container_idx] = (int*)realloc(collection[container_idx], new_container_capacity * sizeof(int));
            container_capacities[container_idx] = new_container_capacity;
            printf("Container %d resized to capacity %d\n", container_idx, new_container_capacity);
        }
        collection[container_idx][container_sizes[container_idx]] = i * 100 + 1;
        container_sizes[container_idx]++;
    }
    printf("\nCurrent state of containers:\n");
    for (int i = 0; i < total_containers; ++i) {
        printf("Container %d (Size: %d, Capacity: %d): [", i, container_sizes[i], container_capacities[i]);
        for (int j = 0; j < container_sizes[i]; ++j) {
            printf("%d%s", collection[i][j], (j == container_sizes[i] - 1) ? "" : ", ");
        }
        printf("]\n");
    }
    printf("\nRemoving element at index 2 from Container 0...\n");
    int target_container_idx_remove_elem = 0;
    int target_element_idx_remove = 2;
    if (target_container_idx_remove_elem < total_containers && target_element_idx_remove < container_sizes[target_container_idx_remove_elem]) {
        for (int j = target_element_idx_remove; j < container_sizes[target_container_idx_remove_elem] - 1; ++j) {
            collection[target_container_idx_remove_elem][j] = collection[target_container_idx_remove_elem][j+1];
        }
        container_sizes[target_container_idx_remove_elem]--;
        if (container_sizes[target_container_idx_remove_elem] > 0 && container_sizes[target_container_idx_remove_elem] * 4 < container_capacities[target_container_idx_remove_elem]) {
            int new_capacity = container_capacities[target_container_idx_remove_elem] / 2;
            collection[target_container_idx_remove_elem] = (int*)realloc(collection[target_container_idx_remove_elem], new_capacity * sizeof(int));
            container_capacities[target_container_idx_remove_elem] = new_capacity;
            printf("Container %d shrunk to capacity %d\n", target_container_idx_remove_elem, new_capacity);
        } else if (container_sizes[target_container_idx_remove_elem] == 0 && container_capacities[target_container_idx_remove_elem] > initial_container_capacity) {
            int new_capacity = (initial_container_capacity > 0) ? initial_container_capacity : 1;
            collection[target_container_idx_remove_elem] = (int*)realloc(collection[target_container_idx_remove_elem], new_capacity * sizeof(int));
            container_capacities[target_container_idx_remove_elem] = new_capacity;
            printf("Container %d (now empty) shrunk to capacity %d\n", target_container_idx_remove_elem, new_capacity);
        }
    }
    printf("\nCurrent state after element removal:\n");
    for (int i = 0; i < total_containers; ++i) {
        printf("Container %d (Size: %d, Capacity: %d): [", i, container_sizes[i], container_capacities[i]);
        for (int j = 0; j < container_sizes[i]; ++j) {
            printf("%d%s", collection[i][j], (j == container_sizes[i] - 1) ? "" : ", ");
        }
        printf("]\n");
    }
    printf("\nRemoving Container 1...\n");
    int target_container_idx_remove = 1;
    if (target_container_idx_remove < total_containers) {
        free(collection[target_container_idx_remove]);
        for (int i = target_container_idx_remove; i < total_containers - 1; ++i) {
            collection[i] = collection[i+1];
            container_sizes[i] = container_sizes[i+1];
            container_capacities[i] = container_capacities[i+1];
        }
        total_containers--;
        if (total_containers > 0 && total_containers * 4 < collection_capacity) {
            int new_capacity = collection_capacity / 2;
            collection = (int**)realloc(collection, new_capacity * sizeof(int*));
            container_sizes = (int*)realloc(container_sizes, new_capacity * sizeof(int));
            container_capacities = (int*)realloc(container_capacities, new_capacity * sizeof(int));
            collection_capacity = new_capacity;
            printf("Main collection shrunk to capacity %d\n", new_capacity);
        } else if (total_containers == 0 && collection_capacity > 0) {
            free(collection); collection = NULL;
            free(container_sizes); container_sizes = NULL;
            free(container_capacities); container_capacities = NULL;
            collection_capacity = 0;
            printf("Main collection fully deallocated as it became empty.\n");
        }
    }
    printf("\nCurrent state after container removal:\n");
    if (total_containers == 0) {
        printf("No containers left.\n");
    } else {
        for (int i = 0; i < total_containers; ++i) {
            printf("Container %d (Size: %d, Capacity: %d): [", i, container_sizes[i], container_capacities[i]);
            for (int j = 0; j < container_sizes[i]; ++j) {
                printf("%d%s", collection[i][j], (j == container_sizes[i] - 1) ? "" : ", ");
            }
            printf("]\n");
        }
    }
    printf("\nCleaning up all remaining memory...\n");
    for (int i = 0; i < total_containers; ++i) {
        free(collection[i]);
        collection[i] = NULL;
    }
    free(collection); collection = NULL;
    free(container_sizes); container_sizes = NULL;
    free(container_capacities); container_capacities = NULL;
    printf("All memory freed.\n");
    return 0;
}