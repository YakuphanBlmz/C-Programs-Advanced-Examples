#include <stdio.h>
#include <stdlib.h>
int grow_warehouse(int ***warehouse_ptr, int **unit_capacities_ptr, int *current_num_units_ptr, int *current_max_units_capacity_ptr) {
    if (*current_num_units_ptr < *current_max_units_capacity_ptr) {
        return 0;
    }
    int new_capacity = (*current_max_units_capacity_ptr == 0) ? 2 : (*current_max_units_capacity_ptr * 2);
    if (new_capacity < *current_num_units_ptr) new_capacity = *current_num_units_ptr + 1;
    int **temp_warehouse = (int **)realloc(*warehouse_ptr, new_capacity * sizeof(int *));
    if (temp_warehouse == NULL) return -1;
    int *temp_unit_capacities = (int *)realloc(*unit_capacities_ptr, new_capacity * sizeof(int));
    if (temp_unit_capacities == NULL) {
        return -1;
    }
    *warehouse_ptr = temp_warehouse;
    *unit_capacities_ptr = temp_unit_capacities;
    *current_max_units_capacity_ptr = new_capacity;
    return 0;
}
int add_new_unit(int ***warehouse_ptr, int **unit_capacities_ptr, int *current_num_units_ptr, int *current_max_units_capacity_ptr) {
    if (grow_warehouse(warehouse_ptr, unit_capacities_ptr, current_num_units_ptr, current_max_units_capacity_ptr) == -1) {
        return -1;
    }
    (*warehouse_ptr)[*current_num_units_ptr] = NULL;
    (*unit_capacities_ptr)[*current_num_units_ptr] = 0;
    (*current_num_units_ptr)++;
    return *current_num_units_ptr - 1;
}
int store_item_in_unit(int ***unit_ptr_addr, int *unit_current_size_ptr, int value) {
    int new_size = *unit_current_size_ptr + 1;
    int *new_storage = (int *)realloc(*unit_ptr_addr, new_size * sizeof(int));
    if (new_storage == NULL) {
        return -1;
    }
    *unit_ptr_addr = new_storage;
    (*unit_ptr_addr)[*unit_current_size_ptr] = value;
    *unit_current_size_ptr = new_size;
    return 0;
}
void remove_and_shift_unit(int ***warehouse_ptr, int **unit_capacities_ptr, int *current_num_units_ptr, int *current_max_units_capacity_ptr, int unit_index) {
    if (unit_index < 0 || unit_index >= *current_num_units_ptr) return;
    free((*warehouse_ptr)[unit_index]);
    for (int i = unit_index; i < *current_num_units_ptr - 1; i++) {
        (*warehouse_ptr)[i] = (*warehouse_ptr)[i+1];
        (*unit_capacities_ptr)[i] = (*unit_capacities_ptr)[i+1];
    }
    (*current_num_units_ptr)--;
    if (*current_num_units_ptr < *current_max_units_capacity_ptr / 2 && *current_max_units_capacity_ptr > 0) {
        int new_max_capacity = (*current_num_units_ptr == 0) ? 0 : *current_num_units_ptr;
        if (new_max_capacity == 0 && *current_num_units_ptr > 0) new_max_capacity = 1;
        int **temp_warehouse = (int **)realloc(*warehouse_ptr, new_max_capacity * sizeof(int *));
        int *temp_unit_capacities = (int *)realloc(*unit_capacities_ptr, new_max_capacity * sizeof(int));
        if (temp_warehouse != NULL) {
            *warehouse_ptr = temp_warehouse;
        }
        if (temp_unit_capacities != NULL) {
            *unit_capacities_ptr = temp_unit_capacities;
        }
        *current_max_units_capacity_ptr = new_max_capacity;
    }
}
void free_all(int ***warehouse_ptr, int **unit_capacities_ptr, int *current_num_units_ptr, int *current_max_units_capacity_ptr) {
    if (*warehouse_ptr != NULL) {
        for (int i = 0; i < *current_num_units_ptr; i++) {
            free((*warehouse_ptr)[i]);
        }
        free(*warehouse_ptr);
        *warehouse_ptr = NULL;
    }
    if (*unit_capacities_ptr != NULL) {
        free(*unit_capacities_ptr);
        *unit_capacities_ptr = NULL;
    }
    *current_num_units_ptr = 0;
    *current_max_units_capacity_ptr = 0;
}
int main() {
    int **warehouse = NULL;
    int *unit_capacities = NULL;
    int num_units = 0;
    int max_units_capacity = 0;
    printf("Initializing warehouse...\n");
    int unit0_idx = add_new_unit(&warehouse, &unit_capacities, &num_units, &max_units_capacity);
    int unit1_idx = add_new_unit(&warehouse, &unit_capacities, &num_units, &max_units_capacity);
    int unit2_idx = add_new_unit(&warehouse, &unit_capacities, &num_units, &max_units_capacity);
    printf("Added %d units. Warehouse capacity: %d\n", num_units, max_units_capacity);
    store_item_in_unit(&(warehouse[unit0_idx]), &(unit_capacities[unit0_idx]), 10);
    store_item_in_unit(&(warehouse[unit0_idx]), &(unit_capacities[unit0_idx]), 20);
    store_item_in_unit(&(warehouse[unit0_idx]), &(unit_capacities[unit0_idx]), 30);
    store_item_in_unit(&(warehouse[unit1_idx]), &(unit_capacities[unit1_idx]), 100);
    store_item_in_unit(&(warehouse[unit1_idx]), &(unit_capacities[unit1_idx]), 110);
    store_item_in_unit(&(warehouse[unit2_idx]), &(unit_capacities[unit2_idx]), 200);
    printf("Current warehouse state:\n");
    for (int i = 0; i < num_units; i++) {
        printf("  Unit %d (size %d): ", i, unit_capacities[i]);
        for (int j = 0; j < unit_capacities[i]; j++) {
            printf("%d ", warehouse[i][j]);
        }
        printf("\n");
    }
    printf("Removing unit %d...\n", unit1_idx);
    remove_and_shift_unit(&warehouse, &unit_capacities, &num_units, &max_units_capacity, unit1_idx);
    printf("Units remaining: %d. Warehouse capacity: %d\n", num_units, max_units_capacity);
    int unit3_idx = add_new_unit(&warehouse, &unit_capacities, &num_units, &max_units_capacity);
    printf("Added unit %d. Units remaining: %d. Warehouse capacity: %d\n", unit3_idx, num_units, max_units_capacity);
    store_item_in_unit(&(warehouse[unit3_idx]), &(unit_capacities[unit3_idx]), 300);
    store_item_in_unit(&(warehouse[unit3_idx]), &(unit_capacities[unit3_idx]), 310);
    printf("Final warehouse state before freeing:\n");
    for (int i = 0; i < num_units; i++) {
        printf("  Unit %d (size %d): ", i, unit_capacities[i]);
        for (int j = 0; j < unit_capacities[i]; j++) {
            printf("%d ", warehouse[i][j]);
        }
        printf("\n");
    }
    printf("Freeing all allocated memory...\n");
    free_all(&warehouse, &unit_capacities, &num_units, &max_units_capacity);
    printf("Memory freed. warehouse: %p, unit_capacities: %p, num_units: %d, max_units_capacity: %d\n", 
           (void*)warehouse, (void*)unit_capacities, num_units, max_units_capacity);
    return 0;
}