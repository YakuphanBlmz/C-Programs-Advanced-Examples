#include <stdio.h>
#include <stdlib.h>
void printJaggedArray(int** jagged_array, int* row_sizes, int num_rows) {
    printf("Current Jagged Array:\n");
    if (num_rows == 0) {
        printf("  (Empty)\n");
        return;
    }
    for (int i = 0; i < num_rows; i++) {
        printf("  Row %d (%d elements): [", i, row_sizes[i]);
        for (int j = 0; j < row_sizes[i]; j++) {
            printf("%d", jagged_array[i][j]);
            if (j < row_sizes[i] - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}
int main() {
    int** jagged_array = NULL;
    int* row_capacities = NULL;
    int* row_sizes = NULL;
    int num_rows = 0;
    int max_rows_capacity = 0;
    int initial_row_element_capacity = 4;
    int initial_jagged_array_capacity = 2;
    printf("--- Initializing Jagged Array ---\n");
    printJaggedArray(jagged_array, row_sizes, num_rows);
    printf("\n--- Adding Rows ---\n");
    for (int i = 0; i < 3; i++) {
        printf("Adding Row %d\n", num_rows);
        if (num_rows == max_rows_capacity) {
            int new_capacity = (max_rows_capacity == 0) ? initial_jagged_array_capacity : max_rows_capacity * 2;
            int** new_jagged_array = (int**)realloc(jagged_array, new_capacity * sizeof(int*));
            int* new_row_capacities = (int*)realloc(row_capacities, new_capacity * sizeof(int));
            int* new_row_sizes = (int*)realloc(row_sizes, new_capacity * sizeof(int));
            if (!new_jagged_array || !new_row_capacities || !new_row_sizes) {
                fprintf(stderr, "Memory realloc failed during row capacity expansion.\n");
                for (int k = 0; k < num_rows; k++) {
                    free(jagged_array[k]);
                }
                free(jagged_array);
                free(row_capacities);
                free(row_sizes);
                return 1;
            }
            jagged_array = new_jagged_array;
            row_capacities = new_row_capacities;
            row_sizes = new_row_sizes;
            max_rows_capacity = new_capacity;
        }
        jagged_array[num_rows] = (int*)malloc(initial_row_element_capacity * sizeof(int));
        if (!jagged_array[num_rows]) {
            fprintf(stderr, "Memory malloc failed for new row.\n");
            for (int k = 0; k < num_rows; k++) {
                free(jagged_array[k]);
            }
            free(jagged_array);
            free(row_capacities);
            free(row_sizes);
            return 1;
        }
        row_capacities[num_rows] = initial_row_element_capacity;
        row_sizes[num_rows] = 0;
        num_rows++;
    }
    printJaggedArray(jagged_array, row_sizes, num_rows);
    printf("\n--- Adding Elements to Rows ---\n");
    int target_row_0 = 0;
    for (int i = 0; i < 5; i++) {
        if (row_sizes[target_row_0] == row_capacities[target_row_0]) {
            int new_element_capacity = row_capacities[target_row_0] * 2;
            int* new_row_data = (int*)realloc(jagged_array[target_row_0], new_element_capacity * sizeof(int));
            if (!new_row_data) {
                fprintf(stderr, "Memory realloc failed for row %d element capacity expansion.\n", target_row_0);
                for (int k = 0; k < num_rows; k++) {
                    free(jagged_array[k]);
                }
                free(jagged_array);
                free(row_capacities);
                free(row_sizes);
                return 1;
            }
            jagged_array[target_row_0] = new_row_data;
            row_capacities[target_row_0] = new_element_capacity;
        }
        jagged_array[target_row_0][row_sizes[target_row_0]++] = (target_row_0 + 1) * 10 + i;
    }
    printf("Added elements to Row %d\n", target_row_0);
    int target_row_1 = 1;
    for (int i = 0; i < 3; i++) {
        if (row_sizes[target_row_1] == row_capacities[target_row_1]) {
            int new_element_capacity = row_capacities[target_row_1] * 2;
            int* new_row_data = (int*)realloc(jagged_array[target_row_1], new_element_capacity * sizeof(int));
            if (!new_row_data) {
                fprintf(stderr, "Memory realloc failed for row %d element capacity expansion.\n", target_row_1);
                for (int k = 0; k < num_rows; k++) {
                    free(jagged_array[k]);
                }
                free(jagged_array);
                free(row_capacities);
                free(row_sizes);
                return 1;
            }
            jagged_array[target_row_1] = new_row_data;
            row_capacities[target_row_1] = new_element_capacity;
        }
        jagged_array[target_row_1][row_sizes[target_row_1]++] = (target_row_1 + 1) * 10 + i;
    }
    printf("Added elements to Row %d\n", target_row_1);
    int target_row_2 = 2;
    for (int i = 0; i < 2; i++) {
        if (row_sizes[target_row_2] == row_capacities[target_row_2]) {
            int new_element_capacity = row_capacities[target_row_2] * 2;
            int* new_row_data = (int*)realloc(jagged_array[target_row_2], new_element_capacity * sizeof(int));
            if (!new_row_data) {
                fprintf(stderr, "Memory realloc failed for row %d element capacity expansion.\n", target_row_2);
                for (int k = 0; k < num_rows; k++) {
                    free(jagged_array[k]);
                }
                free(jagged_array);
                free(row_capacities);
                free(row_sizes);
                return 1;
            }
            jagged_array[target_row_2] = new_row_data;
            row_capacities[target_row_2] = new_element_capacity;
        }
        jagged_array[target_row_2][row_sizes[target_row_2]++] = (target_row_2 + 1) * 10 + i;
    }
    printf("Added elements to Row %d\n", target_row_2);
    printJaggedArray(jagged_array, row_sizes, num_rows);
    printf("\n--- Removing Row 1 ---\n");
    int row_to_remove = 1;
    if (row_to_remove >= 0 && row_to_remove < num_rows) {
        free(jagged_array[row_to_remove]);
        for (int i = row_to_remove; i < num_rows - 1; i++) {
            jagged_array[i] = jagged_array[i + 1];
            row_capacities[i] = row_capacities[i + 1];
            row_sizes[i] = row_sizes[i + 1];
        }
        num_rows--;
        printf("Row %d removed.\n", row_to_remove);
        if (num_rows > 0 && num_rows < max_rows_capacity / 2 && max_rows_capacity / 2 >= initial_jagged_array_capacity) {
            int new_capacity = max_rows_capacity / 2;
            int** new_jagged_array = (int**)realloc(jagged_array, new_capacity * sizeof(int*));
            int* new_row_capacities = (int*)realloc(row_capacities, new_capacity * sizeof(int));
            int* new_row_sizes = (int*)realloc(row_sizes, new_capacity * sizeof(int));
            if (new_jagged_array && new_row_capacities && new_row_sizes) {
                jagged_array = new_jagged_array;
                row_capacities = new_row_capacities;
                row_sizes = new_row_sizes;
                max_rows_capacity = new_capacity;
                printf("Jagged array main capacity shrunk to %d.\n", max_rows_capacity);
            }
        } else if (num_rows == 0) {
            free(jagged_array); jagged_array = NULL;
            free(row_capacities); row_capacities = NULL;
            free(row_sizes); row_sizes = NULL;
            max_rows_capacity = 0;
            printf("All rows removed, main arrays freed.\n");
        }
    } else {
        printf("Invalid row index %d for removal.\n", row_to_remove);
    }
    printJaggedArray(jagged_array, row_sizes, num_rows);
    printf("\n--- Adding one more element to Row 0 ---\n");
    target_row_0 = 0;
    if (num_rows > target_row_0) {
        if (row_sizes[target_row_0] == row_capacities[target_row_0]) {
            int new_element_capacity = row_capacities[target_row_0] * 2;
            int* new_row_data = (int*)realloc(jagged_array[target_row_0], new_element_capacity * sizeof(int));
            if (!new_row_data) {
                fprintf(stderr, "Memory realloc failed for row %d element capacity expansion.\n", target_row_0);
                for (int k = 0; k < num_rows; k++) {
                    free(jagged_array[k]);
                }
                free(jagged_array);
                free(row_capacities);
                free(row_sizes);
                return 1;
            }
            jagged_array[target_row_0] = new_row_data;
            row_capacities[target_row_0] = new_element_capacity;
        }
        jagged_array[target_row_0][row_sizes[target_row_0]++] = 99;
        printf("Added element 99 to Row %d\n", target_row_0);
    }
    printJaggedArray(jagged_array, row_sizes, num_rows);
    printf("\n--- Cleaning up memory ---\n");
    for (int i = 0; i < num_rows; i++) {
        free(jagged_array[i]);
        jagged_array[i] = NULL;
    }
    free(jagged_array);
    free(row_capacities);
    free(row_sizes);
    jagged_array = NULL;
    row_capacities = NULL;
    row_sizes = NULL;
    num_rows = 0;
    max_rows_capacity = 0;
    printf("Memory cleaned. Final state:\n");
    printJaggedArray(jagged_array, row_sizes, num_rows);
    return 0;
}