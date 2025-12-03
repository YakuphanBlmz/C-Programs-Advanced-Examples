#include <stdio.h>
#include <stdlib.h>
int*** create_3d_like_grid(int rows, int cols, const int* inner_sizes_flat) {
    int*** grid = (int***)malloc(rows * sizeof(int**));
    if (grid == NULL) return NULL;
    for (int i = 0; i < rows; i++) {
        grid[i] = (int**)malloc(cols * sizeof(int*));
        if (grid[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(grid[k]);
            }
            free(grid);
            return NULL;
        }
        for (int j = 0; j < cols; j++) {
            int current_inner_size = inner_sizes_flat[i * cols + j];
            grid[i][j] = (int*)malloc(current_inner_size * sizeof(int));
            if (grid[i][j] == NULL) {
                for (int m = 0; m <= i; m++) {
                    for (int n = 0; n < (m == i ? j : cols); n++) {
                        free(grid[m][n]);
                    }
                    free(grid[m]);
                }
                free(grid);
                return NULL;
            }
            for (int k = 0; k < current_inner_size; k++) {
                grid[i][j][k] = (i + 1) * 10000 + (j + 1) * 100 + k;
            }
        }
    }
    return grid;
}
int resize_inner_array(int*** grid, int r, int c, int new_inner_size) {
    int* temp = (int*)realloc(grid[r][c], new_inner_size * sizeof(int));
    if (new_inner_size > 0 && temp == NULL) {
        return 0;
    }
    grid[r][c] = temp;
    return 1;
}
int resize_outer_grid(int**** grid_ptr, int old_rows, int old_cols, int new_rows, int new_cols, const int* new_inner_sizes_flat) {
    int*** current_grid = *grid_ptr;
    int i, j, k;
    if (new_rows < old_rows) {
        for (i = new_rows; i < old_rows; i++) {
            for (j = 0; j < old_cols; j++) {
                free(current_grid[i][j]);
            }
            free(current_grid[i]);
        }
    }
    int*** temp_grid = (int***)realloc(current_grid, new_rows * sizeof(int**));
    if (new_rows > 0 && temp_grid == NULL) {
        return 0;
    }
    *grid_ptr = temp_grid;
    current_grid = temp_grid;
    int common_rows_for_cols_resize = (old_rows < new_rows) ? old_rows : new_rows;
    for (i = 0; i < common_rows_for_cols_resize; i++) {
        if (new_cols < old_cols) {
            for (j = new_cols; j < old_cols; j++) {
                free(current_grid[i][j]);
            }
        }
        int** temp_row = (int**)realloc(current_grid[i], new_cols * sizeof(int*));
        if (new_cols > 0 && temp_row == NULL) {
            return 0;
        }
        current_grid[i] = temp_row;
        if (new_cols > old_cols) {
            for (j = old_cols; j < new_cols; j++) {
                int current_inner_size = new_inner_sizes_flat[i * new_cols + j];
                current_grid[i][j] = (int*)malloc(current_inner_size * sizeof(int));
                if (current_grid[i][j] == NULL) {
                    return 0;
                }
                for (k = 0; k < current_inner_size; k++) {
                    current_grid[i][j][k] = (i + 1) * 10000 + (j + 1) * 100 + k;
                }
            }
        }
    }
    if (new_rows > old_rows) {
        for (i = old_rows; i < new_rows; i++) {
            current_grid[i] = (int**)malloc(new_cols * sizeof(int*));
            if (current_grid[i] == NULL) {
                return 0;
            }
            for (j = 0; j < new_cols; j++) {
                int current_inner_size = new_inner_sizes_flat[i * new_cols + j];
                current_grid[i][j] = (int*)malloc(current_inner_size * sizeof(int));
                if (current_grid[i][j] == NULL) {
                    return 0;
                }
                for (k = 0; k < current_inner_size; k++) {
                    current_grid[i][j][k] = (i + 1) * 10000 + (j + 1) * 100 + k;
                }
            }
        }
    }
    return 1;
}
void free_3d_like_grid(int*** grid, int rows, int cols) {
    if (grid == NULL) return;
    for (int i = 0; i < rows; i++) {
        if (grid[i] != NULL) {
            for (int j = 0; j < cols; j++) {
                free(grid[i][j]);
            }
            free(grid[i]);
        }
    }
    free(grid);
}
int main() {
    int current_rows = 2;
    int current_cols = 2;
    int initial_inner_sizes[] = {1, 2, 3, 4};
    int*** my_grid = create_3d_like_grid(current_rows, current_cols, initial_inner_sizes);
    if (my_grid == NULL) {
        printf("Initial allocation failed.\n");
        return 1;
    }
    *my_grid[0][0] = 99; 
    if (!resize_inner_array(my_grid, 0, 1, 5)) {
        printf("Inner array resize failed.\n");
    }
    int new_rows_1 = 3;
    int new_cols_1 = 3;
    int new_inner_sizes_for_resize_1[] = {
        1, 2, 5,   
        3, 4, 1,   
        2, 3, 4    
    };
    if (!resize_outer_grid(&my_grid, current_rows, current_cols, new_rows_1, new_cols_1, new_inner_sizes_for_resize_1)) {
        printf("Outer grid resize (expand) failed.\n");
    }
    current_rows = new_rows_1;
    current_cols = new_cols_1;
    int new_rows_2 = 1;
    int new_cols_2 = 1;
    int new_inner_sizes_for_resize_2[] = {10};
    if (!resize_outer_grid(&my_grid, current_rows, current_cols, new_rows_2, new_cols_2, new_inner_sizes_for_resize_2)) {
        printf("Outer grid resize (shrink) failed.\n");
    }
    current_rows = new_rows_2;
    current_cols = new_cols_2;
    free_3d_like_grid(my_grid, current_rows, current_cols);
    return 0;
}