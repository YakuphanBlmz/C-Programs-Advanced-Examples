#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int*** createGrid(int rows, int cols) {
    int ***grid = (int ***)malloc(rows * sizeof(int **));
    for (int i = 0; i < rows; i++) {
        grid[i] = (int **)malloc(cols * sizeof(int *));
        for (int j = 0; j < cols; j++) {
            grid[i][j] = NULL;
        }
    }
    return grid;
}
void populateCellWithSize(int ***grid, int r, int c, int size, int value_start) {
    if (grid[r][c] != NULL) {
        free(grid[r][c]);
    }
    if (size == 0) {
        grid[r][c] = NULL;
        return;
    }
    grid[r][c] = (int *)malloc((size + 1) * sizeof(int));
    grid[r][c][0] = size;
    for (int k = 0; k < size; k++) {
        grid[r][c][k + 1] = value_start + k;
    }
}
int getCellSize(int ***grid, int r, int c) {
    if (grid[r][c] == NULL) {
        return 0;
    }
    return grid[r][c][0];
}
void mergeCells(int ***grid, int dr, int dc, int sr, int sc) {
    if (grid[sr][sc] == NULL) {
        return;
    }
    int dest_old_size = getCellSize(grid, dr, dc);
    int src_size = getCellSize(grid, sr, sc);
    int new_total_size = dest_old_size + src_size;
    if (new_total_size == 0) {
        if (grid[dr][dc] != NULL) { free(grid[dr][dc]); grid[dr][dc] = NULL; }
        free(grid[sr][sc]);
        grid[sr][sc] = NULL;
        return;
    }
    int *new_dest_arr = (int *)realloc(grid[dr][dc], (new_total_size + 1) * sizeof(int));
    if (new_dest_arr == NULL) {
        return;
    }
    grid[dr][dc] = new_dest_arr;
    grid[dr][dc][0] = new_total_size;
    if (src_size > 0) {
        memcpy(&(grid[dr][dc][dest_old_size + 1]), &(grid[sr][sc][1]), src_size * sizeof(int));
    }
    free(grid[sr][sc]);
    grid[sr][sc] = NULL;
}
int*** resizeGrid(int ***old_grid, int old_rows, int old_cols, int new_rows, int new_cols) {
    if (new_rows <= 0 || new_cols <= 0) {
        return NULL;
    }
    int ***new_grid = (int ***)malloc(new_rows * sizeof(int **));
    for (int i = 0; i < new_rows; i++) {
        new_grid[i] = (int **)malloc(new_cols * sizeof(int *));
        for (int j = 0; j < new_cols; j++) {
            new_grid[i][j] = NULL;
        }
    }
    int min_rows = (old_rows < new_rows) ? old_rows : new_rows;
    int min_cols = (old_cols < new_cols) ? old_cols : new_cols;
    for (int i = 0; i < min_rows; i++) {
        for (int j = 0; j < min_cols; j++) {
            new_grid[i][j] = old_grid[i][j];
            old_grid[i][j] = NULL;
        }
    }
    for (int i = 0; i < old_rows; i++) {
        for (int j = 0; j < old_cols; j++) {
            if (old_grid[i][j] != NULL) {
                free(old_grid[i][j]);
            }
        }
        free(old_grid[i]);
    }
    free(old_grid);
    return new_grid;
}
void printGrid(int ***grid, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("[%d][%d]: ", i, j);
            if (grid[i][j] == NULL) {
                printf("{NULL}\n");
            } else {
                int size = getCellSize(grid, i, j);
                printf("{size=%d, data=", size);
                for (int k = 0; k < size; k++) {
                    printf("%d ", grid[i][j][k + 1]);
                }
                printf("}\n");
            }
        }
    }
}
void destroyGrid(int ***grid, int rows, int cols) {
    if (grid == NULL) return;
    for (int i = 0; i < rows; i++) {
        if (grid[i] != NULL) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] != NULL) {
                    free(grid[i][j]);
                }
            }
            free(grid[i]);
        }
    }
    free(grid);
}
int main() {
    int rows = 3, cols = 3;
    int ***grid = createGrid(rows, cols);
    populateCellWithSize(grid, 0, 0, 3, 10);
    populateCellWithSize(grid, 0, 1, 2, 20);
    populateCellWithSize(grid, 1, 0, 4, 30);
    populateCellWithSize(grid, 1, 1, 1, 40);
    populateCellWithSize(grid, 2, 2, 5, 50);
    printf("Initial Grid:\n");
    printGrid(grid, rows, cols);
    printf("\nMerging (0,0) with (0,1):\n");
    mergeCells(grid, 0, 0, 0, 1);
    printGrid(grid, rows, cols);
    printf("\nMerging (1,0) with (2,2):\n");
    mergeCells(grid, 1, 0, 2, 2);
    printGrid(grid, rows, cols);
    printf("\nResizing grid from %dx%d to 2x4:\n", rows, cols);
    int new_rows = 2, new_cols = 4;
    grid = resizeGrid(grid, rows, cols, new_rows, new_cols);
    rows = new_rows;
    cols = new_cols;
    populateCellWithSize(grid, 0, 3, 2, 60);
    populateCellWithSize(grid, 1, 2, 3, 70);
    printGrid(grid, rows, cols);
    destroyGrid(grid, rows, cols);
    return 0;
}