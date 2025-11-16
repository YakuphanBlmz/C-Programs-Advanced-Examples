#include <stdio.h>
#include <stdlib.h>
int** create_grid(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        fprintf(stderr, "Error: Grid dimensions must be positive.\n");
        return NULL;
    }
    int** grid = (int**)malloc(rows * sizeof(int*));
    if (grid == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for grid rows.\n");
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        grid[i] = (int*)malloc(cols * sizeof(int));
        if (grid[i] == NULL) {
            fprintf(stderr, "Error: Failed to allocate memory for row %d.\n", i);
            for (int k = 0; k < i; k++) {
                free(grid[k]);
            }
            free(grid);
            return NULL;
        }
        for (int j = 0; j < cols; j++) {
            grid[i][j] = 0;
        }
    }
    return grid;
}
void add_row(int*** grid_ptr, int* rows_ptr, int current_cols, int default_value) {
    int new_rows = *rows_ptr + 1;
    int** new_grid = (int**)realloc(*grid_ptr, new_rows * sizeof(int*));
    if (new_grid == NULL) {
        fprintf(stderr, "Error: Failed to reallocate memory for rows.\n");
        exit(EXIT_FAILURE);
    }
    *grid_ptr = new_grid;
    (*grid_ptr)[new_rows - 1] = (int*)malloc(current_cols * sizeof(int));
    if ((*grid_ptr)[new_rows - 1] == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for a new row.\n");
        exit(EXIT_FAILURE);
    }
    for (int j = 0; j < current_cols; j++) {
        (*grid_ptr)[new_rows - 1][j] = default_value;
    }
    *rows_ptr = new_rows;
}
void add_column(int** grid, int current_rows, int* cols_ptr, int default_value) {
    int new_cols = *cols_ptr + 1;
    for (int i = 0; i < current_rows; i++) {
        int* new_row = (int*)realloc(grid[i], new_cols * sizeof(int));
        if (new_row == NULL) {
            fprintf(stderr, "Error: Failed to reallocate memory for column in row %d.\n", i);
            exit(EXIT_FAILURE);
        }
        grid[i] = new_row;
        grid[i][new_cols - 1] = default_value;
    }
    *cols_ptr = new_cols;
}
void set_value(int** grid, int row, int col, int value) {
    grid[row][col] = value;
}
void print_grid(int** grid, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", grid[i][j]);
        }
        printf("\n");
    }
}
void free_grid(int** grid, int rows) {
    if (grid == NULL) return;
    for (int i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);
}
int main() {
    int rows = 3;
    int cols = 2;
    int** grid = create_grid(rows, cols);
    if (grid == NULL) return EXIT_FAILURE;
    printf("Initial Grid (3x2):\n");
    print_grid(grid, rows, cols);
    set_value(grid, 0, 0, 10);
    set_value(grid, 1, 1, 20);
    printf("\nGrid after setting values (10 at 0,0; 20 at 1,1):\n");
    print_grid(grid, rows, cols);
    printf("\nAdding a row with default value 5...\n");
    add_row(&grid, &rows, cols, 5);
    print_grid(grid, rows, cols);
    printf("\nAdding a column with default value 99...\n");
    add_column(grid, rows, &cols, 99);
    print_grid(grid, rows, cols);
    printf("\nAdding another row with default value 1...\n");
    add_row(&grid, &rows, cols, 1);
    print_grid(grid, rows, cols);
    printf("\nAdding another column with default value 7...\n");
    add_column(grid, rows, &cols, 7);
    print_grid(grid, rows, cols);
    set_value(grid, 3, 2, 30);
    printf("\nGrid after setting value (30 at 3,2):\n");
    print_grid(grid, rows, cols);
    free_grid(grid, rows);
    return 0;
}