#include <stdio.h>
#include <stdlib.h>
void initialize_grid(int*** grid_ptr, int* rows_ptr, int* cols_ptr, int initial_rows, int initial_cols, int default_value) {
    if (initial_rows <= 0 || initial_cols <= 0) {
        *grid_ptr = NULL;
        *rows_ptr = 0;
        *cols_ptr = 0;
        return;
    }
    *grid_ptr = (int**)malloc(initial_rows * sizeof(int*));
    if (*grid_ptr == NULL) {
        perror("Failed to allocate memory for grid rows");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < initial_rows; i++) {
        (*grid_ptr)[i] = (int*)malloc(initial_cols * sizeof(int));
        if ((*grid_ptr)[i] == NULL) {
            perror("Failed to allocate memory for grid column");
            for (int k = 0; k < i; k++) {
                free((*grid_ptr)[k]);
            }
            free(*grid_ptr);
            *grid_ptr = NULL;
            *rows_ptr = 0;
            *cols_ptr = 0;
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < initial_cols; j++) {
            (*grid_ptr)[i][j] = default_value;
        }
    }
    *rows_ptr = initial_rows;
    *cols_ptr = initial_cols;
}
void resize_grid(int*** grid_ptr, int* current_rows_ptr, int* current_cols_ptr, int new_rows, int new_cols, int default_value) {
    if (new_rows <= 0 || new_cols <= 0) {
        if (*grid_ptr != NULL) {
            for (int i = 0; i < *current_rows_ptr; i++) {
                free((*grid_ptr)[i]);
            }
            free(*grid_ptr);
        }
        *grid_ptr = NULL;
        *current_rows_ptr = 0;
        *current_cols_ptr = 0;
        return;
    }
    int old_rows = *current_rows_ptr;
    int old_cols = *current_cols_ptr;
    if (new_rows < old_rows) {
        for (int i = new_rows; i < old_rows; i++) {
            free((*grid_ptr)[i]);
        }
    }
    int** temp_grid = (int**)realloc(*grid_ptr, new_rows * sizeof(int*));
    if (temp_grid == NULL) {
        perror("Failed to reallocate memory for grid rows");
        exit(EXIT_FAILURE);
    }
    *grid_ptr = temp_grid;
    for (int i = 0; i < new_rows; i++) {
        if (i < old_rows) {
            int* temp_row = (int*)realloc((*grid_ptr)[i], new_cols * sizeof(int));
            if (temp_row == NULL) {
                perror("Failed to reallocate memory for grid column");
                exit(EXIT_FAILURE);
            }
            (*grid_ptr)[i] = temp_row;
            if (new_cols > old_cols) {
                for (int j = old_cols; j < new_cols; j++) {
                    (*grid_ptr)[i][j] = default_value;
                }
            }
        } else {
            (*grid_ptr)[i] = (int*)malloc(new_cols * sizeof(int));
            if ((*grid_ptr)[i] == NULL) {
                perror("Failed to allocate memory for new grid column");
                exit(EXIT_FAILURE);
            }
            for (int j = 0; j < new_cols; j++) {
                (*grid_ptr)[i][j] = default_value;
            }
        }
    }
    *current_rows_ptr = new_rows;
    *current_cols_ptr = new_cols;
}
void set_value(int** grid, int rows, int cols, int r, int c, int val) {
    if (grid == NULL || r < 0 || r >= rows || c < 0 || c >= cols) {
        return;
    }
    grid[r][c] = val;
}
int get_value(int** grid, int rows, int cols, int r, int c) {
    if (grid == NULL || r < 0 || r >= rows || c < 0 || c >= cols) {
        return -1;
    }
    return grid[r][c];
}
void print_grid(int** grid, int rows, int cols) {
    if (grid == NULL || rows == 0 || cols == 0) {
        printf("Grid is empty or invalid.\n");
        return;
    }
    printf("Grid (%dx%d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d", grid[i][j]);
        }
        printf("\n");
    }
}
void free_grid(int*** grid_ptr, int* rows_ptr) {
    if (*grid_ptr == NULL) {
        return;
    }
    for (int i = 0; i < *rows_ptr; i++) {
        free((*grid_ptr)[i]);
    }
    free(*grid_ptr);
    *grid_ptr = NULL;
    *rows_ptr = 0;
}
int main() {
    int** myGrid = NULL;
    int numRows = 0;
    int numCols = 0;
    initialize_grid(&myGrid, &numRows, &numCols, 3, 4, 0);
    print_grid(myGrid, numRows, numCols);
    set_value(myGrid, numRows, numCols, 0, 0, 10);
    set_value(myGrid, numRows, numCols, 1, 2, 20);
    set_value(myGrid, numRows, numCols, 2, 3, 30);
    print_grid(myGrid, numRows, numCols);
    resize_grid(&myGrid, &numRows, &numCols, 4, 6, 99);
    print_grid(myGrid, numRows, numCols);
    set_value(myGrid, numRows, numCols, 3, 5, 40);
    print_grid(myGrid, numRows, numCols);
    resize_grid(&myGrid, &numRows, &numCols, 2, 3, 0);
    print_grid(myGrid, numRows, numCols);
    printf("Value at (0,0): %d\n", get_value(myGrid, numRows, numCols, 0, 0));
    printf("Value at (1,2): %d\n", get_value(myGrid, numRows, numCols, 1, 2));
    printf("Value at (0,5) (out of bounds after resize): %d\n", get_value(myGrid, numRows, numCols, 0, 5));
    free_grid(&myGrid, &numRows);
    print_grid(myGrid, numRows, numCols);
    initialize_grid(&myGrid, &numRows, &numCols, 0, 0, 0);
    print_grid(myGrid, numRows, numCols);
    free_grid(&myGrid, &numRows);
    return 0;
}