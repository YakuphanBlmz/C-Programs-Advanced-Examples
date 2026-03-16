#include <stdio.h>
#include <stdlib.h>
int containsTarget(int* row, int target) {
    if (row == NULL || row[0] <= 0) {
        return 0;
    }
    int len = row[0];
    for (int i = 1; i <= len; i++) {
        if (row[i] == target) {
            return 1;
        }
    }
    return 0;
}
void removeRowsWithTarget(int*** array_ptr, int* num_rows_ptr, int target_value) {
    int** current_array = *array_ptr;
    int current_num_rows = *num_rows_ptr;
    if (current_array == NULL || current_num_rows <= 0) {
        return;
    }
    int write_idx = 0;
    for (int read_idx = 0; read_idx < current_num_rows; read_idx++) {
        if (!containsTarget(current_array[read_idx], target_value)) {
            if (read_idx != write_idx) {
                current_array[write_idx] = current_array[read_idx];
            }
            write_idx++;
        } else {
            free(current_array[read_idx]);
        }
    }
    *num_rows_ptr = write_idx;
    if (write_idx == 0) {
        if (current_array != NULL) {
            free(current_array);
        }
        *array_ptr = NULL;
    } else {
        int** new_array_block = (int**)realloc(current_array, write_idx * sizeof(int*));
        if (new_array_block != NULL) {
            *array_ptr = new_array_block;
        }
    }
}
int main() {
    int** array = NULL;
    int num_rows = 0;
    printf("--- Initial Array Setup ---\n");
    num_rows = 3;
    array = (int**)malloc(num_rows * sizeof(int*));
    array[0] = (int*)malloc((3 + 1) * sizeof(int));
    array[0][0] = 3; array[0][1] = 10; array[0][2] = 20; array[0][3] = 30;
    array[1] = (int*)malloc((2 + 1) * sizeof(int));
    array[1][0] = 2; array[1][1] = 40; array[1][2] = 50;
    array[2] = (int*)malloc((4 + 1) * sizeof(int));
    array[2][0] = 4; array[2][1] = 60; array[2][2] = 20; array[2][3] = 80; array[2][4] = 90;
    printf("Original array (num_rows: %d):\n", num_rows);
    for (int i = 0; i < num_rows; i++) {
        printf("Row %d (len %d): ", i, array[i][0]);
        for (int j = 1; j <= array[i][0]; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("--- Removing rows containing 20 ---\n");
    int target_val_1 = 20;
    removeRowsWithTarget(&array, &num_rows, target_val_1);
    printf("Array after removing rows with %d (num_rows: %d):\n", target_val_1, num_rows);
    if (array == NULL || num_rows == 0) {
        printf("Array is empty.\n");
    } else {
        for (int i = 0; i < num_rows; i++) {
            printf("Row %d (len %d): ", i, array[i][0]);
            for (int j = 1; j <= array[i][0]; j++) {
                printf("%d ", array[i][j]);
            }
            printf("\n");
        }
    }
    printf("\n");
    printf("--- Removing rows containing 40 ---\n");
    int target_val_2 = 40;
    removeRowsWithTarget(&array, &num_rows, target_val_2);
    printf("Array after removing rows with %d (num_rows: %d):\n", target_val_2, num_rows);
    if (array == NULL || num_rows == 0) {
        printf("Array is empty.\n");
    } else {
        for (int i = 0; i < num_rows; i++) {
            printf("Row %d (len %d): ", i, array[i][0]);
            for (int j = 1; j <= array[i][0]; j++) {
                printf("%d ", array[i][j]);
            }
            printf("\n");
        }
    }
    printf("\n");
    if (array != NULL) {
        for (int i = 0; i < num_rows; i++) {
            free(array[i]);
        }
        free(array);
        array = NULL;
    }
    printf("All dynamic memory freed.\n");
    return 0;
}