#include <stdio.h>
#include <stdlib.h>
#define INITIAL_OUTER_CAPACITY 2
#define INITIAL_INNER_CAPACITY 4
#define RESIZE_FACTOR 2
int main() {
    int **main_container = NULL;
    int *sub_container_sizes = NULL;
    int *sub_container_capacities = NULL;
    int current_outer_size = 0;
    int current_outer_capacity = 0;
    int status = 0;
    current_outer_capacity = INITIAL_OUTER_CAPACITY;
    main_container = (int **)malloc(current_outer_capacity * sizeof(int *));
    if (main_container == NULL) {
        status = 1;
        goto cleanup_and_exit;
    }
    sub_container_sizes = (int *)malloc(current_outer_capacity * sizeof(int));
    if (sub_container_sizes == NULL) {
        status = 1;
        goto cleanup_and_exit;
    }
    sub_container_capacities = (int *)malloc(current_outer_capacity * sizeof(int));
    if (sub_container_capacities == NULL) {
        status = 1;
        goto cleanup_and_exit;
    }
    for (int i = 0; i < 3; i++) {
        if (current_outer_size == current_outer_capacity) {
            int new_outer_capacity = current_outer_capacity * RESIZE_FACTOR;
            int **temp_main_container = (int **)realloc(main_container, new_outer_capacity * sizeof(int *));
            if (temp_main_container == NULL) {
                status = 1;
                goto cleanup_and_exit;
            }
            main_container = temp_main_container;
            int *temp_sub_container_sizes = (int *)realloc(sub_container_sizes, new_outer_capacity * sizeof(int));
            if (temp_sub_container_sizes == NULL) {
                status = 1;
                goto cleanup_and_exit;
            }
            sub_container_sizes = temp_sub_container_sizes;
            int *temp_sub_container_capacities = (int *)realloc(sub_container_capacities, new_outer_capacity * sizeof(int));
            if (temp_sub_container_capacities == NULL) {
                status = 1;
                goto cleanup_and_exit;
            }
            sub_container_capacities = temp_sub_container_capacities;
            current_outer_capacity = new_outer_capacity;
        }
        main_container[current_outer_size] = (int *)malloc(INITIAL_INNER_CAPACITY * sizeof(int));
        if (main_container[current_outer_size] == NULL) {
            status = 1;
            goto cleanup_and_exit;
        }
        sub_container_sizes[current_outer_size] = 0;
        sub_container_capacities[current_outer_size] = INITIAL_INNER_CAPACITY;
        current_outer_size++;
    }
    for (int i = 0; i < 5; i++) {
        int bag_idx = 0;
        if (sub_container_sizes[bag_idx] == sub_container_capacities[bag_idx]) {
            int new_inner_capacity = sub_container_capacities[bag_idx] * RESIZE_FACTOR;
            int *temp_inner_container = (int *)realloc(main_container[bag_idx], new_inner_capacity * sizeof(int));
            if (temp_inner_container == NULL) {
                status = 1;
                goto cleanup_and_exit;
            }
            main_container[bag_idx] = temp_inner_container;
            sub_container_capacities[bag_idx] = new_inner_capacity;
        }
        main_container[bag_idx][sub_container_sizes[bag_idx]++] = i * 10;
    }
    for (int i = 0; i < 2; i++) {
        int bag_idx = 1;
        if (sub_container_sizes[bag_idx] == sub_container_capacities[bag_idx]) {
            int new_inner_capacity = sub_container_capacities[bag_idx] * RESIZE_FACTOR;
            int *temp_inner_container = (int *)realloc(main_container[bag_idx], new_inner_capacity * sizeof(int));
            if (temp_inner_container == NULL) {
                status = 1;
                goto cleanup_and_exit;
            }
            main_container[bag_idx] = temp_inner_container;
            sub_container_capacities[bag_idx] = new_inner_capacity;
        }
        main_container[bag_idx][sub_container_sizes[bag_idx]++] = i + 100;
    }
    for (int i = 0; i < 7; i++) {
        int bag_idx = 2;
        if (sub_container_sizes[bag_idx] == sub_container_capacities[bag_idx]) {
            int new_inner_capacity = sub_container_capacities[bag_idx] * RESIZE_FACTOR;
            int *temp_inner_container = (int *)realloc(main_container[bag_idx], new_inner_capacity * sizeof(int));
            if (temp_inner_container == NULL) {
                status = 1;
                goto cleanup_and_exit;
            }
            main_container[bag_idx] = temp_inner_container;
            sub_container_capacities[bag_idx] = new_inner_capacity;
        }
        main_container[bag_idx][sub_container_sizes[bag_idx]++] = i * 2 + 1000;
    }
    printf("--- Bag Contents ---\n");
    for (int i = 0; i < current_outer_size; i++) {
        printf("Bag %d (Size: %d, Capacity: %d): ", i, sub_container_sizes[i], sub_container_capacities[i]);
        for (int j = 0; j < sub_container_sizes[i]; j++) {
            printf("%d ", main_container[i][j]);
        }
        printf("\n");
    }
    printf("--------------------\n");
cleanup_and_exit:
    for (int i = 0; i < current_outer_size; i++) {
        free(main_container[i]);
    }
    free(main_container);
    free(sub_container_sizes);
    free(sub_container_capacities);
    return status;
}